#include <vector>
#include <set>
#include <map>
#include <memory>
#include <tuple>

#include <gtest/gtest.h>
#include <repr.hpp>

using namespace std;

TEST(StdlibTests, StdString)
{
    string foo = "foobar";
    EXPECT_EQ(repr(foo), "\"foobar\"");
}

TEST(StdlibTests, CString)
{
    char* foo1 = (char*) "foobar";
    const char* foo2 = foo1;
    const char* emp = "";

    EXPECT_EQ("\"foobar\"", repr(foo1));
    EXPECT_EQ("\"foobar\"", repr(foo2));
    EXPECT_EQ("\"\"", repr(emp));

    EXPECT_EQ("\"foobar\"", repr("foobar"));
    EXPECT_EQ("\"\"", repr(""));

    EXPECT_EQ("\"x\"", repr('x'));
}

TEST(StdlibTests, Vector)
{
    vector<int> iv = {1,2,3,4,5};
    vector<int> emp = {};
    vector<vector<int>> vov = {{1,2}, {3,4}};

    EXPECT_EQ(repr(iv), "[1, 2, 3, 4, 5]");
    EXPECT_EQ(repr(emp), "[]");
    EXPECT_EQ(repr(vov), "[[1, 2], [3, 4]]");
}

TEST(StdlibTests, Map)
{
    map<int, string> omap = {{1, "one"}, {2, "two"}, {3, "three"}};
    vector<pair<int, string>> vmap(omap.begin(), omap.end());

    EXPECT_EQ(repr(omap), "{1: \"one\", 2: \"two\", 3: \"three\"}");
    EXPECT_EQ(repr(vmap), "{1: \"one\", 2: \"two\", 3: \"three\"}");
}

TEST(StdlibTests, Pointers)
{
    int one = 1;
    EXPECT_EQ("1", repr(&one));

    unique_ptr<int> uptr(new int {1});
    EXPECT_EQ("1", repr(uptr));
    uptr.reset();
    EXPECT_EQ("nullptr", repr(uptr));

    shared_ptr<int> sptr(new int {1});
    EXPECT_EQ("1", repr(sptr));
    sptr.reset();
    EXPECT_EQ("nullptr", repr(sptr));
}

TEST(StdlibTests, Booleans)
{
    EXPECT_EQ("1", repr((int) true));
    EXPECT_EQ("0", repr((int) false));
    EXPECT_EQ("false", repr(false));
    EXPECT_EQ("true", repr(true));
}

TEST(StdlibTests, Tuple)
{
    EXPECT_EQ("()", repr(std::make_tuple()));
    EXPECT_EQ("(1)", repr(std::make_tuple(1)));
    EXPECT_EQ("(1, 2)", repr(std::make_tuple(1, 2)));

    std::tuple<int, int, int> foo = std::make_tuple(1, 2, 3);
    const std::tuple<int, int, int>& bar(foo);

    EXPECT_EQ("(1, 2, 3)", repr(foo));
    EXPECT_EQ("(1, 2, 3)", repr(bar));
}

TEST(StdlibTests, Array)
{
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    EXPECT_EQ("(1, 2, 3, 4, 5)", repr(arr));
}
