#include <memory>

#include <llvm/AsmParser/Parser.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>

#include <gtest/gtest.h>
#include <repr.hpp>

#include "test_config.h"

using namespace llvm;

std::unique_ptr<llvm::Module> parseAssembly(const std::string& assembly)
{
    std::unique_ptr<llvm::Module> module;
    llvm::SMDiagnostic error;

#if LLVM35
    module.reset(new llvm::Module("Module", llvm::getGlobalContext()));

    auto res = llvm::ParseAssemblyString(assembly.c_str(), module.get(), error,
                                         module->getContext());

    assert(res == module.get());
#elif LLVM36
    module = llvm::parseAssemblyString(assembly.c_str(), error,
                                       llvm::getGlobalContext());
    assert(module != nullptr);
#endif

    return module;
}

std::unique_ptr<llvm::Module> getTestModule(const std::string& name)
{
    llvm::SMDiagnostic error;
    std::unique_ptr<llvm::Module> module;

#if LLVM35
    module.reset(llvm::ParseAssemblyFile(TEST_DATA_DIR "/" + name + "-3.5.ll",
                                         error, llvm::getGlobalContext()));
#elif LLVM36
    module = llvm::parseAssemblyFile(TEST_DATA_DIR "/" + name + "-3.6.ll",
                                     error, llvm::getGlobalContext());
#endif

    assert(module.get() != nullptr);
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

    EXPECT_EQ("[<%0 = add i32 %a, 1>, <%1 = add i32 %0, 1>, <ret i32 %1>]",
              repr(bb->getInstList()));

    llvm::Instruction* inst = &bb->getInstList().front();
    EXPECT_EQ("%0 = add i32 %a, 1", repr(inst));
}

TEST(LLVMTests, DebugLocations)
{
    auto module = getTestModule("debug_unopt");
    llvm::Function* func = module->begin();

    auto itr = func->begin();
    llvm::BasicBlock* bb = itr++;
    llvm::BasicBlock* bb3 = itr++;
    llvm::BasicBlock* bb5 = itr++;
    llvm::BasicBlock* bb8 = itr++;

    EXPECT_EQ("bb@(debug.c:1)", repr(bb));
    EXPECT_EQ("bb3@(debug.c:6)", repr(bb3));
    EXPECT_EQ("bb5@(debug.c:8)", repr(bb5));
    EXPECT_EQ("bb8@(debug.c:10)", repr(bb8));
}

TEST(LLVMTests, StringRef)
{
    std::string foo = "Hello, world!";
    llvm::StringRef sref(foo);
    EXPECT_EQ("\"Hello, world!\"", repr(sref));
}
