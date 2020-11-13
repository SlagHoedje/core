#include <Core/ByteBuffer.h>

#include <Core/Assert.h>
#include <string.h>

ByteBuffer::ByteBuffer(size_t capacity)
    : m_bytes(new u8[capacity])
    , m_capacity(capacity)
{
}

ByteBuffer::ByteBuffer(const ByteBuffer& other)
    : m_bytes(new u8[other.m_capacity])
    , m_capacity(other.m_capacity)
{
    memcpy(m_bytes, other.m_bytes, m_capacity);
}

ByteBuffer::ByteBuffer(ByteBuffer&& other)
    : m_bytes(other.m_bytes)
    , m_capacity(other.m_capacity)
{
    other.m_bytes = nullptr;
    other.m_capacity = 0;
}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& other)
{
    delete[] m_bytes;

    m_bytes = new u8[other.m_capacity];
    m_capacity = other.m_capacity;

    memcpy(m_bytes, other.m_bytes, m_capacity);

    return *this;
}

ByteBuffer& ByteBuffer::operator=(ByteBuffer&& other)
{
    delete[] m_bytes;

    m_bytes = other.m_bytes;
    m_capacity = 0;

    other.m_bytes = nullptr;
    other.m_capacity = 0;

    return *this;
}

ByteBuffer::~ByteBuffer()
{
    clear();
}

const u8& ByteBuffer::operator[](size_t index) const
{
    ASSERT(index < m_capacity, "index out of range");

    return m_bytes[index];
}

u8& ByteBuffer::operator[](size_t index)
{
    ASSERT(index < m_capacity, "index out of range");

    return m_bytes[index];
}

void ByteBuffer::grow(size_t capacity)
{
    ASSERT(capacity > m_capacity, "new capacity is lower than the old capacity");

    u8* new_bytes = new u8[capacity];

    if (m_bytes != nullptr) {
        memcpy(new_bytes, m_bytes, m_capacity);
        delete[] m_bytes;
    }

    m_bytes = new_bytes;
    m_capacity = capacity;
}

const u8* ByteBuffer::bytes() const
{
    return m_bytes;
}

size_t ByteBuffer::capacity() const
{
    return m_capacity;
}

void ByteBuffer::clear()
{
    delete[] m_bytes;
    m_bytes = nullptr;
    m_capacity = 0;
}
