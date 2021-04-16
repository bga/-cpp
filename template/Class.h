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
#include <!cpp/TestRunner.h>

#if 0
struct Config {
	typedef U32 SomeType;

	enum { someArg = 42 };

	static U32 foo1(U32 x) {
		return x;
	}
	U32 foo2(U32 x) {
		return x;
	}
};
#endif

#pragma push_macro("Self")

#undef Self
#define Self ClassName
template<typename ConfigArg> struct Self {
	typedef ConfigArg Config;
	Config m_config;

	Self() {
	}
};
#pragma pop_macro("Self")

#ifdef BGA__TESTRUNNER_ON
example(BGA__STR(Self)) {
	struct Config {
		typedef U32 SomeType;

		enum { someArg = 42 };

		static U32 foo1(U32 x) {
			return x;
		}
		U32 foo2(U32 x) {
			return x;
		}
	};

	Self<Config> x;
	assert_eq(x.aabb(), 1);
	assert_not_eq(x.aabb(), 2);
}
#endif
