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
#include <!cpp/common.h>
#include <!cpp/Random/Base.h>

namespace Bga { namespace Random {
#pragma push_macro("Self")
#undef Self
#define Self XorShift

namespace details {
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	//# mix it using xorShift
	template<class ResultUIntArg> 
	ResultUIntArg XorShift_mix(ResultUIntArg x);
	
	//# [http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html]
	template<> 
	inline U16 XorShift_mix<U16>(U16 x) {
		x ^= x << 7;
		x ^= x >> 9;
		x ^= x << 8;
		return x;
	}
	template<> 
	inline U32 XorShift_mix<U32>(U32 x) {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		
		return x;
	}
	#ifdef UINT64_MAX
	template<> 
	inline U64 XorShift_mix<U64>(U64 x) {
		x ^= x << 13;
		x ^= x >> 7;
		x ^= x << 17;
		
		return x;
	}
	#endif
} //# namespace


template<class ResultUIntArg> 
struct Self: Base<ResultUIntArg> {
	typedef ResultUIntArg ResultUInt;
	
	ResultUInt mState;
	
	Self() {
		mState = 1;
	}
	
	inline void seed(ResultUInt seed) {
		mState = seed;
	}
	inline ResultUInt generate(const FU8& bitsCount) {
		mState = details::XorShift_mix(mState);
		
		return mState >> (sizeof(ResultUInt) * 8 - bitsCount);
	}
};
#pragma pop_macro("Self")
} } //# namespace
