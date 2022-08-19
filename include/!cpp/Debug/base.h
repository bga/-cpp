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

//# for { ::std::swap }
#include <!cpp/wrapper/utility>

#include <!cpp/common.h>

namespace Bga { namespace Debug {
	#ifndef BGA__DEBUG__INT_MAX_TYPE
		#define BGA__DEBUG__INT_MAX_TYPE IntMax
	#endif

	typedef typename ::std::make_signed<BGA__DEBUG__INT_MAX_TYPE>::type Debug_IntMax;
	typedef typename ::std::make_unsigned<BGA__DEBUG__INT_MAX_TYPE>::type Debug_UIntMax;
	
	typedef typename ::Bga::int_type_traits<Debug_IntMax>::int_fast_type Debug_IntMaxFast;
	typedef typename ::Bga::int_type_traits<Debug_UIntMax>::uint_fast_type Debug_UIntMaxFast;
	
	char const* endl = "\n";
	char const* zeroLiteral = "\\0";
	
	FU8 defaultPrintBase = 10;
	
	typedef FI16 StringSize;
	
	static_assert_test(::std::is_signed<StringSize>::value, !!x);
	
	char const* writeString(char const* s);
	char const* writeString(char const* s, StringSize maxLen);
	
	char* uintToString(Debug_UIntMaxFast v, FU8 base = 10, FI8 minWidth = -1);

	char* intToString(Debug_IntMaxFast v, FU8 base = 10, FI8 minWidth = -1) {
		char* str = uintToString(Debug_UIntMaxFast(Math_abs(v)), base, minWidth);
		if(v < 0) {
			--str;
			*str = '-'; 
		};
		return str;
	}
	void printLocation(char const* file, int line) {
		writeString("[");
		writeString(file);
		writeString(":");
		writeString(uintToString(Debug_UIntMaxFast(line), 10));
		writeString("] ");
	}
	void printExpr(char const* expr) {
		writeString(expr);
		writeString(" = ");
	}
	void printEnd() {
		writeString(endl);
	}
	

	FI8 baseToMinWidth(FU8 base, FU8 intSize) {
		return ((base == 16) ? FI8(intSize) * 2 : -1);
	}

	template<class IntArg>
	typename ::std::enable_if< ::std::is_unsigned<IntArg>::value, void>::type inline printValue(IntArg v) {
		writeString(uintToString(Debug_UIntMaxFast(v), defaultPrintBase, baseToMinWidth(defaultPrintBase, Math_min(sizeof(IntArg), sizeof(Debug_UIntMax)))));
	}
	template<class IntArg>
	typename ::std::enable_if< ::std::is_signed<IntArg>::value, void>::type inline printValue(IntArg v) {
		writeString(intToString(Debug_IntMaxFast(v), defaultPrintBase, baseToMinWidth(defaultPrintBase, Math_min(sizeof(IntArg), sizeof(Debug_IntMax)))));
	}

	void dumpStringToZero(char const* s, StringSize maxLen) {
		writeString("'");
		writeString(s, maxLen);
		writeString("'");
	}
	void dumpStringToMax(char const* s, StringSize maxLen) {
		writeString("'");
		
		char const* const sEnd = s + maxLen;
		while(s != sEnd) {
			if(*s == 0) {
				writeString(zeroLiteral);
				s += 1;
			}
			else {
				s = writeString(s, sEnd - s);
			}
		}
		writeString("'");
	}
	template<class FwIterArg>
	void dumpArray(FwIterArg first, FwIterArg last) {
		while(first != last) {
			printValue(*first);
			writeString(", ");
			++first;
		}
	}
	
	template<class ValueArg, Size n>
	void inline printValue(ValueArg const (&vs)[n]) {
		dumpArray(&vs[0], &vs[n]);
	}
	
