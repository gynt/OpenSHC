from collections.abc import Iterable
import re
from typing import List

from tokenizer import Tokenizer

from ghidra.app.decompiler import ClangFuncNameToken, ClangVariableToken, DecompileResults
from ghidra.program.model.pcode import EquateSymbol, HighFunction
from ghidra.program.model.listing import Function

def joinit(iterable, delimiter):
    try:
        it = iter(iterable)
        yield next(it)
        for x in it:
            yield delimiter
            yield x
    except StopIteration:
        return

class FunctionRewriter(object):

  def __init__(self, results: DecompileResults) -> None:
    self._results = results
    self._hf: HighFunction = results.getHighFunction()
    self._includes = []
    self._usings = []
    self._namespace = list(str(n) for n in self._results.getFunction().getParentNamespace().getPathList(True))
    self._wrapping_namespace = self._namespace[:-1]
    self._namespace_type = self._results.getFunction().getParentNamespace().getType().name()
    self._global_symbols = dict((s.getName(), s) for s in self._hf.getGlobalSymbolMap().getSymbols())
    self._program = self._hf.getDataTypeManager().getProgram()

  def var_path_matches_namespace(self, path: str):
    ns = [el for el in path.split("/") if el]
    return ns == self._namespace

  def is_this_variable(self, tok: ClangVariableToken):
    """Returns if the token's high symbol has a data type that has the name path as the function's namespace"""
    hs = tok.getHighSymbol(self._hf)
    if not hs:
      return False
    if not hs.isGlobal():
      return False
    dt = hs.getDataType()
    return self.var_path_matches_namespace(str(dt.getDataTypePath()))

  def register_datatype(self, dt, usings = False, ignore_simple: bool = True):
    include = str(dt.getDataTypePath())
    if ignore_simple:
      if not include.startswith("/OpenSHC"):
        return
    if not include in self._includes:
      self._includes.append(include)
    if usings and not include in self._usings:
      self._usings.append(include)

  def rewrite_ClangFuncProto_ClangReturnType(self, crt: Tokenizer):
    assert crt.has_next()
    tok = crt.next()
    dt = tok.getDataType() # type: ignore
    self.register_datatype(dt, usings=True)
    return [dt.getName()]
  
  def rewrite_ClangFuncProto_ClangVariableDecl(self, cvd: Tokenizer):
    assert cvd.has_next()
    if cvd.has_upcoming_token(lambda x: str(x) == "this"):
      return [] # We swallow ClassType * this
    
    tok_dt = cvd.next()
    dt = tok_dt.getDataType() # type: ignore
    self.register_datatype(dt, usings=True)

    return [str(tok) for tok in cvd._tokens]

  def rewrite_ClangFuncProto(self, cfp: Tokenizer):
    r = []
    while cfp.has_next():
      tok = cfp.next()
      if str(tok) == self._results.getFunction().getCallingConvention().getName() or str(tok) == self._namespace[0]:
        if str(tok) == self._results.getFunction().getCallingConvention().getName() and str(tok) != "__thiscall":
          r.append(str(tok))
        # After parsing the calling convention we are guaranteed going to enter the function name(space)
        r += [self._namespace[-1], " :: ", self._results.getFunction().getName()]
        while str(cfp.current()) != "(":
          tok = cfp.next()
        r.append("(")
        params = []
        while cfp.has_next():
          cfp.next()
          if cfp.class_name(cfp.current()) == "ClangVariableDecl":
            param = self.rewrite_current(cfp, ["ClangFuncProto"])
            if param:
              params.append(''.join(param))
        r += list(joinit(params, ','))
        r.append(")")
        return r
      r += self.rewrite_current(cfp, ["ClangFuncProto"])  
    return r
  
  def is_thiscall(self, token):
    pass

  def rewrite_variable_only(self, v):
    return v.token + "::instance"
  
  def rewrite_variable(self, v: Tokenizer):
    r = []
    if v.is_instance(v.current(), "ClangOpToken") and str(v.current()) == "&":
      if v.is_instance(v.peek(2), "ClangVariableToken"):
        t4s = str(v.peek(4))
        if t4s == ".":
          r += ["&", str(v.peek(2)), "::instance", "."]
        else:
          r += [str(v.peek(2)), "::instance"]
        v.forward(4)
    elif v.is_instance(v.current(), "ClangVariableToken"):
      if str(v.peek(1)) == ".":
        r += [str(v.current()) + "::instance", "."]
      else:
        r += [str(v.current()) + "::instance"]
    return r
  
  def _advance_first_method_argument(self, fn: Tokenizer):
    assert str(fn.peek(2)) == "("
    if str(fn.peek(4)) == "this":
      fn.advance_multiple(4)
      return "this"
    assert str(fn.peek(4)) == "&"
    var = fn.advance_multiple(6)[-1]
    if isinstance(var, ClangVariableToken) and self.is_this_variable(var):
      return "this"
    return var
  
  def _process_func_args(self, fn: Tokenizer):
    r = []
    while fn.has_next() and fn.has_upcoming_token(predicate=lambda x: True, failfast=lambda x: str(x) in [")", ";"]):
      # TODO: how to handle end of arguments of function??
      fn.next()
      r += self.rewrite_current(fn)
    if str(fn.peek()) == ")":
      fn.next()
    return r

  def rewrite_function_namespace(self, fn: Tokenizer):
    r = []
    f = [fn.current()]
    if fn.class_name(fn.current()) != "ClangFuncNameToken":
      f = fn.advance_until(lambda x: fn.is_instance(x, "ClangFuncNameToken"), inclusive_return=True)
    if f:
      nspart, funcname = f[:-1], f[-1]
      if not isinstance(funcname, ClangFuncNameToken):
        raise Exception()

      addr = funcname.getMinAddress()
      cu = self._program.getListing().getCodeUnitAt(addr)
      if cu.getMnemonicString() != "CALL" and cu.getMnemonicString() != "JMP":
        raise Exception(addr)
      target_address = cu.getPrimaryReference(0).getToAddress()
      func: Function = self._program.getFunctionManager().getFunctionAt(target_address)
      pns = func.getParentNamespace()
      pl = list(pns.getPathList(True))
      pl_func = "::".join(pl[:-1] + [f"{pl[-1]}_Func"])
      pl_func += "::" + func.getName()
      if pns.getType().name() == "CLASS":
        first = self._advance_first_method_argument(fn)
        args = []
        if str(fn.peek(2)) == ",":
          fn.advance_multiple(2)
          args = self._process_func_args(fn)
        r +=  [
          "MACRO_MEMBER_CALL",
          "(",
          pl_func,
          ",",
          " ",
          "this" if str(first) == "this" else f"{first}::ptr",
          ")",
          "(",
          *args,
          ")",
        ]
      else:
        # TODO:
        pass
    else:
      funcname = fn.current()
      r.append(funcname)
    return r
  
  def singleton_symbol(self):
    return None
  
  def rewrite_ClangStatement(self, s: Tokenizer):
    r = []
    while s.has_next():
      s.next()
      cur = s.current()
      if s.class_name(cur) == "ClangVariableToken":
        if self.is_this_variable(cur):
          r.append("this")
          s.advance_until(lambda x: s.class_name(x) != "ClangBreak" and str(s) != " ")
          if str(s.next()) == ".":
            r.append("->") # substitute . with -> in case of DAT_ to this conversion
            s.next()
        else:
          r += self.rewrite_current(s, context=["ClangStatement"])
      elif s.has_upcoming_token(predicate=lambda x: s.is_instance(x, "ClangFuncNameToken"),
                                failfast=lambda x: not re.match(pattern="[A-Za-z0-9_:]*", string=str(x)),
                                include_current=True):
        fpart = [cur]
        if s.class_name(cur) != "ClangFuncNameToken":
          fpart = s.peek_until(lambda x: s.is_instance(x, "ClangFuncNameToken"), inclusive_return=True)
        # Note this inherits the Tokenizer instead of entering a new situation
        r += self.rewrite_function_namespace(s)
      else:
        r += self.rewrite_current(s, context=["ClangStatement"])
    return r
  
  def rewrite_ClangVariableToken(self, cvt: ClangVariableToken):
    hs = cvt.getHighSymbol(self._hf)
    if isinstance(hs, EquateSymbol):
      if not hs.getDataType() or str(hs.getDataType()) == 'undefined':
        return [str(hs.getValue())] # We do this because we can't get the enum associated with the equate name from anywhere...
      self.register_datatype(hs.getDataType(), usings = True)
    hc = cvt.getHighVariable()
    if hc:
      if hc.getDataType().getName() == "BOOLEnum":
        return [str(cvt)] # TRUE and FALSE can be written as such
    if str(cvt) == "'\\0'":
      return [str(0)] # convert uchar and char 0's into proper decimal 0's
    return [str(cvt)]
  
  def rewrite_ClangBreak(self):
    return ["\n"]
  
  def rewrite_ClangTokenGroup(self, s: Tokenizer):
    s.reset(False)
    r = []
    while s.has_next():
      cur = s.next()
      r += self.rewrite_current(s)
    return r
  
  def rewrite_current(self, s: Tokenizer, context: List[str] = [], fallback: bool = True):
    r = []
    cur = s.current()
    n = s.class_name(cur)
    simple_needle = f"rewrite_{n}"
    needle = simple_needle
    if context:
      needle = f"rewrite_{'_'.join(context)}_{n}"
    if n == "ClangBreak":
      r += self.rewrite_ClangBreak()
    elif hasattr(self, needle):
      if isinstance(cur, Iterable):
        r += getattr(self, needle)(s.enter(False))
      else:
        r += getattr(self, needle)(cur)
    elif fallback and hasattr(self, simple_needle):
      if isinstance(cur, Iterable):
        r += getattr(self, simple_needle)(s.enter(False))
      else:
        r += getattr(self, simple_needle)(cur)
    else:
      r.append(str(cur))
    return r
  
  def rewrite_function(self, s: Tokenizer):
    r = []
    if s._index == -1:
      s.next()
    while True:
      r += self.rewrite_current(s)
      if not s.has_next():
        break
      s.next()
    indentation = 0
    pr = []
    for c in r:
      newline = False
      newline_before = False
      if str(c) in ["{", "/*", "/**", "/* ", "/** "]:
        indentation += 2
        newline = True
      elif str(c) in ["}", "*/", " */"]:
        indentation -= 2
        newline = True
      elif str(c) in [";"]:
        newline = True
      pr.append(str(c))
      if newline:
        pr.append("\n")      
        if indentation:
          pr.append(" " * indentation)
    includes = "\n".join(f'#include "{str(incl)[1:]}.hpp"' for incl in self._includes)
    wrapper_open = "\n".join(f"namespace {ns} {{" for ns in self._wrapping_namespace)
    wrapper_close = "\n".join(f"}}" for ns in self._wrapping_namespace)
    usings = "\n".join(f'using {"::".join(str(incl)[1:].split("/"))};' for incl in self._includes)
    global_vars = "\n".join(f'#include "OpenSHC/Globals/{n}"'for n, s in self._global_symbols.items() if not self.var_path_matches_namespace(str(s.getDataType().getDataTypePath())))
    
    return f"{includes}\n\n{global_vars}\n\n{wrapper_open}\n\n{usings}\n\n{''.join(str(c) for c in pr)}\n\n{wrapper_close}".replace("_HoldStrong", "OpenSHC")