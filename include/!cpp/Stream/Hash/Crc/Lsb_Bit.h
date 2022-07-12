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
#include <!cpp/TestRunner.h>

#pragma push_macro("Self")
#undef Self
#define Self Lbs_Bit

namespace Bga { namespace Stream { namespace Hash { namespace Crc {  
	
template<class ValueArg>
struct Self {
	typedef ValueArg Value;
	typedef ValueArg HashValue;
	
	static const HashValue hashInit = HashValue(-1);

	const Value generator;

	Self(Value generator_): generator(generator_) {
		
	}
	
	HashValue update(Value data, HashValue hashInit) const {
		typedef typename ::Bga::int_type_traits<HashValue>::fast_type HashValueF;

		const HashValueF generatorF = this->generator;
		HashValueF hash = hashInit;
		
		hash ^= data;
		forInc(FU8, bit, 0, CHAR_BIT * sizeof(Value)) {
			if((hash & 1) != 0) {
				hash >>= 1;
				hash ^= generatorF;
			}
			else {
				hash >>= 1;
			}
		}
		return hash;
	}

	HashValue finalize(HashValue hash) const {
		return hash;
	}

};

} } } } //# namespace

#ifdef BGA__TESTRUNNER_ON
#include <!cpp/Stream/Hash/Hash.h>

example(BGA__STR(Self)) {
	using namespace ::Bga::Stream::Hash;
	
	U8 data[] = { '1', '2', '3', '4', '5' };
	enum { 
		generator = 0x31, 
		dataCrcValue = 25, 
	}; 
	
	assert_eq(unsigned(makeHash(Crc::Self<U8>(generator)).bulkCalc(nullptr, 0)), unsigned(0xFF)); 
	assert_eq(unsigned(makeHash(Crc::Self<U8>(generator)).bulkCalc(data, arraySize(data))), unsigned(dataCrcValue)); 
}
#endif

#pragma pop_macro("Self")
