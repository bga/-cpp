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


#include <!cpp/wrapper/cstdio>
#include <!cpp/String/StringView.h>
#include <!cpp/common.h>
#include <!cpp/TestRunner.h>

#include <!cpp/debug.h>

namespace Bga { namespace String { namespace Tml {

#pragma push_macro("Self")

#undef Self
#define Self ChunkGenerator

template<class CharArg>
struct Self {
	typedef CharArg Char;
	

	typedef ::Bga::String::StringView<Char> Ret;

	Char const* lastP;
	Char const* const* keyValuePairsArray;
	Char const delimiter;
	Char const listDelimiter;
	Size chunkN;
	
	Self(Char const* tml_, Char const* const* keyValuePairsArray_, Char const delimiter_ = '%', Char const listDelimiter_ = '\0')
		: lastP(tml_), keyValuePairsArray(keyValuePairsArray_), delimiter(delimiter_), listDelimiter(listDelimiter_) {
		this->chunkN = Size(-1);
	}
	
	void reset(Char const* tml_) {
		this->lastP = tml_;
		this->chunkN = Size(-1);
	}
	
	Ret operator()() {
		Ret ret;
		ret.s = nullptr;
		
		if(this->lastP == nullptr) {
			return ret;
		};
		
		if(*this->lastP == 0) {
			return ret;
		};
		
		Char const* p = this->lastP;
		while(*p != 0 && *p != this->delimiter) {
			p += 1;
		}
		if(*p == 0) {
			ret.s = this->lastP;
			ret.len = p - this->lastP;
			this->lastP = p;
			return ret;
		};
		
		this->chunkN += 1;
		
		//# raw text chunk
		if(this->chunkN % 2 == 0) { 
			ret.s = this->lastP;
			ret.len = p - this->lastP;
			this->lastP = p + 1; //# skip delimiter
			
			return ret;
		};
		
		
		Char const* name = this->lastP;
		Char const* nameEnd = p;
		debug Debug_print("%.2s", name);

		ret.s = name - 1;
		ret.len = nameEnd - name + 2; //# name + delimiters around
//		ret.len = 0;

		//# "%%" -> "%"
		if(name == nameEnd) {
			ret.len = 1;
			return ret;
		};
		
		Char const* const* kvs = this->keyValuePairsArray;
		while(*kvs != nullptr) {
			Char const* kv = *kvs;
			while(*kv != this->listDelimiter) {
				debug Debug_print("%.2s", kv);

				Bool isMatch = true;
				Char const* nameP = name;
				while(*kv != this->listDelimiter && nameP != nameEnd) {
					if(*kv != *nameP) {
						isMatch = false;
					};
					kv += 1;
					nameP += 1;
				}
				isMatch = isMatch && *kv == this->listDelimiter && nameP == nameEnd;
				while(*kv != this->listDelimiter) {
					kv += 1;
				}
				kv += 1;
				Char const* vBegin = kv;
				
				while(*kv != this->listDelimiter) {
					kv += 1;
				}
				
				Char const* vEnd = kv;
				kv += 1;
				
				if(isMatch) {
					ret.s = vBegin;
					ret.len = vEnd - vBegin;
					
					break;
				};
			}
			kvs += 1;
		}

		this->lastP = p + 1; //# skip delimiter
		
		return ret;
	}
};

} } } //# namespace

#ifdef BGA__TESTRUNNER_ON
#include <!cpp/wrapper/string>
template<class CharArg>
static ::std::basic_string<CharArg> collectAllChunks(::Bga::String::Tml::Self<CharArg>&& tml) {
	typename ::Bga::String::Tml::Self<CharArg>::Ret chunk;  
	typedef ::std::basic_string<CharArg> Ret;
	
	Ret ret("");
	for(;;) {
		chunk = tml();
		if(chunk.s == nullptr) {
			break;
		};
		ret += Ret(chunk.s, chunk.len);
	}
	return ret;
}

example(BGA__STR(Self)) {
	typedef ::Bga::String::Tml::Self<char> Self;
	// typedef typename Self::Ret Tml_Ret;

	char delimiter = '%';
	char listDelimiter = '\0';
	
	#define BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ(tmlArg, expectedValueArg, varDataArg...) if(1) { char const* varData[] =  varDataArg; assert_eq(collectAllChunks(Self(tmlArg, varData, delimiter, listDelimiter)), ::std::basic_string<char>(expectedValueArg)); }
	
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("", "", { nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("abc", "abc", { nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%var%", "value", { "var\0value\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%var%", "value1", { "var\0value1\0var\0value2\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%foo%%com%", "barbaz", { "foo\0bar\0\0", "com\0baz\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%foo%+%com%", "bar+baz", { "foo\0bar\0\0", "com\0baz\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("_%var%", "_value", { "var\0value\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%var%_", "value_", { "var\0value\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%var_%", "%var_%", { "var\0value\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%va%", "%va%", { "var\0value\0\0", nullptr });
	BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%%", "%", { "var\0value\0\0", nullptr });
	
	if(1) {
		char delimiter = '$';
		BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("$var$", "value", { "var\0value\0\0", nullptr });
	};
	
	if(1) {
		char listDelimiter = ':';
		BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ("%var%", "value1", { "var:value1:var:value2::", nullptr });
	};
	
	#undef BGA__STRING__TML__CHUNK_GEN__TEST__ASSERT_EQ
}
#endif

#undef Self
