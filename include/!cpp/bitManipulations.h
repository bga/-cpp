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
#include <stdint.h>
#include <!cpp/common.h>

#ifdef _BV
  #undef _BV
#endif
#if !BGA__IS_EMPTY_MACRO(BGA__MAYBE_CONSTEXPR)
  constexpr inline uintmax_t _BV(unsigned bitNo) {
    return uintmax_t(1) << bitNo;
  }
#else
  #define _BV(bitNoArg) (uintmax_t(1) << (bitNoArg))
#endif

#define bitsCountToMask(bitsCountArg) ((uintmax_t(1) << (bitsCountArg)) - 1)
#define hasBit(vArg, bitNumberArg) (((vArg) & _BV((bitNumberArg))))
#define hasBitMask(vArg, bitNumberArg) (((vArg) & (bitNumberArg)))

template<class TArg>
inline TArg clearBit(TArg& vArg, unsigned bitNumberArg) {
  vArg &= ~(TArg(1) << bitNumberArg);
  return vArg;
}
template<class TArg, class T2Arg>
inline TArg clearBitMask(TArg& vArg, T2Arg maskArg) {
  vArg &= maskArg;
  return vArg;
}

template<class TArg>
inline TArg setBit(TArg& vArg, unsigned bitNumberArg) {
  vArg |= (TArg(1) << bitNumberArg);
  return vArg;
}
template<class TArg, class T2Arg>
inline TArg setBitMask(TArg& vArg, T2Arg maskArg) {
  vArg |= maskArg;
  return vArg;
}

template<class TArg>
inline TArg toggleBit(TArg& vArg, unsigned bitNumberArg) {
  return (vArg ^= (TArg(1) << bitNumberArg));
}
template<class TArg, class T2Arg>
TArg toggleBitMask(TArg& vArg, T2Arg maskArg) {
  vArg ^= maskArg;
  return vArg;
}

template<class TArg>
inline TArg setBitValue(TArg& vArg, unsigned bitNumberArg, bool isSet) {
  return (isSet) ? setBit(vArg, bitNumberArg) : clearBit(vArg, bitNumberArg);
}

template<class TArg, class T2Arg, class T3Arg>
inline TArg setBitMaskedValues(TArg& destArg, unsigned destShiftArg, T2Arg maskArg, T3Arg srcArg) {
  destArg &= ~(maskArg << destShiftArg);
  destArg |= ((srcArg & maskArg) << destShiftArg);
  return destArg;
}

#define makeU32leFrom4U8(b3, b2, b1, b0) (((FU32)(b0)) | (((FU32)(b1)) << 8) | (((FU32)(b2)) << 16) | (((FU32)(b3)) << 24))
#define makeU32beFrom4U8(b3, b2, b1, b0) (((FU32)(b3)) | (((FU32)(b2)) << 8) | (((FU32)(b1)) << 16) | (((FU32)(b0)) << 24))
#define makeU32leFrom2U16le(b1, b0) (((FU32)(b1)) | (((FU32)(b0)) << 16))
#define makeU32leFrom2U16be(b1, b0) (((FU32)(staticSwapBytes16(b1))) | (((FU32)(staticSwapBytes16(b0))) << 16))
#define makeU32beFrom2U16be(b1, b0) (((FU32)(b0)) | (((FU32)(b1)) << 16))
#define makeU32beFrom2U16le(b1, b0) (((FU32)(staticSwapBytes16(b0))) | (((FU32)(staticSwapBytes16(b1))) << 16))

namespace BitRotate {
  template<typename TArg> struct getTotalBitsCount;
  template<> struct getTotalBitsCount<uint8_t> {
    static const int value = 8;
  };
  template<> struct getTotalBitsCount<uint16_t> {
    static const int value = 16;
  };
  template<> struct getTotalBitsCount<uint32_t> {
    static const int value = 32;
  };
  #ifdef UINT64_MAX
		template<> struct getTotalBitsCount<uint64_t> {
			static const int value = 64;
		};
	#endif
} // namespace BitRotate

