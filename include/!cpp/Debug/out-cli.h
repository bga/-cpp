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

#include <!cpp/wrapper/cstdio>
#include <!cpp/wrapper/cstring>
#include <!cpp/common.h>

namespace Bga { namespace Debug {
	#ifndef BGA__DEBUG__LOG_URL
		#define BGA__DEBUG__LOG_URL ((char *)0)
	#endif
	
	FILE* const OutCli_defaultStream = stderr;
	
	char const* writeString(char const* s, StringSize maxLen) {
		FILE* const f = (BGA__DEBUG__LOG_URL == 0) ? OutCli_defaultStream : fopen(BGA__DEBUG__LOG_URL, "a");
		
		while(*s != 0 && maxLen != 0) {
			fputc(*s, f);
			++s;
			--maxLen;
		}
		
		if(BGA__DEBUG__LOG_URL != 0) {
			fclose(f);
		};
		
		return s;  
	}
	char const* writeString(char const* s) {
		return writeString(s, StringSize(-1));
	}

} } //# namespace
#endif
