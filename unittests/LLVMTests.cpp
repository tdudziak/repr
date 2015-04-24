#include <memory>

#include <llvm/AsmParser/Parser.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

#include <gtest/gtest.h>
#include <repr.hpp>

using namespace llvm;

std::unique_ptr<llvm::Module> parseAssembly(const std::string& assembly)
{
    std::unique_ptr<llvm::Module> module(
        new llvm::Module("Module", llvm::getGlobalContext()));

    llvm::SMDiagnostic error;
    bool success = ParseAssemblyString(assembly.c_str(), module.get(), error,
                                       module->getContext()) == module.get();

    std::string ErrMsg;
    llvm::raw_string_ostream OS(ErrMsg);
    error.print("", OS);

    // A failure here means that the test itself is buggy.
    if (!success)
        llvm::report_fatal_error(OS.str().c_str());

    return module;
}

std::string foo_src = "define i32 @foo(i32 %a) #0 {\n"
                      "bb:\n"
                      "   br label %loop\n"
                      "loop:\n"
                      "   %x = phi i32 [%a, %bb], [%x_next, %loop]\n"
                      "   %x_next = add i32 %x, 1\n"
                      "   br label %loop\n"
                      "}\n";

std::string bar_src = "define i32 @bar(i32 %a) #0 {\n"
                      "bb:\n"
                      "%0 = add i32 %a, 1\n"
                      "%1 = add i32 %0, 1\n"
                      "ret i32 %1\n"
                      "}\n";

TEST(LLVMTests, ModuleFunction)
{
    auto module = parseAssembly(foo_src + bar_src);
    llvm::Function* foo = module->begin();

    EXPECT_EQ("foo", repr(foo));
    EXPECT_EQ("[foo, bar]", repr(module));
}

TEST(LLVMTests, BasicBlock)
{
    auto module = parseAssembly(foo_src);
    llvm::Function* foo = module->begin();
    EXPECT_EQ("[bb, loop]", repr(foo->getBasicBlockList()));
}

TEST(LLVMTests, Instruction)
{
    auto module = parseAssembly(bar_src);
    llvm::Function* bar = module->begin();
    llvm::BasicBlock* bb = bar->begin();

    EXPECT_EQ("bb", repr(bb));

    // TODO: some extra delimiters to avoid the confusion with commas?
    EXPECT_EQ("[%0 = add i32 %a, 1, %1 = add i32 %0, 1, ret i32 %1]",
              repr(bb->getInstList()));

    llvm::Instruction* inst = &bb->getInstList().front();
    EXPECT_EQ("%0 = add i32 %a, 1", repr(inst));
}
