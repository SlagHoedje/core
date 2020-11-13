#pragma once

#define ASSERT(x, msg) static_cast<bool>(x) ? void(0) : __assert_failed(__FILE__, __LINE__, #x, msg)
#define ASSERT_UNREACHABLE(msg) ASSERT(false, msg)

void __assert_failed(const char* file, int line, const char* expression, const char* msg);
