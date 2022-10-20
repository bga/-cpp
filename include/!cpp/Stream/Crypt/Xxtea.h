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
#include <!cpp/bitManipulations.h>
#include <!cpp/wrapper/cstring>
#include <!cpp/newKeywords.h>
#include <!cpp/TestRunner.h>

#pragma push_macro("Self")
#undef Self
#define Self Xxtea

namespace Bga { namespace Stream { namespace Crypt {  

// using namespace Bga;

//# based on ref code from [https://en.wikipedia.org/wiki/XXTEA]
struct Self {
	struct Key_Half {
		U32 data[2];
		Bool operator== (const Key_Half& x) const {
			return ::memcmp(reinterpret_cast<Char const*>(&(*this)), reinterpret_cast<Char const*>(&(x)), sizeof(*this)) == 0;
		}
		Bool operator!= (const Key_Half& x) const {
			return !(*this == x);
		}
	};
	struct Key {
		union {
			U32 data[4];
			Key_Half halfs[2];
		};
		Bool operator== (const Key& x) const {
			return ::memcmp(reinterpret_cast<Char const*>(&(*this)), reinterpret_cast<Char const*>(&(x)), sizeof(*this)) == 0;
		}
		Bool operator!= (const Key& x) const {
			return !(*this == x);
		}
	};
	// typedef U32 Key[4];
	// typedef U32 Key_Half[sizeof(Key) / sizeof(U32) / 2];
	typedef U32 Value;

	static const FU32 delta = 0x9e3779b9;

	//# To cipher "212 bytes or more" algorithm performs just 6 rounds, and carefully chosen bit patterns allows to detect and analyze avalanche effect. The paper notices adding two additional rounds (i.e. 8 rounds instead of 6) fixes this problem. [https://en.wikipedia.org/wiki/XXTEA#Cryptanalysis]
	static const FU8 roundsMin = 8;

	Key const* keyPtr;
	
	#define BGA__STREAM__CRYPT__XXTEA__MX (((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (this->keyPtr->data[(p & 3) ^ e] ^ z)))
	#define BGA__STREAM__CRYPT__XXTEA__NEXT_INDEX(pArg) 
	
	void encrypt(Value* v, Size n) const {
		if(n < 2) return;
		
		FU32 y, z, sum;
		Size p;
		FU8 rounds;
		FU32 e;

		if(n > 1) {
			rounds = this->roundsMin + 52 / n;
			sum = 0;
			z = v[n - 1];
			do {
				sum += this->delta;
				e = (sum >> 2) & 3;
				for(p = 0; p < n; p++) {
					Size pNext = p; cycleInc(pNext, n);
					y = v[pNext];
					z = v[p] += BGA__STREAM__CRYPT__XXTEA__MX;
				}
			} while(--rounds);
		}
	}
	void decrypt(Value* v, Size nArg) const {
		SSize n = SSize(nArg);
		
		if(n < 2) return;
		
		FU32 y, z, sum;
		SSize p;
		FU8 rounds;
		FU32 e;

		rounds = this->roundsMin + 52 / n;
		sum = rounds * this->delta;
		y = v[0];
		do {
			e = (sum >> 2) & 3;
			for(p = n - 1; p >= 0; p--) {
				SSize pNext = p; cycleDec(pNext, n);
				z = v[pNext];
				y = v[p] -= BGA__STREAM__CRYPT__XXTEA__MX;
			}
			sum -= this->delta;
		} while(--rounds);
	}
	
	#undef BGA__STREAM__CRYPT__XXTEA__MX
	
};

} } } //# namespace

#ifdef BGA__TESTRUNNER_ON
#include <!cpp/wrapper/iomanip>
#include <!cpp/wrapper/cstring>

template<class ValueArg, Size lenArg> 
::std::ostream& operator<< (::std::ostream& os, const ::std::array<ValueArg, lenArg>& arr) {
	forInc(Size, i, 0, arr.size()) {
		os << ::std::setw(2 * sizeof(ValueArg)) << ::std::setfill('0') << ::std::setbase(16) << arr[i]; 
	}
	return os;
}

example(BGA__STR(Self)) {
	using namespace Bga;
	using ::Bga::Stream::Crypt::Self;
	
	Self::Key key; 
	key.data[0] = 0x12345678UL; 
	key.data[1] = 0x23456789UL; 
	key.data[2] = 0x34567890UL;
	key.data[3] = 0x4567890AUL;
	
	typedef ::std::array<U32, 2> DataArray;
	
	// DataArray data = { '1', '2', '3', '4' };
	DataArray data = { '1', '2' };
	// DataArray data = { '1' };
	DataArray dataCopy = data;
	
	Self cryptEngine;
	cryptEngine.keyPtr = &key; 

	cryptEngine.encrypt(data.data(), data.size());
	assert_not_eq(data, dataCopy); 

	cryptEngine.decrypt(data.data(), data.size());
	assert_eq(data, dataCopy); 
}
#endif

#pragma pop_macro("Self")