	Size transformArrayIndex(SSize k, Size end) {
		return (k < 0) ? Size(SSize(end) + k + 1) : Size(k);
	}
	#define BGA__DEBUG__INSPECT_STRING_TO_ZERO(vsArg, maxLenArg) do { \
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::printExpr(BGA__STR(vsArg) "[.. " BGA__STR(maxLenArg) "]"); \
		::Bga::Debug::dumpStringToZero( (vsArg), (maxLenArg) ); \
		::Bga::Debug::printEnd(); \
	} while(0);
	#define BGA__DEBUG__INSPECT_STRING_TO_MAX(vsArg, maxLenArg) do { \
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::printExpr(BGA__STR(vsArg) "[.. " BGA__STR(maxLenArg) "]"); \
		::Bga::Debug::dumpStringToMax( (vsArg), (maxLenArg) ); \
		::Bga::Debug::printEnd(); \
	} while(0);

	#define BGA__DEBUG__INSPECT_ARRAY(vsArg, firstIndexArg, lastIndexArg) do { \
		Size vsSize = arraySize( (vsArg) ); \
		Size firstIndex = ::Bga::Debug::transformArrayIndex( (firstIndexArg), vsSize ); \
		Size lastIndex = ::Bga::Debug::transformArrayIndex( (lastIndexArg), vsSize ); \
		\
		if(lastIndex < firstIndex) { \
			::std::swap(firstIndex, lastIndex); \
		}; \
		\
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::printExpr(BGA__STR(vsArg) "[" BGA__STR(firstIndexArg) " .. " BGA__STR(lastIndexArg) "]"); \
		::Bga::Debug::dumpArray( &(vsArg)[firstIndex], &(vsArg)[lastIndex] ); \
		::Bga::Debug::printEnd(); \
	} while(0);
	#define BGA__DEBUG__HEX_INSPECT_ARRAY(vsArg, firstIndexArg, lastIndexArg) do { \
		::Bga::Debug::defaultPrintBase = 16; \
		BGA__DEBUG__INSPECT_ARRAY(vsArg, firstIndexArg, lastIndexArg) \
		::Bga::Debug::defaultPrintBase = 10; \
	} while(0);

	#define BGA__DEBUG__INSPECT_ITER_RANGE(firstArg, lastArg) do { \
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::dumpArray((firstArg), (lastArg)); \
		::Bga::Debug::printEnd(); \
	} while(0);
	#define BGA__DEBUG__HEX_INSPECT_ITER_RANGE(firstArg, lastArg) do { \
		::Bga::Debug::defaultPrintBase = 16; \
		BGA__DEBUG__INSPECT_ITER_RANGE(firstArg, lastArg) \
		::Bga::Debug::defaultPrintBase = 10; \
	} while(0);

	#define BGA__DEBUG__INSPECT(vArg) do { \
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::printExpr(BGA__STR(vArg)); \
		::Bga::Debug::printValue( (vArg) ); \
		::Bga::Debug::printEnd(); \
	} while(0);

	#define BGA__DEBUG__HEX_INSPECT(vArg) do { \
		::Bga::Debug::defaultPrintBase = 16; \
		BGA__DEBUG__INSPECT(vArg) \
		::Bga::Debug::defaultPrintBase = 10; \
	} while(0);

	#define BGA__DEBUG__INSPECT_MEM(objArg) do { \
		::Bga::Debug::printLocation(__FILE__, __LINE__); \
		::Bga::Debug::printExpr(BGA__STR(objArg)); \
		::Bga::Debug::dumpArray(reinterpret_cast<U8 const*>(&(objArg)), &(reinterpret_cast<U8 const*>(&(objArg))[sizeof(objArg)])); \
		::Bga::Debug::printEnd(); \
	} while(0);
	#define BGA__DEBUG__HEX_INSPECT_MEM(objArg) do { \
		::Bga::Debug::defaultPrintBase = 16; \
		BGA__DEBUG__INSPECT_MEM(objArg) \
		::Bga::Debug::defaultPrintBase = 10; \
	} while(0);
	
} } //# namespace
#else
	#define BGA__DEBUG__INSPECT_STRING_TO_MAX(vsArg, maxLenArg) do { (void)vsArg; (void)maxLenArg; } while(0);
	#define BGA__DEBUG__INSPECT_STRING_TO_ZERO(vsArg, maxLenArg) do { (void)vArg; (void)maxLenArg; } while(0);
	#define BGA__DEBUG__INSPECT_ARRAY(vsArg, firstIndexArg, lastIndexArg) do { (void)vsArg; (void)firstIndexArg; (void)lastIndexArg; } while(0);
	#define BGA__DEBUG__HEX_INSPECT_ARRAY(vsArg, firstIndexArg, lastIndexArg) do { (void)vsArg; (void)firstIndexArg; (void)lastIndexArg; } while(0);
	#define BGA__DEBUG__INSPECT_ITER_RANGE(firstArg, lastArg) do { (void)firstArg; (void)lastArg; } while(0);
	#define BGA__DEBUG__HEX_INSPECT_ITER_RANGE(firstArg, lastArg) do { (void)firstArg; (void)lastArg; } while(0);
	#define BGA__DEBUG__INSPECT(vArg) (void)vArg;
	#define BGA__DEBUG__HEX_INSPECT(vArg) (void)vArg;
	#define BGA__DEBUG__INSPECT_MEM(vArg) (void)vArg;
	#define BGA__DEBUG__HEX_INSPECT_MEM(vArg) (void)vArg;
#endif
	
#ifndef NDEBUG
	#define BGA__DEBUG__EXEC if(1)
#else
	#define BGA__DEBUG__EXEC if(0)
#endif
