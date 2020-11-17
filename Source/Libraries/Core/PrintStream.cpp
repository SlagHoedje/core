#include <Core/PrintStream.h>

void PrintStream::printf(const char* format, ...)
{
    va_list arg;

    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
}

void PrintStream::append(char c)
{
    printf("%c", c);
}

void PrintStream::append(const char* c_string)
{
    printf(c_string);
}

void PrintStream::append(bool value)
{
    append(value ? "true" : "false");
}

void PrintStream::append(short value)
{
    printf("%d", value);
}

void PrintStream::append(unsigned short value)
{
    printf("%u", value);
}

void PrintStream::append(int value)
{
    printf("%d", value);
}

void PrintStream::append(unsigned int value)
{
    printf("%u", value);
}

void PrintStream::append(long value)
{
    printf("%d", value);
}

void PrintStream::append(unsigned long value)
{
    printf("%u", value);
}

void PrintStream::append(long long value)
{
    printf("%d", value);
}

void PrintStream::append(unsigned long long value)
{
    printf("%u", value);
}
