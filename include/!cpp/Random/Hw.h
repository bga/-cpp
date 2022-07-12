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
#include <!cpp/Random/XorShift.h>
// #include <!cpp/TestRunner.h>

//# include seq
#if 0
	/////////////////////////////// USER PART ////////////////////////////////////////
	#define BGA__HAL__CONFIG__ENABLE_ENTROPY_GEN
	namespace Bga { namespace Random { namespace Config { 
		typedef FU32 EntropyUInt;
	} } } //# namespace
	/////////////////////////////// USER PART END ////////////////////////////////////////
	
	/////////////////////////////// HAL PART ////////////////////////////////////////
	#if defined(BGA__HAL__CONFIG__ENABLE_ENTROPY_GEN)
		namespace Bga { namespace Random {
			void Entropy_pushBit(Bool);
		} } //# namespace
	#endif

		namespace Bga { namespace Hal {
			#if defined(BGA__HAL__CONFIG__ENABLE_ENTROPY_GEN)
				#undef  BGA__HAL__HAS_ENTROPY_SOURCE
				#define BGA__HAL__HAS_ENTROPY_SOURCE
				void entropySource() {
					::Bga::Random::Entropy_pushBit(randomBit);
				}
			#endif
		} } //# namespace
	/////////////////////////////// HAL PART END ////////////////////////////////////////
	
	#include <!cpp/Random/Hw.h>
	
	namespace App {
		// using namespace Bga;
		
		struct HwConfig {
			enum {
				genTryTimes = 20, 
			};
			void genEntropy() {
				::Bga::Hal::entropySource();
			}
		};
		::Bga::Random::Hw<U32, HwConfig> random;
		
		void someAlgo() {
			FU32 x = random.generate(12 /* bits */);
		}
	}
#endif

#ifndef BGA__HAL__HAS_ENTROPY_SOURCE
	#error No hw entropy source defined. Include at least one before include this random
#endif

#pragma push_macro("Self")

#undef Self
#define Self Hw

namespace Bga { namespace Random {

namespace details {
	Config::EntropyUInt entropyData;
} //# namespace

void Entropy_pushBit(Bool x) {
	details::entropyData <<= 1;
	if(x) {
		details::entropyData |= 1; 
	};
}

#if 0
struct Config {
	enum {
		genTryTimes = 20, 
	};
	void genEntropy() {
		::Bga::Random::Entropy_pushBit(randomBit);
	}
};
#endif


template<class ResultUIntArg, class ConfigArg> struct Self: Base<ResultUIntArg> {
	typedef ResultUIntArg ResultUInt;
	typedef ConfigArg Config;

	Config m_config;
	
	ResultUInt m_lastEntropyData;
	
	ResultUInt generate(const FU8 bitsCount) {
		FU8 limit = m_config.genTryTimes; 
		while(details::entropyData == m_lastEntropyData) {
			m_config.genEntropy();
			limit -= 1;
			if(limit == 0) {
				break;
			};
		}
		m_lastEntropyData = details::entropyData;
		return details::XorShift_mix(m_lastEntropyData) >> (sizeof(ResultUInt) * CHAR_BIT - bitsCount);
	}
	
};

#pragma pop_macro("Self")

} } //# namespace
