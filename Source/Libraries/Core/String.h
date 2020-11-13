#pragma once

#include <Core/Types.h>
#include <Core/Vector.h>
#include <iostream>

class StringView;

class String {
public:
    String();
    String(const char*);
    String(const char*, size_t length);
    explicit String(const StringView&);

    String(const String&);
    String(String&&);

    String& operator=(const String&);
    String& operator=(String&&);
    String& operator=(const char*);

    ~String();

    bool operator==(const char*) const;
    bool operator!=(const char*) const;

    bool operator==(const StringView&) const;
    bool operator!=(const StringView&) const;

    bool operator==(const String&) const;
    bool operator!=(const String&) const;

    size_t length() const;
    bool is_null() const;
    const char* data() const;

    String substring(size_t start, size_t length) const;
    StringView substring_view(size_t start, size_t length) const;

    Vector<String> split(char delim, bool ignore_empty = true) const;
    Vector<StringView> split_view(char delim, bool ignore_empty = true) const;

    friend std::ostream& operator<<(std::ostream&, const String&);

private:
    char* m_inner;
    size_t m_length;
};
