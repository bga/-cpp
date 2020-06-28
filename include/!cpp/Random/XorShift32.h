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
