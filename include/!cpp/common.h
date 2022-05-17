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
  typedef int64_t I64_or_void;
  typedef uint64_t U64_or_void;
#else
  typedef void I64_or_void;
  typedef void U64_or_void;
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
  typedef int_least64_t LI64_or_void;
  typedef uint_least64_t LU64_or_void;
#else
  typedef void LI64_or_void;
  typedef void LU64_or_void;
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
  typedef int_fast64_t FI64_or_void;
  typedef uint_fast64_t FU64_or_void;
#else
  typedef void FI64_or_void;
  typedef void FU64_or_void;
#endif

typedef int Z;
typedef int Int;
typedef unsigned int UInt;
typedef intmax_t IntMax;
typedef uintmax_t UIntMax;

typedef void Void;
typedef bool Bool;

//# missed in standard csdtint. Add for unification
#ifndef UINT8_MIN
  #define UINT8_MIN UINT8_C(0)
#endif
#ifndef UINT16_MIN
  #define UINT16_MIN UINT16_C(0)
#endif
#ifndef UINT32_MIN
  #define UINT32_MIN UINT32_C(0)
#endif
#ifdef UINT64_MAX
  #ifndef UINT64_MIN
    #define UINT64_MIN UINT64_C(0)
  #endif
#endif

namespace Bga {

template<class TArg, class DefaultTArg>
struct void_to_default {
  typedef TArg type;
};
template<class DefaultTArg>
struct void_to_default<void, DefaultTArg> {
  typedef DefaultTArg type;
};


template<class T> 
struct int_type_traits;

#ifdef _MIN
  #pragma push_macro("_MIN")
  #undef _MIN
#endif

#ifdef _MAX
  #pragma push_macro("_MAX")
  #undef _MAX
#endif

#define BGA__GEN_INT_TYPE_TRAIT(intPrefixArg, intPrefixUpperArg, numArg) \
  template<> struct int_type_traits<BGA__CONCAT3(intPrefixArg, numArg, _t)> { \
    typedef typename ::std::make_signed<BGA__CONCAT3(intPrefixArg, numArg, _t)>::type signed_type; \
    typedef typename ::std::make_unsigned<BGA__CONCAT3(intPrefixArg, numArg, _t)>::type unsigned_type; \
    \
    typedef BGA__CONCAT4(intPrefixArg, _fast, numArg, _t) fast_type; \
    typedef typename ::std::make_signed<fast_type>::type int_fast_type; \
    typedef typename ::std::make_unsigned<fast_type>::type uint_fast_type; \
    \
    typedef BGA__CONCAT4(intPrefixArg, _least, numArg, _t) least_type; \
    typedef typename ::std::make_signed<least_type>::type int_least_type; \
    typedef typename ::std::make_unsigned<least_type>::type uint_least_type; \
    \
    static const BGA__CONCAT3(intPrefixArg, numArg, _t) min_value =  BGA__CONCAT3(intPrefixUpperArg, numArg, _MIN); \
    static const BGA__CONCAT3(intPrefixArg, numArg, _t) max_value =  BGA__CONCAT3(intPrefixUpperArg, numArg, _MAX); \
    \
    static const int bit_width = sizeof(BGA__CONCAT3(intPrefixArg, numArg, _t)) * 8; \
  } \
;

#define BGA__GEN_INT_TYPE_TRAIT__I_AND_U(numArg) \
  BGA__GEN_INT_TYPE_TRAIT(int, INT, numArg) \
  BGA__GEN_INT_TYPE_TRAIT(uint, UINT, numArg) \
;

BGA__GEN_INT_TYPE_TRAIT__I_AND_U(8);
BGA__GEN_INT_TYPE_TRAIT__I_AND_U(16);
BGA__GEN_INT_TYPE_TRAIT__I_AND_U(32);
#ifdef UINT64_MAX
  BGA__GEN_INT_TYPE_TRAIT__I_AND_U(64);
#endif

#undef BGA__GEN_INT_TYPE_TRAIT__I_AND_U
#undef BGA__GEN_INT_TYPE_TRAIT

#pragma pop_macro("_MAX")
#pragma pop_macro("_MIN")


template<unsigned bitWidthArg>
struct make_signed_from_bit_width {
  typedef typename ::std::conditional<bitWidthArg <= 8, I8, 
    typename ::std::conditional<bitWidthArg <= 16, I16, 
      typename ::std::conditional<bitWidthArg <= 32, I32, 
        typename ::std::conditional<bitWidthArg <= 64, I64_or_void, 
          void
        >::type
      >::type
    >::type
  >::type type;
};

template<unsigned bitWidthArg>
struct make_unsigned_from_bit_width {
  typedef typename ::std::make_unsigned<typename make_signed_from_bit_width<bitWidthArg>::type>::type type;
};

template<class IntArg>
struct make_signed_half_int_nocv {
  typedef typename make_signed_from_bit_width<int_type_traits<IntArg>::bit_width / 2>::type type;
};
template<class IntArg>
struct make_unsigned_half_int_nocv {
  typedef typename ::std::make_unsigned<typename make_signed_half_int_nocv<IntArg>::type>::type type;
};
template<class IntArg>
struct make_signed_double_int_nocv {
  typedef typename make_signed_from_bit_width<int_type_traits<IntArg>::bit_width * 2>::type type;
};
template<class IntArg>
struct make_unsigned_double_int_nocv {
  typedef typename ::std::make_unsigned<typename make_signed_double_int_nocv<IntArg>::type>::type type;
};

template<class IntArg>
struct make_half_int_nocv {
  typedef typename ::std::conditional< ::std::is_signed<IntArg>::value, 
    typename make_signed_half_int_nocv<IntArg>::type, 
    typename make_unsigned_half_int_nocv<IntArg>::type 
  >::type type;
};

template<class IntArg>
struct make_double_int_nocv {
  typedef typename ::std::conditional< ::std::is_signed<IntArg>::value, 
    typename make_signed_double_int_nocv<IntArg>::type, 
    typename make_unsigned_double_int_nocv<IntArg>::type 
  >::type type;
};

} //# namespace

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

