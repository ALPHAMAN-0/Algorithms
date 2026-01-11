// Custom stdc++.h header for Clang with C++20/C++23 support
// Organized by categories for better readability

// Make this header safe to include multiple times
#pragma once
#ifndef VSCODE_STDCXX_H
#define VSCODE_STDCXX_H

// C++ Input/Output
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

// C++ Containers
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <array>
#include <tuple>
#include <bitset>
#include <valarray>
#include <span>

// C++ Strings
#include <string>
#include <string_view>

// C++ Algorithms & Utilities
#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <numeric>
#include <limits>
#include <locale>
#include <ranges>

// C++ Memory Management
#include <memory>
#include <new>

// C++ Type Support
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <concepts>
#include <initializer_list>

// C++ Modern Features
#include <filesystem>
#include <optional>
#include <variant>
#include <any>
#include <compare>

// C++ Error Handling
#include <exception>
#include <stdexcept>
#include <system_error>
#include <cassert>

// C++ Concurrency
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <execution>

// C++ Time
#include <chrono>
#include <ctime>

// C++ Random
#include <random>

// C++ Numerics & Math
#include <complex>
#include <numbers>
#include <bit>
#include <cmath>

// C Standard Library Wrappers
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>

// C++20 format (may not be fully implemented in all compilers yet)
// Prefer a safe detect: use __has_include when available, otherwise fall back
#if defined(__has_include)
#  if __has_include(<format>)
#    include <format>
#  endif
#elif defined(__cpp_lib_format)
#  include <format>
#endif

#endif // VSCODE_STDCXX_H
