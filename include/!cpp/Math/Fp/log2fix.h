//# [https://github.com/dmoulding/log2fix]
/*
	The MIT License (MIT)

	Copyright (c) 2015 Dan Moulding

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#pragma once

#include <stdint.h>
#include <stddef.h>

#include <!cpp/TestRunner.h>
namespace Math { namespace Fp {  

namespace Log2fix { namespace details {
	template<class TArg> struct DoublePrec;
	template<> struct DoublePrec<uint8_t> { typedef uint16_t Ret; };
	template<> struct DoublePrec<uint16_t> { typedef uint32_t Ret; };
	#ifdef UINT64_MAX
		template<> struct DoublePrec<uint32_t> { typedef uint64_t Ret; };
	#endif
	
	template<class TArg> struct Consts;
	#ifdef UINT64_MAX
		template<> struct Consts<uint32_t> { enum { INV_LOG2_E_Q1DOT_N_SUB_1 = UINT64_C(0x58b90bfc), INV_LOG2_10_Q1DOT_N_SUB_1 =  UINT64_C(0x268826a1) }; };
	#endif
} }

template<class TArg>
TArg log2fix(TArg x, size_t precision) {
	// This implementation is based on Clay. S. Turner's fast binary logarithm
	// algorithm[1].
	
	TArg b = TArg(1) << (precision - 1);
	TArg y = 0;
	
	// static_assert(0 < precision && precision < sizeof(TArg) * 8 - 1);
	
	if(x == 0) {
		return TArg(-1); // represents negative infinity
	}
	
	while(x < TArg(1) << precision) {
		x <<= 1;
		y -= TArg(1) << precision;
	}
	
	while((TArg(2) << precision) <= x ) {
		x >>= 1;
		y += TArg(1) << precision;
	}
	
	typename Log2fix::details::DoublePrec<TArg>::Ret z = x;
	
	for(size_t i = 0; i < precision; i++) {
		z = z * z >> precision;
		if(z >= (TArg(2) << precision)) {
			z >>= 1;
			y += b;
		}
		b >>= 1;
	}
	
	return y;
}

template<class TArg>
TArg logfix(TArg x, size_t precision) {
	typedef typename Log2fix::details::DoublePrec<TArg>::Ret T2Arg; 
	T2Arg t = T2Arg(log2fix(x, precision)) * Log2fix::details::Consts<TArg>::INV_LOG2_E_Q1DOT_N_SUB_1;
	
	return t >> (sizeof(TArg) * 8 - 1);
}

template<class TArg>
TArg log10fix(TArg x, size_t precision) {
	typedef typename Log2fix::details::DoublePrec<TArg>::Ret T2Arg; 
	T2Arg t = T2Arg(log2fix(x, precision)) * Log2fix::details::Consts<TArg>::INV_LOG2_10_Q1DOT_N_SUB_1;
	
	return t >> (sizeof(TArg) * 8 - 1);
}

// [1] C. S. Turner,  "A Fast Binary Logarithm Algorithm", IEEE Signal
//     Processing Mag., pp. 124,140, Sep. 2010.

} }

example("log2fix") {
	using Math::Fp::logfix;
	
	assert_eq(logfix(uint32_t(0x62000000), 32 - 5), 0x140B512E);
}
