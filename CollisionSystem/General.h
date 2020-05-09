#pragma once

#include <math.h>
#include <time.h>

const double EPS = 1e-6;
const double PI = 4.0 * atan(1.0);

template<typename T1, typename T2>
constexpr auto max(T1 a, T2 b) { 
	return a > b ? a : b; 
}

template<typename T1, typename T2>
constexpr auto min(T1 a, T2 b) {
	return a < b ? a : b;
}

template<typename T1, typename T2, typename T3>
constexpr auto getInRange(T1 l, T2 v, T3 r) {
	return (l <= v ? (v <= r ? v : r) : l);
}

template<typename T1, typename T2, typename T3>
constexpr bool isInRange(T1 l, T2 v, T3 r) { 
	return (l <= v) && (v <= r); 
}
