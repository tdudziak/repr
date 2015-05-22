A template-based, LLVM-enabled pretty-printer.

# Usage

Include `repr.hpp` in your project and use the template function `repr()` to
convert anything into an `std::string`. If you include the file after any
LLVM header it will support LLVM classes automagically.

# Features

 * Uses a set of heuristics to find a good human-readable representation.
 * Supports all containers that implement `begin()` and `end()`.
 * Prints label names of LLVM basic blocks instead of their contents.
 * Will work on anything that implements an `ostream` or `llvm::raw_ostream`
   `operator<<`.
 * Automatically follows pointers (including smart pointers) but doesn't
   dereference null pointers (prints `nullptr` instead).
 * Prints containers of characters like strings, this supporting many of the
   different crazy string-like objects.
 * Can be also used in non-LLVM projects.

# Example

Following C++14 code:

```cpp
#include <vector>
#include <map>
#include <memory>
#include <repr.hpp>

int main()
{
    std::map<const char*, std::unique_ptr<std::vector<int>>> stl_madness;
    (void)stl_madness["empty"];
    auto uptr = std::make_unique<std::vector<int>>();
    uptr->push_back(1);
    uptr->push_back(2);
    uptr->push_back(3);
    stl_madness["one_two_three"] = std::move(uptr);
    std::cout << repr(stl_madness) << std::endl;
}
```

prints:

```
{"empty": nullptr, "one_two_three": [1, 2, 3]}
```
