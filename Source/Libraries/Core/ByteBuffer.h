#pragma once

#include <Core/Types.h>
#include <stdlib.h>

class ByteBuffer {
public:
    explicit ByteBuffer(size_t capacity = 1);

    ByteBuffer(const ByteBuffer&);
    ByteBuffer(ByteBuffer&&);

    ByteBuffer& operator=(const ByteBuffer&);
    ByteBuffer& operator=(ByteBuffer&&);

    ~ByteBuffer();

    const u8& operator[](size_t) const;
    u8& operator[](size_t);

    void grow(size_t capacity);
    const u8* bytes() const;
    size_t capacity() const;

    void clear();

private:
    u8* m_bytes;
    size_t m_capacity;
};
