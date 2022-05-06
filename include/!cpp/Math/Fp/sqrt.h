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

#include <!cpp/wrapper/cstdint>

#include <!cpp/TestRunner.h>

namespace Math { namespace Fp { namespace Sqrt { namespace details { 
	template<class TArg> struct HalfInt {
		typedef typename ::Bga::make_half_int_nocv<TArg>::type Ret;
	};
} } } }

namespace Math { namespace Fp {
template<class TArg>
typename Sqrt::details::HalfInt<TArg>::Ret sqrt(TArg x) {
	typedef typename Sqrt::details::HalfInt<TArg>::Ret HalfT;
	HalfT a = 0;
	HalfT p = HalfT(-1) - (HalfT(-1) >> 1); //# set last bit
	
	while(p != 0) {
		HalfT newA = a | p;
		TArg newA2 = TArg(newA) * newA;
		if(newA2 <= x) a = newA;
		// more instructions for rare condition
		#ifdef MATH_FP_SQRT_FASTEXIT
			if(newA2 == x) break;
		#endif
		p >>= 1;
	}
	return a;
}
}}

example("Math::Fp::sqrt") {
	using Math::Fp::sqrt;
	
	assert_eq(sqrt(uint16_t(123UL)), 11);
	assert_eq(sqrt(uint16_t(0UL)), 0);
	assert_eq(sqrt(uint16_t(1UL)), 1);
	assert_eq(sqrt(uint16_t(10UL)), 3);
	assert_eq(sqrt(uint16_t(100UL)), 10);
	assert_eq(sqrt(uint32_t(1000UL)), 31);
	assert_eq(sqrt(uint32_t(10000UL)), 100);
	assert_eq(sqrt(uint32_t(100000UL)), 317);
}
