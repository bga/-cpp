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


#include <!cpp/wrapper/cstring>
#include <!cpp/common.h>


namespace Bga { namespace String {

#pragma push_macro("Self")

#undef Self
#define Self StringView

template<class CharArg, class IndexArg = Size>
struct Self {
	typedef CharArg Char;
	typedef IndexArg Index;
	
	Char const* s;
	Index len;
	
	Bool operator== (Self const& rhv) const {
		if(this->len == 0 && rhv.len == 0) {
			return true;
		};
		if(this->s == rhv.s) {
			return this->len == rhv.len || this->s == nullptr;
		};
		
		if(this->len != rhv.len) {
			return false;
		};
		
		#if 1
		return memcmp(this->s, rhv.s, this->len);
		#else
		Char const* p1 = this->s, p1End = this->s + this->len;
		Char const* p2 = rhv.s;
		while(p1 < p1End && *p1 == *p2) {
			p1 += 1;
			p2 += 1;
		}
		
		return p1 == p1End; 
		#endif
	}
	
	Bool operator!= (Self const& rhv) const {
		return !(*this == rhv);
	}
};

#undef Self

} } //# namespace
