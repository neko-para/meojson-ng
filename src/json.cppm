module;

#define MEOJSON_MODULE

#include <algorithm>
#include <array>
#include <bit>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#ifndef MEOJSON_DISABLE_PACKED_BYTES
#if defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP)
#include <emmintrin.h>
#if defined(__SSE4_1__) || defined(__AVX2__) || defined(_MSC_VER)
#include <smmintrin.h>
#endif
#elif defined(__ARM_NEON) || defined(_M_ARM) || defined(_M_ARM64)
#if defined(MEOJSON_ENABLE_NEON)
#include <arm_neon.h>
#endif
#endif
#endif

export module meojson;

#define MEOJSON_EXPORT export

#include "json.hpp"
