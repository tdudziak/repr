#define ENABLE_REPR_LLVM
#include <repr.hpp>

#include <memory>
#include <sstream>

#include <llvm/AsmParser/Parser.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>

#include <gtest/gtest.h>

#include "test_config.h"

using namespace llvm;

std::unique_ptr<llvm::Module> parseAssembly(const std::string& assembly)
{
    std::unique_ptr<llvm::Module> module;
    llvm::SMDiagnostic error;

#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR == 5
    module.reset(new llvm::Module("Module", llvm::getGlobalContext()));

    auto res = llvm::ParseAssemblyString(assembly.c_str(), module.get(), error,
                                         module->getContext());

    assert(res == module.get());
#else
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

    std::ostringstream osstr;
    osstr << TEST_DATA_DIR << "/" << name << "-" << LLVM_VERSION_MAJOR << "."
          << LLVM_VERSION_MINOR << ".ll";
    std::string fname = osstr.str();

#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR == 5
    module.reset(
        llvm::ParseAssemblyFile(fname, error, llvm::getGlobalContext()));
#else
    module = llvm::parseAssemblyFile(fname, error, llvm::getGlobalContext());
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
    llvm::Function* foo = &*module->begin();

    EXPECT_EQ("foo", repr(foo));
    EXPECT_EQ("[foo, bar]", repr(module));
}

TEST(LLVMTests, BasicBlock)
{
    auto module = parseAssembly(foo_src);
    llvm::Function* foo = &*module->begin();
    EXPECT_EQ("[bb, loop]", repr(foo->getBasicBlockList()));
}

TEST(LLVMTests, Instruction)
{
    auto module = parseAssembly(bar_src);
    llvm::Function* bar = &*module->begin();
    llvm::BasicBlock* bb = &*bar->begin();

    EXPECT_EQ("bb", repr(bb));

    EXPECT_EQ("[<%0 = add i32 %a, 1>, <%1 = add i32 %0, 1>, <ret i32 %1>]",
              repr(bb->getInstList()));

    llvm::Instruction* inst = &bb->getInstList().front();
    EXPECT_EQ("%0 = add i32 %a, 1", repr(inst));
}

#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR > 5
TEST(LLVMTests, DebugLocations)
{
    auto module = getTestModule("debug_unopt");
    llvm::Function* func = &*module->begin();

    auto itr = func->begin();
    llvm::BasicBlock* bb = &*itr++;
    llvm::BasicBlock* bb3 = &*itr++;
    llvm::BasicBlock* bb5 = &*itr++;
    llvm::BasicBlock* bb8 = &*itr++;

    EXPECT_EQ("bb(debug.c:1)", repr(bb));
    EXPECT_EQ("bb3(debug.c:6)", repr(bb3));
    EXPECT_EQ("bb5(debug.c:8)", repr(bb5));
    EXPECT_EQ("bb8(debug.c:10)", repr(bb8));
}

TEST(LLVMTests, DebugValues)
{
    auto module = getTestModule("debug_ssa");
    auto& func = *module->begin();

    for (auto& bb : func) {
        for (auto& inst : bb) {
            if (inst.getName() == "tmp7") {
                EXPECT_EQ("tmp7(y@debug.c:8)", repr(inst));
            }
        }
    }
}
#endif

TEST(LLVMTests, StringRef)
{
    std::string foo = "Hello, world!";
    llvm::StringRef sref(foo);
    EXPECT_EQ("\"Hello, world!\"", repr(sref));
}

TEST(LLVMTests, Iterators)
{
    auto module = parseAssembly(foo_src);

    EXPECT_EQ("foo", repr(module->begin()));
    EXPECT_EQ("foo", repr(*module->begin()));
    EXPECT_EQ("foo", repr(&*module->begin()));
    EXPECT_EQ("bb", repr(module->begin()->begin()));
    EXPECT_EQ("bb", repr(*module->begin()->begin()));
    EXPECT_EQ("bb", repr(&*module->begin()->begin()));
    EXPECT_EQ("br label %loop", repr(module->begin()->begin()->begin()));
    EXPECT_EQ("br label %loop", repr(*module->begin()->begin()->begin()));
    EXPECT_EQ("br label %loop", repr(&*module->begin()->begin()->begin()));
}
