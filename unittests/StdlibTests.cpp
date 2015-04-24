#include <gtest/gtest.h>

#include <repr.hpp>

TEST(StdlibTests, StdString)
{
    std::string foo = "foobar";
    EXPECT_EQ(repr(foo), "foobar");
}

TEST(StdlibTests, CString)
{
    char* foo1 = (char*) "foobar";
    const char* foo2 = foo1;
    volatile char* foo3 = foo1;
    const volatile char* foo4 = foo1;

    EXPECT_EQ("foobar", repr(foo1));
    EXPECT_EQ("foobar", repr(foo2));
    EXPECT_EQ("foobar", repr(foo3));
    EXPECT_EQ("foobar", repr(foo4));
}

TEST(StdlibTests, CharArray)
{
    const char foo[] = "foobar";
    EXPECT_EQ("foobar", repr(foo));
}
