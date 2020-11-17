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

inline FilePrintStream cout()
{
    return FilePrintStream(stdout);
}
