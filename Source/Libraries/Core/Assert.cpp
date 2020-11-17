#include <Core/Stdio.h>
#include <stdlib.h>

void __assert_failed(const char* file, int line, const char* expression, const char* msg)
{
    cerr().println(file, ':', line, ": Assertion '", expression, "' failed: ", msg);
    abort();
}
