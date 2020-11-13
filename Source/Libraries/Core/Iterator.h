#pragma once

#include <Core/Types.h>

template <typename C, typename V>
class Iterator {
public:
    Iterator(C& container, size_t index)
        : m_container(container)
        , m_index(index)
    {
    }

    bool operator==(const Iterator& other) const
    {
        return m_index == other.m_index;
    }

    bool operator!=(const Iterator& other) const
    {
        return m_index != other.m_index;
    }

    bool operator<(const Iterator& other) const
    {
        return m_index < other.m_index;
    }

    bool operator>(const Iterator& other) const
    {
        return m_index > other.m_index;
    }

    bool operator<=(const Iterator& other) const
    {
        return m_index <= other.m_index;
    }

    bool operator>=(const Iterator& other) const
    {
        return m_index >= other.m_index;
    }

    Iterator operator+(ptrdiff_t diff) const
    {
        return Iterator(m_container, m_index + diff);
    }

    Iterator operator-(ptrdiff_t diff) const
    {
        return Iterator(m_container, m_index - diff);
    }

    Iterator operator++()
    {
        ++m_index;

        return *this;
    }

    Iterator operator++(int)
    {
        ++m_index;

        return Iterator(m_container, m_index - 1);
    }

    Iterator operator--()
    {
        --m_index;

        return *this;
    }

    Iterator operator--(int)
    {
        --m_index;

        return Iterator(m_container, m_index + 1);
    }

    const V& operator*() const
    {
        return m_container[m_index];
    }

    V& operator*()
    {
        return m_container[m_index];
    }

    const V* operator->() const
    {
        return &m_container[m_index];
    }

    V* operator->()
    {
        return &m_container[m_index];
    }

private:
    C& m_container;
    size_t m_index;
};
