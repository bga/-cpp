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

namespace Random {
#pragma push_macro("Self")
#undef Self
#define Self XorShift32
struct Self: Random::Base {
	U32 mState;
	Self() {
		mState = 1;
	}
	U32 generate(const U8 bitsCount) {
		/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
		U32 x = mState;
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		mState = x;
		return x >> (32 - bitsCount);
	}
};
#pragma pop_macro("Self")
} //# namespace Random
