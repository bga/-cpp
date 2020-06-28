#pragma once

#include <!cpp/common.h>

namespace Random {

#pragma push_macro("Self")
#undef Self
#define Self Base
struct Self {
	U32 generate(const U8& bitsCount);
};
#pragma pop_macro("Self")

} //# namespace Random
