//# [https://github.com/dmoulding/log2fix]

/*
	To C++ convert by Bga
	
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

#include <!cpp/wrapper/cstdint>
#include <!cpp/wrapper/cstddef>
#include <!cpp/wrapper/type_traits>

#include <!cpp/TestRunner.h>
namespace Math { namespace Fp {  

namespace Log2fix { namespace details {
	template<class TArg> struct DoublePrec;
	template<> struct DoublePrec<uint8_t> { typedef uint16_t Ret; };
	template<> struct DoublePrec<int8_t> { typedef int16_t Ret; };
	template<> struct DoublePrec<uint16_t> { typedef uint32_t Ret; };
	template<> struct DoublePrec<int16_t> { typedef int32_t Ret; };
	#ifdef UINT64_MAX
		template<> struct DoublePrec<uint32_t> { typedef uint64_t Ret; };
		template<> struct DoublePrec<int32_t> { typedef int64_t Ret; };
	#endif

	template<class TArg> struct ToSigned;
	template<> struct ToSigned<uint8_t> { typedef int8_t Ret; };
	template<> struct ToSigned<uint16_t> { typedef int16_t Ret; };
	template<> struct ToSigned<uint32_t> { typedef int32_t Ret; };
	
	template<class TArg> struct Consts;
	template<> struct Consts<uint8_t> { enum { INV_LOG2_E_Q0DOT_N = UINT8_C(177), INV_LOG2_10_Q0DOT_N =  UINT8_C(77) }; };
	template<> struct Consts<uint16_t> { enum { INV_LOG2_E_Q0DOT_N = UINT16_C(45426), INV_LOG2_10_Q0DOT_N =  UINT16_C(19728) }; };
	#ifdef UINT64_MAX
		template<> struct Consts<uint32_t> { enum { INV_LOG2_E_Q0DOT_N = UINT32_C(2977044471), INV_LOG2_10_Q0DOT_N =  UINT32_C(1292913986) }; };
	#endif
} }

template<class TArg>
typename Log2fix::details::ToSigned<TArg>::Ret /* (max - precision).precision */ log2fix(TArg x, Size precision) {
	// This implementation is based on Clay. S. Turner's fast binary logarithm
	// algorithm[1].
	
	typedef typename Log2fix::details::ToSigned<TArg>::Ret STArg; 
	typedef typename Log2fix::details::DoublePrec<TArg>::Ret T2Arg; 
	typedef typename Log2fix::details::DoublePrec<STArg>::Ret ST2Arg; 

	TArg b = TArg(1) << (precision - 1);
	STArg y = 0;
	
	// static_assert(0 < precision && precision < sizeof(TArg) * 8 - 1);
	
	if(x == 0) {
		return -1; // represents negative infinity
	}
	
	while(x < TArg(1) << precision) {
		x <<= 1;
		y -= TArg(1) << precision;
	}
	
	while((TArg(2) << precision) <= x ) {
		x >>= 1;
		y += TArg(1) << precision;
	}
	
	T2Arg z = x;
	
	for(Size i = 0; i < precision; i++) {
		z = z * z >> precision;
		if(z >= (T2Arg(2) << precision)) {
			z >>= 1;
			y += b;
		}
		b >>= 1;
	}
	
	return y;
}

template<class TArg>
typename Log2fix::details::ToSigned<TArg>::Ret logfix(TArg x, Size precision) {
	typedef typename Log2fix::details::ToSigned<TArg>::Ret STArg; 
	typedef typename Log2fix::details::DoublePrec<STArg>::Ret ST2Arg; 
	ST2Arg t = ST2Arg(log2fix(x, precision)) * Log2fix::details::Consts<TArg>::INV_LOG2_E_Q0DOT_N;
	
	return t >> (sizeof(TArg) * 8);
}

#if 0
template<class TArg>
typename Log2fix::details::ToSigned<TArg>::Ret log10fix(TArg x, Size precision) {
	typedef typename Log2fix::details::ToSigned<TArg>::Ret STArg; 
	typedef typename Log2fix::details::DoublePrec<STArg>::Ret ST2Arg; 
	ST2Arg t = ST2Arg(log2fix(x, precision)) * Log2fix::details::Consts<TArg>::INV_LOG2_10_Q0DOT_N;
	
	return t >> (sizeof(TArg) * 8);
}
#endif

// [1] C. S. Turner,  "A Fast Binary Logarithm Algorithm", IEEE Signal
//     Processing Mag., pp. 124,140, Sep. 2010.

} }

example("log2fix") {
	using Math::Fp::logfix;
	
	assert_eq(logfix(uint8_t(0x62), 8 - 5), 0x13);
	assert_eq(logfix(uint16_t(0x6200), 16 - 5), 0x140A);
	#ifdef UINT64_MAX
		assert_eq(logfix(uint32_t(0x62000000), 32 - 5), 0x140B512E);
	#endif
}
