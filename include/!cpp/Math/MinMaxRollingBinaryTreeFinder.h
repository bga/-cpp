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
#include <!cpp/Math/MinMax.h>
#include <!cpp/bitManipulations.h>
#include <!cpp/newKeywords.h>
// #include <!cpp/TestRunner.h>

namespace Math {

#if 0
struct Config {
	enum {
		levelMax = 4,
		levelValuesSizeLog2 = 2,
	};

	typedef FU16 Index;
	typedef FU8 SubIndex;
	typedef FU8 Level;
	typedef I16 DataValue;
};
#endif

#pragma push_macro("Self")
#undef Self
#define Self MinMaxRollingBinaryTreeFinder
template<class ConfigArg>
struct Self {
	typedef ConfigArg Config;

	Config m_config;

	typedef typename Config::Index Index;
	typedef typename Config::SubIndex SubIndex;
	typedef typename Config::Level Level;
	typedef typename Config::DataValue DataValue;

	typedef MinMax<DataValue> MinMaxD;

	static const Level levelMax = Config::levelMax;
	static const SubIndex levelValuesSizeLog2 = Config::levelValuesSizeLog2;
	static const SubIndex levelValuesSize = (1 << levelValuesSizeLog2);


	Index index;
	MinMaxD matrix[levelMax][levelValuesSize];
	MinMaxD rootMinMax;

	Self() {
		index = 0;

		//# make it invalid
		rootMinMax.min = 1;
		rootMinMax.max = 0;
	}

	inline Bool isCarry(Level forcePropagate = 0) const {
		const Index bitMask = bitsCountToMask((levelMax - forcePropagate) * Config::levelValuesSizeLog2);
		return (this->index & bitMask) == bitMask;
	}

	inline MinMaxD fromArray(const MinMaxD* vs, Size size) {
		return MinMaxD::fromArray(vs, size);
	}

	void prefill(DataValue valueToAdd) {
		forInc(Level, level, 0, levelMax) {
			forInc(SubIndex, i, 0, levelValuesSize) {
				matrix[level][i].min = matrix[level][i].max = valueToAdd;
			}
		}
		rootMinMax.min = rootMinMax.max = valueToAdd;
	}
	MinMaxD addValue(DataValue valueToAdd, Level forcePropagate) {
		if(rootMinMax.max < rootMinMax.min) {
			prefill(valueToAdd);
			return rootMinMax;
		};

		enum { subIndexMask = bitsCountToMask(levelValuesSizeLog2) };

		Index newIndex = index + 1;
		index = newIndex;

		Level level = 0;

		matrix[level][newIndex & subIndexMask].min = matrix[level][newIndex & subIndexMask].max  = valueToAdd;

		while((newIndex & subIndexMask) == subIndexMask || forcePropagate <= level) {
			if(levelMax - 1 <= level) {
				rootMinMax = fromArray(matrix[levelMax - 1], arraySize(matrix[levelMax - 1]));
				break;
			};
			
			matrix[level + 1][(newIndex >> levelValuesSizeLog2) & subIndexMask] = fromArray(matrix[level], arraySize(matrix[level]));
			newIndex >>= levelValuesSizeLog2;
			level += 1;
		}

		return rootMinMax;
	}

	#if 0
	void dump() {
		forInc(Level, level, 0, levelMax) {
			forInc(SubIndex, i, 0, levelValuesSize) {
				std::cout << matrix[level][i] << " ";
			}
			std::cout << std::endl;
		}
	}
	#endif
};
#pragma pop_macro("Self")

} //# namespace

//# TODO tests
