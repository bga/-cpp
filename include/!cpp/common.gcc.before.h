/*
	Copyright 2020-2021 Bga <bga.email@gmail.com>

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

#if defined(__cpp_constexpr) 
	#define BGA__MAYBE_CONSTEXPR constexpr
#endif

//# [https://stackoverflow.com/a/42403287]
#if defined(__GNUC__)
#  define BGA__CXX__GCC__VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#  if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#    define BGA__CXX__GCC__CXX11
#  endif
#  if (BGA__CXX__GCC__VERSION < 40600) || !defined(BGA__CXX__GCC__CXX11)
#    define BGA__CXX__NO_NULLPTR
#  endif
#endif

