#pragma once

#include <Core/Assert.h>
#include <Core/Iterator.h>
#include <Core/Move.h>
#include <Core/Types.h>
#include <stdlib.h>
#include <string.h>

#include <new>

template <typename T>
class Vector {
public:
    using ConstIterator = Iterator<const Vector, const T>;
    using Iterator = Iterator<Vector, T>;

    Vector()
        : m_elements(nullptr)
        , m_size(0)
        , m_capacity(0)
    {
    }

    Vector(size_t capacity)
        : m_elements(static_cast<T*>(malloc(sizeof(T) * capacity)))
        , m_size(0)
        , m_capacity(capacity)
    {
    }

    Vector(const Vector& other)
        : m_elements(static_cast<T*>(malloc(sizeof(T) * other.m_capacity)))
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
    {
        for (size_t i = 0; i < m_size; ++i) {
            m_elements[i] = T(other.m_elements[i]);
        }
    }

    Vector(Vector&& other)
        : m_elements(other.m_elements)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
    {
        other.m_elements = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector& operator=(const Vector& other)
    {
        if (&other == this) {
            return *this;
        }

        clear();

        m_elements = static_cast<T*>(malloc(sizeof(T) * other.m_capacity));
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        for (size_t i = 0; i < m_size; ++i) {
            m_elements[i] = T(other.m_elements[i]);
        }

        return *this;
    }

    Vector& operator=(Vector&& other)
    {
        if (&other == this) {
            return *this;
        }

        clear();

        m_elements = other.m_elements;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_elements = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    ~Vector()
    {
        clear();
    }

    const T& operator[](size_t index) const
    {
        ASSERT(index < m_size, "index out of range");

        return m_elements[index];
    }

    T& operator[](size_t index)
    {
        ASSERT(index < m_size, "index out of range");

        return m_elements[index];
    }

    ConstIterator begin() const
    {
        return ConstIterator(*this, 0);
    }

    ConstIterator end() const
    {
        return ConstIterator(*this, m_size);
    }

    Iterator begin()
    {
        return Iterator(*this, 0);
    }

    Iterator end()
    {
        return Iterator(*this, m_size);
    }

    void append(const T& element)
    {
        insert(m_size, element);
    }

    void append(T&& element)
    {
        insert(m_size, move(element));
    }

    void prepend(const T& element)
    {
        insert(0, element);
    }

    void prepend(T&& element)
    {
        insert(0, move(element));
    }

    T pop_back()
    {
        T element = move(m_elements[m_size - 1]);

        remove(m_size - 1);

        return element;
    }

    void insert(size_t index, const T& element)
    {
        insert(index, T(element));
    }

    void insert(size_t index, T&& element)
    {
        ASSERT(index <= m_size, "index out of range");

        ensure_capacity(m_size + 1);

        if (index != m_size) {
            for (size_t i = m_size; i > index; --i) {
                new (&m_elements[i]) T(move(m_elements[i - 1]));
            }
        }

        new (&m_elements[index]) T(move(element));

        ++m_size;
    }

    void remove(size_t index)
    {
        ASSERT(index < m_size, "index out of range");

        m_elements[index].~T();

        if (index == m_size - 1) {
            --m_size;
            return;
        }

        for (size_t i = index; i < m_size - 1; ++i) {
            new (&m_elements[i]) T(move(m_elements[i + 1]));
        }

        --m_size;
    }

    void clear()
    {
        for (size_t i = 0; i < m_size; ++i) {
            m_elements[i].~T();
        }

        free(m_elements);

        m_elements = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

private:
    void ensure_capacity(size_t new_capacity)
    {
        if (new_capacity <= m_capacity) {
            return;
        }

        T* new_elements = static_cast<T*>(malloc(sizeof(T) * new_capacity));

        if (m_elements != nullptr) {
            memcpy(new_elements, m_elements, sizeof(T) * m_size);
            free(m_elements);
        }

        m_capacity = new_capacity;
        m_elements = new_elements;
    }

    T* m_elements;
    size_t m_size;
    size_t m_capacity;
};