#if 0
  static_assert_type_eq(void, void) //# OK 
  static_assert_type_eq(void, int) //# FAIL 
#endif
template<class AArg, class BArg> 
struct static_assert_type_eq_helper {

};
template<class AArg> 
struct static_assert_type_eq_helper<AArg, AArg> {
	static_assert_type_eq_helper(int) {  }
};

#define static_assert_type_eq(AArg, BArg) \
	struct BGA__UNIQUE_NAME { void dummy() { const static_assert_type_eq_helper< AArg, BArg > x(1); } } \
;

#if 0
  static_assert_type_neq(void, int) //# OK 
  static_assert_type_neq(void, void) //# FAIL 
#endif
template<class AArg, class BArg> 
struct static_assert_type_neq_helper {
	static_assert_type_neq_helper(int) {  }
};
template<class AArg> 
struct static_assert_type_neq_helper<AArg, AArg> {

};

#define static_assert_type_neq(AArg, BArg) \
	struct BGA__UNIQUE_NAME { void dummy() { const static_assert_type_neq_helper< AArg, BArg > x(1); } } \
;


template<typename TArg> BGA__MAYBE_CONSTEXPR TArg Math_abs(const TArg& x) {
  #define BGA__MATH__ABS(x) (((x) < 0) ? -(x) : (x))
  return BGA__MATH__ABS(x);
}
template<typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR AArg Math_min(const AArg& a, const BArg& b) {
  #define BGA__MATH__MIN(a, b) (((a) < (b)) ? (a) : (b))
  return BGA__MATH__MIN(a, b);
}
template<typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR AArg Math_max(const AArg& a, const BArg& b) {
  #define BGA__MATH__MAX(a, b) (((a) < (b)) ? (b) : (a))
  return BGA__MATH__MAX(a, b);
}
template<typename AArg, typename XArg, typename BArg> BGA__MAYBE_CONSTEXPR XArg Math_clamp(const AArg& a, const XArg& x, const BArg& b) {
  #define BGA__MATH__CLAMP(a, x, b) BGA__MATH__MIN(BGA__MATH__MAX(x, a), b)
  return Math_min(Math_max(x, a), b);
}
template<typename TArg, typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR TArg Math_lerp(const TArg& t, const AArg& a, const BArg& b) {
  #define BGA__MATH__LERP(t, a, b) ((t) * ((b) - (a)) + (a))
  return BGA__MATH__LERP(t, a, b);
}

namespace details {
template<int nArg, unsigned powArg> struct Pow { static const IntMax value = nArg * Pow<nArg, powArg - 1>::value; };
template<int nArg> struct Pow<nArg, 0> { static const IntMax value = 1; };
} //# namespace
#define BGA__MATH__POW_INT(nArg, powArg) details::Pow<(nArg), (powArg)>::value 


#if 0
#include <!cpp/wrapper/cstdlib>
Int randomInt(Int a,  Int b) {
  return a + rand() % (b - a + 1);
}
#endif

typedef ptrdiff_t SSize;
typedef typename ::std::make_unsigned<SSize>::type Size;

template<class Type, Size n>
BGA__MAYBE_CONSTEXPR Size arraySize( Type (&)[n] ) {
  return n;
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
    char (*BGA__CONCAT(__inspectInt_, BGA__UNIQUE_ID))[constExpr] = 1;
#else
  #define static_print(constExpr)
#endif
