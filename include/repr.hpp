#ifndef REPR_HPP
#define REPR_HPP

#include <iostream>
#include <sstream>
#include <type_traits>

// forward declaration
namespace repr_impl
{
using std::enable_if;
using std::is_function;

template <typename T> void repr_stream(std::ostream&, const T&);
} // namespace repr_impl

template <typename T> std::string repr(const T& x)
{
    std::ostringstream out;
    repr_impl::repr_stream(out, x);
    return out.str();
}

namespace repr_impl
{
template <int n> struct overload_priority;

template <> struct overload_priority<100>
{
};

template <int n> struct overload_priority : public overload_priority<n + 1>
{
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

// any pointer type
template <typename T>
void repr_stream(std::ostream& out, T* const& x, overload_priority<1>)
{
    if (x == nullptr)
        out << "nullptr";
    else
        out << repr(*x);
}

// ostream-printable
template <typename T, typename = decltype(std::cout << val<T>())>
void repr_stream(std::ostream& out, const T& x, overload_priority<2>)
{
    out << x;
}

// iterable (container) of pairs; print like a map
template <typename T, typename = decltype(val<T>().begin()->first),
          typename = decltype(val<T>().begin()->second)>
void repr_stream(std::ostream& out, const T& xs, overload_priority<3>)
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
void repr_stream(std::ostream& out, const T& xs, overload_priority<4>)
{
    bool needs_comma = false;
    out << "[";

    for (const auto& x : xs) {
        if (needs_comma)
            out << ", ";

        out << repr(x);
        needs_comma = true;
    }

    out << "]";
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
