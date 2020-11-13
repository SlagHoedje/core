#include <Core/StringView.h>

StringView::StringView(const char* c_string)
    : m_inner(c_string)
    , m_length(strlen(c_string))
{
}

StringView::StringView(const char* c_string, size_t length)
    : m_inner(c_string)
    , m_length(length)
{
}

StringView::StringView(const String& string)
    : m_inner(string.data())
    , m_length(string.length())
{
}

StringView::StringView(const StringView& other)
    : m_inner(other.m_inner)
    , m_length(other.m_length)
{
}

StringView::StringView(StringView&& other)
    : m_inner(other.m_inner)
    , m_length(other.m_length)
{
}

StringView& StringView::operator=(const StringView& other)
{
    m_inner = other.m_inner;
    m_length = other.m_length;

    return *this;
}

StringView& StringView::operator=(StringView&& other)
{
    m_inner = other.m_inner;
    m_length = other.m_length;

    return *this;
}

StringView::~StringView()
{
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

size_t StringView::length() const
{
    return m_length;
}

const char* StringView::data() const
{
    return m_inner;
}

StringView StringView::substring_view(size_t start, size_t length) const
{
    ASSERT(start + length <= m_length, "substring out of range");

    return StringView(m_inner + start, length);
}
