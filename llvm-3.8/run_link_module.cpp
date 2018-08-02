#include <llvm/Pass.h>
#include <llvm/IR/PassManager.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/Support/MemoryBuffer.h"
#include <algorithm>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Transforms/IPO.h"
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <iostream>
#include <string>
#include <llvm/Linker/Linker.h>
#include <memory>
#include <llvm/ExecutionEngine/RuntimeDyld.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/DynamicLibrary.h>

using namespace llvm;
static void test() {
    throw 1;
}
int main() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    llvm::LLVMContext &Context = llvm::getGlobalContext();
    llvm::SMDiagnostic Err;
    std::unique_ptr<llvm::Module> Mod = llvm::parseIRFile("test.ll", Err, Context);

    std::unique_ptr<llvm::RTDyldMemoryManager> MemMgr(new llvm::SectionMemoryManager());

    llvm::Function* f = Mod->getFunction("exec");
    // Build engine with JIT
    std::string err;
    llvm::EngineBuilder factory(std::move(Mod));
    factory.setErrorStr(&err);
    factory.setEngineKind(llvm::EngineKind::JIT);
    // factory.setUseMCJIT(true);
    // factory.setMCJITMemoryManager(MemMgr);
    llvm::ExecutionEngine *m_EE = factory.create();

    llvm::sys::DynamicLibrary::AddSymbol("_Z4testv", reinterpret_cast<void*>(test));


    m_EE->finalizeObject();

    void* poi = m_EE->getPointerToFunction(f);
    void (*exec)(void*) = reinterpret_cast<void (*)(void*)>(poi); 

    try {
        exec(NULL);
    } catch (int e) {
        std::cout << "catched " << e << std::endl;
    }
    return 0;
}
