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

//# [https://stackoverflow.com/a/3782064]
#define BGA__IS_EMPTY_MACRO__NO_OTHER_MACRO_STARTS_WITH_THIS_NAME_
#define BGA__IS_EMPTY_MACRO_IMPL(nameArg) defined(BGA__IS_EMPTY_MACRO__NO_OTHER_MACRO_STARTS_WITH_THIS_NAME_ ## nameArg)
#define BGA__IS_EMPTY_MACRO(nameArg) BGA__IS_EMPTY_MACRO_IMPL(nameArg)

#if 0
  template<class ValueArg, BGA__TEMPLATE__ENABLE_IF(boost::is_arithmetic<ValueArg>::value)>
  ValueArg abs(ValueArg x) {
    return (0 <= x) ? x : -x;
  }
#endif
#define BGA__TEMPLATE__ENABLE_IF(condExprArg) typename ::std::enable_if<(condExprArg), int>::type = 0



#define BGA__STR(x) BGA__STR_IMPL(x)
#define BGA__STR_IMPL(x) #x

#define BGA__CONCAT(a, b) BGA__CONCAT_IMPL(a, b)
#define BGA__CONCAT_IMPL(a, b) a ## b

#define BGA__CONCAT3(a, b, c) BGA__CONCAT(BGA__CONCAT(a, b), c)
#define BGA__CONCAT4(a, b, c, d) BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(a, b), c), d)
#define BGA__CONCAT5(a, b, c, d, e) BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(a, b), c), d), e)
#define BGA__CONCAT6(a, b, c, d, e, f) BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(BGA__CONCAT(a, b), c), d), e), f)

#define BGA__DUP1(aArg, sepArg) aArg
#define BGA__DUP2(aArg, sepArg) aArg sepArg aArg
#define BGA__DUP3(aArg, sepArg) aArg sepArg aArg sepArg aArg
#define BGA__DUP4(aArg, sepArg) BGA__DUP2(aArg, sepArg) sepArg BGA__DUP2(aArg, sepArg)
#define BGA__DUP5(aArg, sepArg) BGA__DUP4(aArg, sepArg) sepArg BGA__DUP1(aArg, sepArg)
#define BGA__DUP6(aArg, sepArg) BGA__DUP4(aArg, sepArg) sepArg BGA__DUP2(aArg, sepArg)
#define BGA__DUP7(aArg, sepArg) BGA__DUP4(aArg, sepArg) sepArg BGA__DUP3(aArg, sepArg)
#define BGA__DUP8(aArg, sepArg) BGA__DUP4(aArg, sepArg) sepArg BGA__DUP4(aArg, sepArg)
#define BGA__DUP9(aArg, sepArg) BGA__DUP5(aArg, sepArg) sepArg BGA__DUP4(aArg, sepArg)
#define BGA__DUP10(aArg, sepArg) BGA__DUP5(aArg, sepArg) sepArg BGA__DUP5(aArg, sepArg)
#define BGA__DUP16(aArg, sepArg) BGA__DUP8(aArg, sepArg) sepArg BGA__DUP8(aArg, sepArg)
#define BGA__DUP24(aArg, sepArg) BGA__DUP16(aArg, sepArg) sepArg BGA__DUP8(aArg, sepArg)
#define BGA__DUP32(aArg, sepArg) BGA__DUP16(aArg, sepArg) sepArg BGA__DUP16(aArg, sepArg)
#define BGA__DUP48(aArg, sepArg) BGA__DUP32(aArg, sepArg) sepArg BGA__DUP16(aArg, sepArg)
#define BGA__DUP64(aArg, sepArg) BGA__DUP32(aArg, sepArg) sepArg BGA__DUP32(aArg, sepArg)
#define BGA__DUP96(aArg, sepArg) BGA__DUP64(aArg, sepArg) sepArg BGA__DUP32(aArg, sepArg)
#define BGA__DUP128(aArg, sepArg) BGA__DUP64(aArg, sepArg) sepArg BGA__DUP64(aArg, sepArg)
#define BGA__DUP256(aArg, sepArg) BGA__DUP128(aArg, sepArg) sepArg BGA__DUP128(aArg, sepArg)
#define BGA__DUP512(aArg, sepArg) BGA__DUP256(aArg, sepArg) sepArg BGA__DUP256(aArg, sepArg)


#define BGA__PRAGMA(xArg) _Pragma(BGA__STR(xArg))

#ifdef __COUNTER__
  #define BGA__UNIQUE_ID __COUNTER__
#else
  #define BGA__UNIQUE_ID __LINE__
#endif

#define BGA__UNIQUE_NAME BGA__CONCAT(dummy, BGA__UNIQUE_ID)

#define BGA__DEFINE_CV_TEMPLATE_SPECIALIZATION(structArg, typeArg) \
  template <class T> structArg typeArg<T const> : public typeArg<T> {  }; \
  template <class T> structArg typeArg<T volatile> : public typeArg<T> {  }; \
  template <class T> structArg typeArg<T const volatile> : public typeArg<T> {  };

