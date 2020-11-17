#include <Core/Stdio.h>

#include <stdarg.h>

FilePrintStream::FilePrintStream(FILE* file)
    : m_file(file)
{
}

void FilePrintStream::vprintf(const char* format, va_list arg)
{
    vfprintf(m_file, format, arg);
}
