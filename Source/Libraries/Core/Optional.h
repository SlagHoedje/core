#pragma once

#include <Core/Assert.h>
#include <Core/Move.h>
#include <Core/Types.h>

template <typename T>
class Optional {
public:
    Optional()
        : m_storage()
        , m_has_value(false)
    {
    }

    Optional(T&& value)
        : m_storage()
        , m_has_value(true)
    {
        new (slot()) T(move(value));
    }

    Optional(const T& value)
        : m_storage()
        , m_has_value(true)
    {
        new (slot()) T(value);
    }

    Optional(Optional&& other)
        : m_storage()
        , m_has_value(other.m_has_value)
    {
        if (m_has_value) {
            new (slot()) T(other.take());
        }
    }

    Optional(const Optional& other)
        : m_storage()
        , m_has_value(other.m_has_value)
    {
        if (m_has_value) {
            new (slot()) T(other.value());
        }
    }

    ~Optional()
    {
        clear();
    }

    void clear()
    {
        if (m_has_value) {
            value().~T();

            m_has_value = false;
        }
    }

    bool has_value() const
    {
        return m_has_value;
    }

    const T& value() const
    {
        ASSERT(m_has_value, "option does not contain a value");
        return *slot();
    }

    T& value()
    {
        ASSERT(m_has_value, "option does not contain a value");
        return *slot();
    }

    T take()
    {
        T released_value = move(value());
        clear();
        return released_value;
    }

private:
    const T* slot() const
    {
        return reinterpret_cast<const T*>(&m_storage);
    }

    T* slot()
    {
        return reinterpret_cast<T*>(&m_storage);
    }
    u8 m_storage[sizeof(T)];
    bool m_has_value;
};
