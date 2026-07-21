from collections.abc import Iterable
from typing import List

from tokenizer import Tokenizer

from ghidra.app.decompiler import ClangVariableToken, DecompileResults
from ghidra.program.model.pcode import EquateSymbol, HighFunction

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
    self._namespace = list(self._results.getFunction().getParentNamespace().getPathList(True))
    self._namespace_type = self._results.getFunction().getParentNamespace().getType().name()
    self._global_symbols = dict((s.getName(), s) for s in self._hf.getGlobalSymbolMap().getSymbols())

  def is_this_variable(self, tok: ClangVariableToken):
    """Returns if the token's high symbol has a data type that has the name path as the function's namespace"""
    hs = tok.getHighSymbol(self._hf)
    if not hs.isGlobal():
      return False
    dt = hs.getDataType()
    ns = [el for el in str(dt.getDataTypePath()).split("/") if el]
    return ns == self._namespace

  def register_datatype(self, dt, usings = False):
    include = dt.getDataTypePath()
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
  
  def rewrite_function_namespace(self, fn: Tokenizer):
    fn.reset(False)
    r = []
    f = fn.peek_until(lambda x: fn.is_instance(x, "ClangFuncNameToken"), inclusive_return=True)
    if f:
      nspart, funcname = f[:-1], f[-1]
      if nspart:
        untilns = nspart[:-4]
        ns = nspart[-4]

        r += untilns
        r += [str(ns) + "_Func" + "" + "::" + ""]
        # add include!
      else:
        # fetch the namespace _Func part from somewhere
        pass
    else:
      funcname = fn.current()
    r += [funcname]

    return r
  
  def singleton_symbol(self):
    return None
  
  def rewrite_ClangStatement(self, s: Tokenizer):
    r = []
    s.next()
    if s.class_name(s.current()) == "ClangVariableToken":
      if self.is_this_variable(s.current()):
        r.append("this")
        s.advance_until(lambda x: s.class_name(x) != "ClangBreak" and str(s) != " ")
        if str(s.next()) == ".":
          r.append("->") # substitute . with -> in case of DAT_ to this conversion
          s.next()
          
    

    # TODO: unfinished!
    if s.has_upcoming_token((lambda x: str(x) == " " and s.is_instance(x, "ClangSyntaxToken")), include_current=True):
      lhs = s.advance_until((lambda x: str(x) == " " and s.is_instance(x, "ClangSyntaxToken")), inclusive_return=True)
      r += lhs
      op = s.next()
      r.append(op)
      space = s.next()
      r.append(space)
      if not str(space) == " ":
        raise Exception()
      value = s.next()
      r.append(value)
      if s.has_upcoming_token((lambda x: str(x) == " " and s.is_instance(x, "ClangSyntaxToken")), include_current=True):
        print("oh no!")
        raise Exception("unhandled situation")
    if s.has_upcoming_token(lambda x: s.is_instance(x, "ClangFuncNameToken"), include_current=True):
      fpart = s.advance_until(lambda x: s.is_instance(x, "ClangFuncNameToken"), inclusive_return=True)
      fns = self.rewrite_function_namespace(Tokenizer(fpart))
      macro = "MACRO_CALL"
      thiscall = self.is_thiscall(fpart[-1])
      if thiscall:
        macro = "MACRO_CALL_MEMBER"
      r += [macro, "("] + fns
      if thiscall:
        pass
      
      r += [")"]
    else:
      n = s.next(no_exception=True)
      if n is not None:
        r += [n]
    return r
  
  def rewrite_ClangVariableToken(self, cvt: ClangVariableToken):
    hs = cvt.getHighSymbol(self._hf)
    if isinstance(hs, EquateSymbol):
      if not hs.getDataType() or str(hs.getDataType()) == 'undefined':
        return [str(hs.getValue())] # We do this because we can't get the enum associated with the equate name from anywhere...
      self.register_datatype(hs.getDataType(), usings = True)
    return str(cvt)
  
  def rewrite_ClangBreak(self):
    return ["\n"]
  
  def rewrite_ClangTokenGroup(self, s: Tokenizer):
    s.reset(False)
    r = []
    while s.has_next():
      cur = s.next()
      r += self.rewrite_current(s)
    return r
  
  def rewrite_current(self, s: Tokenizer, context: List[str] = []):
    r = []
    cur = s.current()
    n = s.class_name(cur)
    needle = f"rewrite_{n}"
    if context:
      needle = f"rewrite_{'_'.join(context)}_{n}"
    if n == "ClangBreak":
      r += self.rewrite_ClangBreak()
    elif hasattr(self, needle):
      if isinstance(cur, Iterable):
        r += getattr(self, needle)(s.enter(False))
      else:
        r += getattr(self, needle)(cur)
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
    return ''.join(str(c) for c in pr)