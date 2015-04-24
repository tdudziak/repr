#include <gtest/gtest.h>

#include <repr.hpp>

TEST(StdlibTests, StdString)
{
    std::string foo = "foobar";
    EXPECT_EQ(repr(foo), "foobar");
}

TEST(StdlibTests, CString)
{
    const char* foo = "foobar";
    EXPECT_EQ(repr(foo), "foobar");
}

TEST(StdlibTests, CharArray)
{
    const char foo[] = "foobar";
    EXPECT_EQ(repr(foo), "foobar");
}
