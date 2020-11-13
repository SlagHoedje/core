#pragma once

#include <Core/ByteBuffer.h>
#include <Core/String.h>
#include <Core/StringView.h>

class StringBuilder {
public:
    StringBuilder();

    // FIXME: Maybe we need these in the future
    StringBuilder(const StringBuilder&) = delete;
    StringBuilder(StringBuilder&&) = delete;

    ~StringBuilder();

    void append(const char);
    void append(const StringView&);

    template <typename D, typename C>
    void join(const D& delim, const C& collection)
    {
        bool first = true;

        for (const auto& value : collection) {
            if (first) {
                first = false;
            } else {
                append(delim);
            }

            append(value);
        }
    }

    void repeat(char, int amount);

    void clear();

    String to_string() const;

private:
    void ensure_capacity(size_t);

    ByteBuffer m_bytes;
    size_t m_length;
};
