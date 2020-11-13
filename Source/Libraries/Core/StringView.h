#pragma once

#include <Core/String.h>
#include <Core/Types.h>

class StringView {
public:
    StringView(const char*);
    StringView(const char*, size_t length);
    StringView(const String&);

    StringView(const StringView&);
    StringView(StringView&&);

    StringView& operator=(const StringView&);
    StringView& operator=(StringView&&);

    ~StringView();

    size_t length() const;
    const char* data() const;

    StringView substring_view(size_t start, size_t length) const;

private:
    const char* m_inner;
    size_t m_length;
};
