#include <!cpp/wrapper/cstdio>
#include <!cpp/wrapper/iostream>
#include <!cpp/wrapper/iomanip>
#include <!cpp/common.h>
#include "MinMaxRollingBinaryTreeFinder.h"

const unsigned showIndexMaxLog10 = 2; 
const unsigned showIndexMax = BGA__MATH__POW_INT(10, showIndexMaxLog10); 


struct MinMaxRollingBinaryTreeFinder_Config {
	enum {
		levelMax = 3,
		levelValuesSizeLog2 = 2,
	};

	typedef FU16 Index;
	typedef FU8 SubIndex;
	typedef FU8 Level;
	typedef FI32 DataValue;
};

typedef Math::MinMaxRollingBinaryTreeFinder<MinMaxRollingBinaryTreeFinder_Config> MinMaxRollingBinaryTreeFinder;
MinMaxRollingBinaryTreeFinder minMaxRollingBinaryTreeFinder;

typedef MinMaxRollingBinaryTreeFinder::MinMaxD MinMaxRollingBinaryTreeFinder_MinMaxD;

void MinMaxRollingBinaryTreeFinder_dump(::std::ostream& stream, MinMaxRollingBinaryTreeFinder& minMaxRollingBinaryTreeFinder) {
	forInc(MinMaxRollingBinaryTreeFinder::Level, level, 0, minMaxRollingBinaryTreeFinder.levelMax) {
		forInc(MinMaxRollingBinaryTreeFinder::SubIndex, i, 0, minMaxRollingBinaryTreeFinder.levelValuesSize) {
			stream << ::std::setw(showIndexMaxLog10) << minMaxRollingBinaryTreeFinder.matrix[level][i].max << " ";
		}
		stream << std::endl;
	}
}


void test(FI32 begin, FI32 end, FI32 showIndexLow, FI32 showIndexHigh) {
	forInc(FI32, i, begin, end) {
		MinMaxRollingBinaryTreeFinder_MinMaxD rootMinMax = minMaxRollingBinaryTreeFinder.addValue(FI32(i), minMaxRollingBinaryTreeFinder.levelMax - 1);
		
		if(showIndexLow <= i && i <= showIndexHigh) {
			::std::cout << "i = " << i << ::std::endl;
			MinMaxRollingBinaryTreeFinder_dump(::std::cout, minMaxRollingBinaryTreeFinder);
			::std::cout << "rootMinMax.max = " << rootMinMax.max << ::std::endl;
			::std::cout << ::std::endl;
		};
	}

}

int main(int argc, char* argv[]) {
	int showIndexLow = 0; if(argc < 1 || 1 != sscanf(argv[1], "%d", &showIndexLow)) return 1;
	int showIndexHigh = showIndexMax; if(argc < 2 || 1 != sscanf(argv[2], "%d", &showIndexHigh)) return 1;
	
	if(showIndexHigh < showIndexLow) {
		::std::swap(showIndexHigh, showIndexLow);
	};
	
	test(0, showIndexMax, showIndexLow, showIndexHigh);
	test(-showIndexMax, 0, showIndexLow, showIndexHigh);
	return 0;
}
