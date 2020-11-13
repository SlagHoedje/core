#pragma once

template <typename, typename>
inline constexpr static bool IsSame = false;

template <typename T>
inline constexpr static bool IsSame<T, T> = true;
