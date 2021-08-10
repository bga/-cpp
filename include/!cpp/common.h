/*
  Copyright 2020 Bga <bga.email@gmail.com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#pragma once

#include <!cpp/common_macro.h>

#include <!cpp/wrapper/cstdint>
#include <!cpp/wrapper/cstddef>
#include <!cpp/wrapper/type_traits>

#if defined(__IAR_SYSTEMS_ICC__ )
  #include "common.iar.before.h"
#endif

#if defined(__GNUC__ )
  #include "common.gcc.before.h"
#endif



//#define override

typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
#ifdef UINT64_MAX
  typedef int64_t I64;
  typedef uint64_t U64;
#endif

typedef int_least8_t LI8;
typedef uint_least8_t LU8;
typedef int_least16_t LI16;
typedef uint_least16_t LU16;
typedef int_least32_t LI32;
typedef uint_least32_t LU32;
#ifdef UINT64_MAX
  typedef int_least64_t LI64;
  typedef uint_least64_t LU64;
#endif

typedef int_fast8_t FI8;
typedef uint_fast8_t FU8;
typedef int_fast16_t FI16;
typedef uint_fast16_t FU16;
typedef int_fast32_t FI32;
typedef uint_fast32_t FU32;
#ifdef UINT64_MAX
  typedef int_fast64_t FI64;
  typedef uint_fast64_t FU64;
#endif

typedef int Z;
typedef int Int;
typedef unsigned int UInt;
typedef intmax_t IntMax;
typedef uintmax_t UIntMax;

typedef void Void;
typedef bool Bool;

#define BGA__GEN_STATIC_ASSERT_XX_HELPER(nameArg, exprArg) \
	template<IntMax a, IntMax b> struct nameArg { \
		struct _ {  }; \
		typedef typename std::conditional<(exprArg), int, _>::type type; \
	};
#define BGA__STATIC_ASSERT_XX(nameArg, aArg, bArg) \
	struct BGA__UNIQUE_NAME { typename nameArg<(aArg), (bArg)>::type dummy() { return 1; } }

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_lt_helper, a < b)
#define static_assert_lt(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_lt_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_lte_helper, a <= b)
#define static_assert_lte(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_lte_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_gt_helper, b < a)
#define static_assert_gt(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_gt_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_gte_helper, b <= a)
#define static_assert_gte(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_gte_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_eq_helper, a == b)
#define static_assert_eq(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_eq_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_neq_helper, a != b)
#define static_assert_neq(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_neq_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_hasBit_helper, a & (UIntMax(1) << b))
#define static_assert_hasBit(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_hasBit_helper, (aArg), (bArg))

#if 0
  static_assert_test(1, x == 1 || x == 2); //# OK
  static_assert_test(2, x == 1 || x == 2); //# OK
  static_assert_test(3, x == 1 || x == 2); //# FAIL
#endif
BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_test_helper, !!b)
#define static_assert_test(aArg, testAExprArg) struct BGA__UNIQUE_NAME { static const IntMax x = (aArg); BGA__STATIC_ASSERT_XX(static_assert_test_helper, x, (testAExprArg)); }


template<typename TArg> TArg Math_abs(const TArg& x) {
  #define BGA__MATH__ABS(x) (((x) < 0) ? -(x) : (x))
  return BGA__MATH__ABS(x);
}
template<typename AArg, typename BArg> AArg Math_min(const AArg& a, const BArg& b) {
  #define BGA__MATH__MIN(a, b) (((a) < (b)) ? (a) : (b))
  return BGA__MATH__MIN(a, b);
}
template<typename AArg, typename BArg> AArg Math_max(const AArg& a, const BArg& b) {
  #define BGA__MATH__MAX(a, b) (((a) < (b)) ? (b) : (a))
  return BGA__MATH__MAX(a, b);
}
template<typename AArg, typename XArg, typename BArg> XArg Math_clamp(const AArg& a, const XArg& x, const BArg& b) {
  #define BGA__MATH__CLAMP(a, x, b) BGA__MATH__MIN(BGA__MATH__MAX(x, a), b)
  return Math_min(Math_max(x, a), b);
}
template<typename TArg, typename AArg, typename BArg> TArg Math_lerp(const TArg& t, const AArg& a, const BArg& b) {
  #define BGA__MATH__LERP(t, a, b) ((t) * ((b) - (a)) + (a))
  return BGA__MATH__LERP(t, a, b);
}


#if 0
#include <!cpp/wrapper/cstdlib>
Int randomInt(Int a,  Int b) {
  return a + rand() % (b - a + 1);
}
#endif

typedef ptrdiff_t Size;

template<class Type, Size n>
BGA__MAYBE_CONSTEXPR Size arraySize( Type (&)[n] ) {
  return n;
}

template<typename T> void swap(T &a, T &b) {
  T temp = a; a = b; b = temp;
}

#ifndef nop
  inline void nop() {

  }
#endif

#if 0
int x;
BGA__RUN {
  std::cout << "BGA__RUN" << std::endl;
}
#endif
#define BGA__RUN BGA__RUN_ID_IMPL(BGA__UNIQUE_ID)

#define BGA__RUN_ID_IMPL(idArg) BGA__RUN_IMPL(BGA__CONCAT(Run, idArg), BGA__CONCAT(runMethod, idArg), BGA__CONCAT(runInstance, idArg))
#define BGA__RUN_IMPL(_classNameArg, _methodNameArg, _instanceNameArg) \
void _methodNameArg(); \
class _classNameArg { \
  public: \
  _classNameArg() { \
    _methodNameArg(); \
  } \
} _instanceNameArg; \
void _methodNameArg()

//# macro for inspecting constant expr at compile time. Still produces error
//# TODO use warning
#if 0
  static_print(F_CPU / (1 << adcPrescaler))
#endif
/* BGA__PRAGMA(message(__FILE__ ":" BGA__STR(__LINE__) " " BGA__STR(exprArg) " =")) */ \
#ifdef BGA__ENABLE_STATIC_PRINT
  #define static_print(constExpr) \
    char (*BGA__CONCAT(__inspectInt_, __LINE__))[constExpr] = 1;
#else
  #define static_print(constExpr)
#endif
