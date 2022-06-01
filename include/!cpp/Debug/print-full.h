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

#define _DEBUG_DONT_EXEC 0 &&


#ifndef NDEBUG

#include <!cpp/common.h>

namespace Bga { namespace Debug {

	char temp[UInt(sizeof(Debug_IntMax) * 8 * 0.3010) //# * log(10) / log(2) 
		+ 1 //# + ruoud up 
		+ 1 //# + sign
		+ 2 //# + 0x
		+ 1 //# + zero
	];
	
	char inline nToChar(FU8 x) {
		return (x < 10) ? '0' + x : 'A' + (x - 10);
	}
	
	char* uintToString(Debug_UIntMaxFast v, FU8 base, FI8 minWidth) {
		FU8 p = arraySize(temp);
		temp[--p] = 0;
		
		do {
			temp[--p] = nToChar(v % base);
			v /= base;
			--minWidth;
		} while(v != 0 || 0 < minWidth);

		if(base == 2) {
			temp[--p] = 'b';
			temp[--p] = '0';
		};

		if(base == 16) {
			temp[--p] = 'x';
			temp[--p] = '0';
		};
		
		return &temp[p];
	}
} } //# namespace
#endif
