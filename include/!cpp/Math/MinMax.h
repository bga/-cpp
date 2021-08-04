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
#include <!cpp/newKeywords.h>

// #include <!cpp/TestRunner.h>

namespace Math {

#pragma push_macro("Self")
#undef Self
#define Self MinMax
template<class IntTypeArg>
struct Self {
	typedef IntTypeArg IntType;

	IntTypeArg min;
	IntTypeArg max;

	Bool isValid() const {
		return this->min <= this->max;
	}
	Self& merge(const Self& from) {
		if(from.min < this->min) {
			this->min = from.min;
		};
		if(this->max < from.max) {
			this->max = from.max;
		};
		return *this;
	}

	static inline Self fromArray(const Self* vs, Size size) {
		Self x = vs[0];
		forInc(Size, i, 1, size) {
			x.merge(vs[i]);
		}
		return x;
	}

};
#pragma pop_macro("Self")

} //# namespace
