#ifndef REPR_HPP
#define REPR_HPP

#include <iostream>
#include <sstream>
#include <type_traits>
#include <algorithm>
#include <functional>

#include <llvm/Support/raw_ostream.h>

// forward declaration
namespace repr_impl
{
template <typename T> void repr_stream(std::ostream&, const T&);
} // namespace repr_impl

template <typename T> std::string repr(const T& x)
{
    std::ostringstream out;
    repr_impl::repr_stream(out, x);

    auto not_space = std::not1(std::ptr_fun<int, int>(std::isspace));
    std::string result = out.str();
    result.erase(result.begin(),
                 std::find_if(result.begin(), result.end(), not_space));
    result.erase(std::find_if(result.rbegin(), result.rend(), not_space).base(),
                 result.end());

    return result;
}

namespace repr_impl
{
using std::enable_if;
using std::is_function;
using std::is_same;
using std::remove_cv;
using std::remove_extent;

template <int n> struct overload_priority;

template <> struct overload_priority<100>
{
};

template <int n> struct overload_priority : public overload_priority<n + 1>
{
};

template <typename T> struct is_string_like
{
    static const bool value =
        is_same<T, char*>::value || is_same<T, const char*>::value ||
        is_same<typename remove_extent<T>::type, char>::value ||
        is_same<typename remove_extent<T>::type, const char>::value ||
        is_same<T, std::string>::value;
};

// Used in decltype(...) SFINAE guards to provide a value of type T. Not
// implemented anywhere.
template <typename T> T val();

// function type (NOT std::function)
// Has to come before pointers as function types are infinitely-dereferencable
// pointer-like things.
template <typename T,
          typename = typename enable_if<is_function<T>::value>::type>
void repr_stream(std::ostream& out, const T& x, overload_priority<0>)
{
    out << "<function@" << &x << ">";
}

// string-like: char*, const char*, char[], and std::string
template <typename T,
          typename = typename enable_if<is_string_like<T>::value>::type>
void repr_stream(std::ostream& out, const T& x, overload_priority<1>)
{
    out << "\"" << x << "\"";
}

// pointers dumb and smart
template <typename T, typename = decltype(*val<T>()),
          typename = decltype(val<T>() == nullptr)>
void repr_stream(std::ostream& out, const T& x, overload_priority<2>)
{
    if (x == nullptr)
        out << "nullptr";
    else
        out << repr(*x);
}

// LLVM nameable values
// It's tempting to just provide a non-template overload for llvm::Value& but
// it might mess with overload resolution and overload_priority.
template <typename T, typename = decltype(val<T&>().getName().str()),
          typename = decltype(val<llvm::raw_ostream&>() << val<T&>())>
void repr_stream(std::ostream& out, const T& x, overload_priority<3>)
{
    std::string name = x.getName().str();

    if (name.size() > 0) {
        out << name;
    } else {
        std::string result;
        llvm::raw_string_ostream raw(result);
        raw << x;
        out << result;
    }
}

// ostream-printable
template <typename T, typename = decltype(std::cout << val<T>())>
void repr_stream(std::ostream& out, const T& x, overload_priority<4>)
{
    std::ios::fmtflags oldflags(out.flags());
    out << std::boolalpha << x;
    out.flags(oldflags);
}

// iterable (container) of pairs; print like a map
template <typename T, typename = decltype(val<T>().begin()->first),
          typename = decltype(val<T>().begin()->second)>
void repr_stream(std::ostream& out, const T& xs, overload_priority<5>)
{
    bool needs_comma = false;
    out << "{";

    for (const auto& x : xs) {
        if (needs_comma)
            out << ", ";

        out << repr(x.first) << ": " << repr(x.second);
        needs_comma = true;
    }

    out << "}";
}

// iterable
template <typename T, typename = decltype(val<T>().begin())>
void repr_stream(std::ostream& out, const T& xs, overload_priority<6>)
{
    bool needs_brackets = false;
    std::vector<std::string> contents;

    for (const auto& x : xs) {
        std::string repr_x = repr(x);

        bool x_needs_brackets = false;
        for (char c : repr_x) {
            if (std::isspace(c) || c == ',')
                x_needs_brackets = true;
        }

        // bracketing possibly not needed if contents are already delimited
        if (repr_x.size() >= 2) {
            char a = repr_x[0];
            char b = repr_x[repr_x.size()-1];

            if (a == '{' && b == '}')
                x_needs_brackets = false;

            if (a == '[' && b == ']')
                x_needs_brackets = false;
        }

        needs_brackets = needs_brackets || x_needs_brackets;
        contents.push_back(std::move(repr_x));
    }

    bool needs_comma = false;
    out << "[";
    for (const std::string& x : contents) {
        if (needs_comma)
            out << ", ";

        if (needs_brackets)
            out << "<" << x << ">";
        else
            out << x;

        needs_comma = true;
    }
    out << "]";
}

// LLVM objects that don't have getName but can be printed to a raw_ostream
template <typename T,
          typename = decltype(val<llvm::raw_ostream&>() << val<T>())>
void repr_stream(std::ostream& out, const T& x, overload_priority<7>)
{
    std::string result;
    llvm::raw_string_ostream raw(result);
    raw << x;
    out << result;
}

// other: just print the address
template <typename T>
void repr_stream(std::ostream& out, const T& x, overload_priority<100>)
{
    out << "<" << &x << ">";
}

// dispatch to one of the overloads above
template <typename T> void repr_stream(std::ostream& out, const T& x)
{
    repr_stream(out, x, overload_priority<0>());
}
} // namespace repr_impl

#endif
