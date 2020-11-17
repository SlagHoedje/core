#pragma once

#include <Core/PrintStream.h>
#include <stdio.h>

class FilePrintStream : public PrintStream {
public:
    FilePrintStream(FILE*);

private:
    void vprintf(const char*, va_list) override;

    FILE* m_file;
};

ALWAYS_INLINE FilePrintStream cout()
{
    return FilePrintStream(stdout);
}

ALWAYS_INLINE FilePrintStream cerr()
{
    return FilePrintStream(stderr);
}
