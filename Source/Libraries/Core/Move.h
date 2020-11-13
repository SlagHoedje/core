#pragma once

template <typename T>
T&& move(T& t)
{
    return static_cast<T&&>(t);
}

template <typename T>
T&& move(T&& t)
{
    return static_cast<T&&>(t);
}
