#pragma once

#include <Windows.h>

inline bool operator==(const POINT& p1, const POINT& p2) { return p1.x == p2.x && p1.y == p2.y; }
inline bool operator!=(const POINT& p1, const POINT& p2) { return !(p1 == p2); }
inline POINT operator+(const POINT& p1, const POINT& p2) { return { p1.x + p2.x, p1.y + p2.y }; }
inline POINT operator-(const POINT& p1, const POINT& p2) { return { p1.x - p2.x, p1.y - p2.y }; }
inline POINT operator*(const POINT& p1, float f) { return { static_cast<long>(p1.x * f),static_cast<long>(p1.y * f) }; }