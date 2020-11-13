#include <iostream>
#include <stddef.h>

void __assert_failed(const char* file, int line, const char* expression, const char* msg)
{
    std::cerr << file << ':' << line << ": Assertion '" << expression << "' failed: " << msg << '\n';
    abort();
}
