#include <Core/StringBuilder.h>
#include <string.h>

StringBuilder::StringBuilder()
    : m_length(0)
{
}

StringBuilder::~StringBuilder()
{
}

void StringBuilder::append(const char c)
{
    ensure_capacity(m_length + 1);
    m_bytes[m_length] = c;
    ++m_length;
}

void StringBuilder::append(const StringView& string_view)
{
    if (string_view.length() == 0) {
        return;
    }

    ensure_capacity(m_length + string_view.length());

    memcpy(&m_bytes[m_length], string_view.data(), string_view.length());
    m_length += string_view.length();
}

void StringBuilder::clear()
{
    m_bytes.clear();
    m_length = 0;
}

String StringBuilder::to_string() const
{
    return String(reinterpret_cast<const char*>(m_bytes.bytes()), m_length);
}

void StringBuilder::ensure_capacity(size_t capacity)
{
    if (capacity <= m_bytes.capacity()) {
        return;
    }

    m_bytes.grow(capacity);
}
