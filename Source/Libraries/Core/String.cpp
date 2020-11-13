#include <Core/Assert.h>
#include <Core/String.h>
#include <Core/StringView.h>
#include <string.h>

String::String()
    : m_inner(nullptr)
    , m_length(0)
{
}

String::String(const char* c_string)
    : m_length(strlen(c_string))
{
    m_inner = new char[m_length];
    memcpy(m_inner, c_string, m_length);
}

String::String(const char* c_string, size_t length)
    : m_inner(new char[length])
    , m_length(length)
{
    memcpy(m_inner, c_string, m_length);
}

String::String(const StringView& string_view)
    : m_length(string_view.length())
{
    m_inner = new char[m_length];
    memcpy(m_inner, string_view.data(), m_length);
}

String::String(const String& other)
    : m_length(other.m_length)
{
    if (other.m_inner != nullptr) {
        m_inner = new char[m_length];
        memcpy(m_inner, other.m_inner, m_length);
    } else {
        m_inner = nullptr;
    }
}

String::String(String&& other)
{
    m_inner = other.m_inner;
    m_length = other.m_length;

    other.m_inner = nullptr;
    other.m_length = 0;
}

String& String::operator=(const String& other)
{
    if (&other == this) {
        return *this;
    }

    delete[] m_inner;

    m_length = other.m_length;

    if (other.m_inner != nullptr) {
        m_inner = new char[m_length];
        memcpy(m_inner, other.m_inner, m_length);
    } else {
        m_inner = nullptr;
    }

    return *this;
}

String& String::operator=(String&& other)
{
    if (&other == this) {
        return *this;
    }

    delete[] m_inner;

    m_inner = other.m_inner;
    m_length = other.m_length;

    other.m_inner = nullptr;
    other.m_length = 0;

    return *this;
}

String& String::operator=(const char* c_string)
{
    delete[] m_inner;

    m_length = strlen(c_string);
    m_inner = new char[m_length];
    memcpy(m_inner, c_string, m_length);

    return *this;
}

String::~String()
{
    delete[] m_inner;
}

bool String::operator==(const char* other) const
{
    if (m_length != strlen(other)) {
        return false;
    }

    return !strncmp(m_inner, other, m_length);
}

bool String::operator!=(const char* other) const
{
    return !(*this == other);
}

bool String::operator==(const StringView& other) const
{
    if (m_length != other.length()) {
        return false;
    }

    return !strncmp(m_inner, other.data(), m_length);
}

bool String::operator!=(const StringView& other) const
{
    return !(*this == other);
}

bool String::operator==(const String& other) const
{
    if (m_length != other.length()) {
        return false;
    }

    return !strncmp(m_inner, other.data(), m_length);
}

bool String::operator!=(const String& other) const
{
    return !(*this == other);
}

size_t String::length() const
{
    return m_length;
}

bool String::is_null() const
{
    return m_inner == nullptr;
}

const char* String::data() const
{
    return m_inner;
}

String String::substring(size_t start, size_t length) const
{
    ASSERT(!is_null(), "can't take substring of a null string");
    ASSERT(start + length <= m_length, "substring out of range");

    return String(m_inner + start, length);
}

StringView String::substring_view(size_t start, size_t length) const
{
    ASSERT(start + length <= m_length, "substring out of range");

    return StringView(m_inner + start, length);
}

Vector<String> String::split(char delim, bool ignore_empty) const
{
    (void)ignore_empty;

    Vector<String> out;

    // FIXME: Change this to a for each loop sometime?
    size_t start = 0;
    for (size_t i = 0; i < m_length; ++i) {
        char current = m_inner[i];

        if (current == delim) {
            if (!ignore_empty || start != i) {
                out.append(substring(start, i - start));
            }

            start = i + 1;
        }
    }

    out.append(substring(start, m_length - start));

    return out;
}

Vector<StringView> String::split_view(char delim, bool ignore_empty) const
{
    (void)ignore_empty;

    Vector<StringView> out;

    // FIXME: Change this to a for each loop sometime?
    size_t start = 0;
    for (size_t i = 0; i < m_length; ++i) {
        char current = m_inner[i];

        if (current == delim) {
            if (!ignore_empty || start != i) {
                out.append(substring_view(start, i - start));
            }

            start = i + 1;
        }
    }

    if (!ignore_empty || start != m_length) {
        out.append(substring_view(start, m_length - start));
    }

    return out;
}

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    for (size_t i = 0; i < string.length(); ++i) {
        stream << string.m_inner[i];
    }

    return stream;
}
