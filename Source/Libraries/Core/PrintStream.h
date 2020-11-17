#pragma once

#include <Core/Types.h>
#include <stdarg.h>

class PrintStream {
public:
    inline void print() { }

    template <typename T, typename... A>
    void print(const T& value, const A&... values)
    {
        append(value);
        print(values...);
    }

    template <typename... A>
    void println(const A&... values)
    {
        print(values..., '\n');
    }

private:
    void printf(const char*, ...);
    virtual void vprintf(const char*, va_list) = 0;

    void append(char);
    void append(const char*);

    void append(bool);
    void append(short);
    void append(unsigned short);
    void append(int);
    void append(unsigned int);
    void append(long);
    void append(unsigned long);
    void append(long long);
    void append(unsigned long long);

    template <typename T>
    void append(const T* value)
    {
        printf("%p", value);
    }
};
