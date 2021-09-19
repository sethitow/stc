#include "compile.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include "llvm/ADT/Optional.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include "lexer.hpp"
#include "parse.hpp"

int compile(std::string filename)
{

    std::stringstream strFile;
    {
        std::ifstream inFile(filename);
        strFile << inFile.rdbuf();
    }

    auto tokens = tokenize(strFile.str());

    {
        std::ofstream outFile(filename + ".tok");
        for (const auto &tok : tokens.to_vec())
        {
            outFile << tok.to_string() << "\n";
        }
    }

    auto ast = parse(tokens);

    auto CPU = "generic";
    auto Features = "";

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();

    LLVMInitializeX86TargetInfo();
    LLVMInitializeX86Target();
    LLVMInitializeX86TargetMC();
    LLVMInitializeX86AsmParser();
    LLVMInitializeX86AsmPrinter();

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
    // Print an error and exit if we couldn't find the requested target. This generally occurs if we've forgotten to initialise the TargetRegistry or we have a bogus target triple.
    if (!Target)
    {
        llvm::errs() << Error;
        return EXIT_FAILURE;
    }

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    auto ctx = CodeGenContext(filename);
    ctx.llvm_module->setDataLayout(TargetMachine->createDataLayout());
    ctx.llvm_module->setTargetTriple(TargetTriple);
    ast->codegen(ctx);

    {
        std::error_code EC;
        llvm::raw_fd_ostream ll_dest(filename + ".ll", EC, llvm::sys::fs::F_None);
        if (EC)
        {
            llvm::errs() << "Could not open file: " << EC.message();
            return EXIT_FAILURE;
        }
        ctx.llvm_module->print(ll_dest, nullptr);
        ll_dest.flush();
    }

    {
        std::error_code EC;
        llvm::raw_fd_ostream o_dest(filename + ".o", EC, llvm::sys::fs::F_None);
        if (EC)
        {
            llvm::errs() << "Could not open file: " << EC.message();
            return 1;
        }
        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;

        if (TargetMachine->addPassesToEmitFile(pass, o_dest, nullptr, FileType))
        {
            llvm::errs() << "TargetMachine can't emit a file of this type";
            return 1;
        }

        pass.run(*ctx.llvm_module);
        o_dest.flush();
    }

    return EXIT_SUCCESS;
}