template<typename TArg> inline TArg bitRotateLeft(TArg v, unsigned int n) {
  using namespace BitRotate;
  const int totalBitsCount = getTotalBitsCount<TArg>::value;
  return (v << n) | (v >> (totalBitsCount - n));
}
template<typename TArg> inline TArg bitRotateRight(TArg v, unsigned int n) {
  using namespace BitRotate;
  const int totalBitsCount = getTotalBitsCount<TArg>::value;
  return (v >> n) | (v << (totalBitsCount - n));
}

//# [https://stackoverflow.com/a/776523]
#if defined(__x86_64__) || defined(__i386__)
#ifdef _MSC_VER
  #include <intrin.h>
#else
  #include <x86intrin.h>  // Not just <immintrin.h> for compilers other than icc
#endif


template<> inline uint32_t bitRotateLeft(uint32_t v, unsigned int n) {
  return _rotl(v, n);  // gcc, icc, msvc.  Intel-defined.
}
template<> inline uint32_t bitRotateRight(uint32_t v, unsigned int n) {
  return _rotr(v, n);  // gcc, icc, msvc.  Intel-defined.
}

#if 0
#ifdef UINT64_MAX
  template<> inline uint64_t bitRotateLeft(uint64_t v, unsigned int n) {
    return _rotl64(v, n);  // gcc, icc, msvc.  Intel-defined.
  }
  template<> inline uint64_t bitRotateRight(uint64_t v, unsigned int n) {
    return _rotr64(v, n);  // gcc, icc, msvc.  Intel-defined.
  }
#endif
#endif
#endif

template<typename TArg> inline TArg bitRotate(TArg v, int n) {
  using namespace BitRotate;
  return (n < 0) ? bitRotateRight(v, -n) : bitRotateLeft(v, n);
}

template<typename IntArg>
IntArg changeByteEndian(IntArg x);

#define staticSwapBytes16(x) ((U16(U8((x) >> 0)) << 8) | (U16(U8((x) >> 8)) << 8))

inline uint16_t changeByteEndian(uint16_t x) {
  return staticSwapBytes16(x);
}

#define staticSwapBytes32(x) ((U32(U8((x) >> 0)) << 24) | (U32(U8((x) >> 8)) << 16) | (U32(U8((x) >> 16)) << 8) | (U32(U8((x) >> 24)) << 0))
inline uint32_t changeByteEndian(uint32_t x) {
  return staticSwapBytes32(x);
}

#ifdef UINT64_MAX
  #define staticSwapBytes64(x) (U64(U8((x) >> 0)) << 56) | (U64(U8((x) >> 8)) << 48) | (U64(U8((x) >> 16)) << 40) | (U64(U8((x) >> 24)) << 32) | (U64(U8((x) >> 32)) << 24) | (U64(U8((x) >> 40)) << 16) | (U64(U8((x) >> 48)) << 8) | (U64(U8((x) >> 56)) << 0);
  inline uint64_t changeByteEndian(uint64_t x) {
    return staticSwapBytes64(x);
  }
#endif


#define isPowerOf2(vArg) (((vArg) & ((vArg) - 1)) == 0)
template<typename IntArg, typename MaxIntArg>
inline IntArg cycleInc(IntArg& vArg, const MaxIntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg += 1;
    vArg &= maxVArg - 1;
  }
  else {
    vArg += 1;
    if(vArg == maxVArg) {
      vArg = 0;
    }
    else {

    }
  }
  return vArg;
}

template<typename IntArg>
inline void cycleDec(IntArg& vArg, const IntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg -= 1;
    vArg &= maxVArg - 1;
  }
  else {
    if(vArg == 0) {
      vArg = maxVArg - 1;
    }
    else {
      vArg += 1;
    }
  }
}


template<uintmax_t x> struct IntToMaskHelperClass {
  #define GEN_SHIFT(aArg, bArg, shiftArg) static const uintmax_t BGA__CONCAT(x, bArg) = BGA__CONCAT(x, aArg) | (BGA__CONCAT(x, aArg) >> ((((shiftArg) / 4) <= sizeof(uintmax_t)) ? (shiftArg) : 0));

  static const uintmax_t x1 = x;

  GEN_SHIFT(1, 2, 32)
  GEN_SHIFT(2, 3, 16)
  GEN_SHIFT(3, 4,  8)
  GEN_SHIFT(4, 5,  4)
  GEN_SHIFT(5, 6,  2)
  GEN_SHIFT(6, 7,  1)

  #undef GEN_SHIFT

  static const uintmax_t result = x7;
};

