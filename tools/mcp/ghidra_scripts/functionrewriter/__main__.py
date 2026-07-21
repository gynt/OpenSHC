import atexit
import pyghidra

if not pyghidra.started():
    pyghidra.start()

import tempfile
project_dir = tempfile.mkdtemp(prefix="ghidra-project-")
project_name = "temp-project"
project = pyghidra.open_project(project_dir, project_name, True)

from java.io import File

from ghidra.base.project import GhidraProject
from ghidra.app.util.importer import ProgramLoader
from ghidra.util.task import ConsoleTaskMonitor

monitor = ConsoleTaskMonitor()

loader = pyghidra.program_loader().project(project)
loader = loader.source("Stronghold Crusader.exe.gzf")
with loader.load() as load_results:
    load_results.save(pyghidra.task_monitor()) # type: ignore
    

currentProgram, obj = pyghidra.consume_program(project, "/Stronghold Crusader.exe", project)

from ghidra.program.flatapi import FlatProgramAPI
flat_api = FlatProgramAPI(currentProgram, pyghidra.task_monitor())

def getCurrentProgram():
    return currentProgram

def do_atexit():
    currentProgram.release(project) # type: ignore
    project.close()

atexit.register(do_atexit)


# Start scripting!

from urllib.parse import urlparse, parse_qs
from ghidra.app.decompiler import DecompInterface, DecompileOptions, DecompileResults # type: ignore
from ghidra.util.task import ConsoleTaskMonitor # type: ignore
from ghidra.program.model.listing import Function # type: ignore
from ghidra.program.model.pcode import HighSymbol # type: ignore

def decompile(func: Function, style = "decompile"):
     # Initialize decompiler
    decompiler = DecompInterface()
        
    # Set decompiler options
    options = DecompileOptions()
    decompiler.setOptions(options)
    
    decompiler.toggleSyntaxTree(True)
    decompiler.toggleCCode(True)
    decompiler.toggleJumpLoads(True)
    decompiler.toggleParamMeasures(True)
    decompiler.setSimplificationStyle(style)
    
    decompiler.openProgram(getCurrentProgram())

    # Decompile
    monitor = ConsoleTaskMonitor()
    results = decompiler.decompileFunction(func, 30, monitor)  # 30 second timeout

    decompiler.closeProgram()

    return results


from rewriter import FunctionRewriter
from tokenizer import Tokenizer
import subprocess

def test(addr):
    func = currentProgram.getFunctionManager().getFunctionAt(flat_api.toAddr(addr))
    r = decompile(func, "decompile")
    fw = FunctionRewriter(r)
    fnew = fw.rewrite_function(Tokenizer(r.getCCodeMarkup()))

    print("============= OLD ===============")
    print(r.getDecompiledFunction().getC())

    print("============= NEW ===============")
    ps = subprocess.Popen(["clang-format"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    print(ps.communicate(fnew.replace("\n\n", ""))[0])

#test(0x401000)
#test(0x00401040)
test(0x00401060)