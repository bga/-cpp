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
#include <!cpp/Stream/Hash/Crc/Msb_Bit.h>
#include <!cpp/TestRunner.h>

#pragma push_macro("Self")
#undef Self
#define Self Msb_Nibble_OneTable

namespace Bga { namespace Stream { namespace Hash { namespace Crc {

template<class ValueArg, class LookupTableValueArg>
struct Self;

template<class LookupTableValueArg>
struct Self<U8, LookupTableValueArg> {
	typedef FU8 Value;
	typedef FU8 HashValue;
	typedef LookupTableValueArg LookupTableValue;
	
	typedef LookupTableValue LookupTable[(UIntMax(1) << (1 * CHAR_BIT / 2))];
	
	static const HashValue hashInit = HashValue(-1);

	LookupTableValue* lookupTable; 

	Self(LookupTableValue* lookupTable_, FU8 generator): lookupTable(lookupTable_) {
		this->genTable(generator);
	} 
	Self(LookupTableValue* lookupTable_): lookupTable(lookupTable_) {
	} 
	
		
	Self& genTable(FU8 const generator) {
		::Bga::Stream::Hash::Crc::Msb_Bit<U8> subGen(generator);
		forInc(FU8, dividend, 0, (UIntMax(1) << (1 * CHAR_BIT / 2))) {
			this->lookupTable[dividend] = subGen.update(dividend, 0);
		}
		return *this;
	}

	//# [https://github.com/pebble/ArduinoPebbleSerial/blob/master/utility/hash.c]
	//# MIT license
	HashValue update(Value data, HashValue hashInit) const {
		typedef typename ::Bga::int_type_traits<HashValue>::fast_type HashValueF;

		HashValueF hash = hashInit;
		for(FU8 i = 2; i > 0; i--) {
			FU8 nibble = data;
			if(i % 2 == 0) {
				nibble >>= (CHAR_BIT / 2);
			};
			FU8 index = nibble ^ (hash >> (CHAR_BIT / 2));
			hash = FU8(this->lookupTable[index & ((UIntMax(1) << (1 * CHAR_BIT / 2)) - 1)]) ^ (hash << (CHAR_BIT / 2));
		}
		
		return hash;
	}
	
	HashValue finalize(HashValue hash) const {
		return hash;
	}
};


//# Optimal polynomial chosen based on
//# http://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
//# Note that this is different than the standard CRC-8 polynomial, because the
//# standard CRC-8 polynomial is not particularly good.
//# nibble lookup table for (x^8 + x^5 + x^3 + x^2 + x + 1)
#if 0
#include <iostream>

void genTable(uint8_t const generator) {
	::std::cout << "const FU8 Crc8_Config::lookupTable[" << (uintmax_t(1) << (1 * CHAR_BIT / 2)) <<  "] = {\n\t"; 
	for(int dividend = 0; dividend != (uintmax_t(1) << (1 * CHAR_BIT / 2)); dividend += 1) {
		uint8_t currbyte = dividend;
		
		for(uint_fast8_t bit = 0; bit != CHAR_BIT; bit += 1) {
			if((currbyte & (UIntMax(1) << (1 * CHAR_BIT - 1))) != 0) {
				currbyte <<= 1;
				currbyte ^= generator;
			}
			else {
				currbyte <<= 1;
			}
		}
		::std::cout << unsigned(currbyte) << ", ";
//		lookup[dividend] = currbyte;
	}
	::std::cout << "\b\b\n};" << ::std::endl; 
}
int main() {
	genTable(0x2F);
	return 0;
}
#endif // 0

} } } } //# namespace

#ifdef BGA__TESTRUNNER_ON
example(BGA__STR(Self)) {
	using namespace ::Bga::Stream::Hash;
	
	FU8 data[] = { '1', '2', '3', '4', '5' };
	enum { 
		generator = 0x31, 
		dataCrcValue = 157, 
	}; 
	
	typename Crc::Self<U8, FU8>::LookupTable hashLookupTableGen;
	
	assert_eq(unsigned(makeHash(Crc::Self<U8, FU8>(hashLookupTableGen, generator)).bulkCalc(data, arraySize(data))), unsigned(dataCrcValue));
}
#endif

#pragma pop_macro("Self")