#define intToMaskConstExpr(xArg) IntToMaskHelperClass<(xArg)>::result

#define intToMaskConstExpr(xArg) IntToMaskHelperClass<(xArg)>::result

#if 0
  enum {
    x = constExpr,
    xLog2 = log2Static(x)
  };
#endif

#define log2Static_g(xArg, shiftArg, TArg) ((xArg) <= (TArg(1) << (shiftArg))) ?  (shiftArg) :

//# { var s = ""; for(var i = 0; i < 64; i += 1) s+= "".concat("log2Static_g(xArg, ", i, ", TArg) "); copy(s); }
#define log2Static0_32(xArg, TArg) log2Static_g(xArg, 0, TArg) log2Static_g(xArg, 1, TArg) log2Static_g(xArg, 2, TArg) log2Static_g(xArg, 3, TArg) log2Static_g(xArg, 4, TArg) log2Static_g(xArg, 5, TArg) log2Static_g(xArg, 6, TArg) log2Static_g(xArg, 7, TArg) log2Static_g(xArg, 8, TArg) log2Static_g(xArg, 9, TArg) log2Static_g(xArg, 10, TArg) log2Static_g(xArg, 11, TArg) log2Static_g(xArg, 12, TArg) log2Static_g(xArg, 13, TArg) log2Static_g(xArg, 14, TArg) log2Static_g(xArg, 15, TArg) log2Static_g(xArg, 16, TArg) log2Static_g(xArg, 17, TArg) log2Static_g(xArg, 18, TArg) log2Static_g(xArg, 19, TArg) log2Static_g(xArg, 20, TArg) log2Static_g(xArg, 21, TArg) log2Static_g(xArg, 22, TArg) log2Static_g(xArg, 23, TArg) log2Static_g(xArg, 24, TArg) log2Static_g(xArg, 25, TArg) log2Static_g(xArg, 26, TArg) log2Static_g(xArg, 27, TArg) log2Static_g(xArg, 28, TArg) log2Static_g(xArg, 29, TArg) log2Static_g(xArg, 30, TArg) log2Static_g(xArg, 31, TArg)

#define log2Static_32_64(xArg, TArg) log2Static_g(xArg, 32, TArg) log2Static_g(xArg, 33, TArg) log2Static_g(xArg, 34, TArg) log2Static_g(xArg, 35, TArg) log2Static_g(xArg, 36, TArg) log2Static_g(xArg, 37, TArg) log2Static_g(xArg, 38, TArg) log2Static_g(xArg, 39, TArg) log2Static_g(xArg, 40, TArg) log2Static_g(xArg, 41, TArg) log2Static_g(xArg, 42, TArg) log2Static_g(xArg, 43, TArg) log2Static_g(xArg, 44, TArg) log2Static_g(xArg, 45, TArg) log2Static_g(xArg, 46, TArg) log2Static_g(xArg, 47, TArg) log2Static_g(xArg, 48, TArg) log2Static_g(xArg, 49, TArg) log2Static_g(xArg, 50, TArg) log2Static_g(xArg, 51, TArg) log2Static_g(xArg, 52, TArg) log2Static_g(xArg, 53, TArg) log2Static_g(xArg, 54, TArg) log2Static_g(xArg, 55, TArg) log2Static_g(xArg, 56, TArg) log2Static_g(xArg, 57, TArg) log2Static_g(xArg, 58, TArg) log2Static_g(xArg, 59, TArg) log2Static_g(xArg, 60, TArg) log2Static_g(xArg, 61, TArg) log2Static_g(xArg, 62, TArg) log2Static_g(xArg, 63, TArg)


#if 0
#elif defined(UINT64_MAX)
  #define log2Static(xArg) (log2Static0_32(xArg, UINT64_C) log2Static_32_64(xArg, UINT64_C) (-1))
#else
  #define log2Static(xArg) (log2Static0_32(xArg, UINT32_C) (-1))
#endif


