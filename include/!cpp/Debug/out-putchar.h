/*
	Copyright 2022 Bga <bga.email@gmail.com>

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


#ifndef NDEBUG

#include <!cpp/common.h>

namespace Bga { namespace Debug {
	char const* writeString(char const* s, StringSize maxLen) {
		while(*s != 0 && maxLen != 0) {
			::putchar(*s);
			++s;
			--maxLen;
		}
		return s;
	}

	#ifdef BGA__DEBUG__OUT_PUTCHAR__USE_UNIFIED_FN
	char const* writeString(char const* s) {
		return writeString(s, StringSize(-1));
	}
	
	#else
	//# if user dont dump strings, 2nd version with maxLen is not needed -> less flash size
	char const* writeString(char const* s) {
		while(*s != 0) {
			::putchar(*s);
			++s;
		}
		return s;
	}
	#endif
} } //# namespace
#endif
