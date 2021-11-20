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

#include <!cpp/wrapper/cstddef>
#include <!cpp/wrapper/algorithm>
#include <!cpp/bitManipulations.h>
#include <!cpp/newKeywords.h> 
#include <!cpp/common.h> 

#pragma push_macro("Self")
#undef Self
#define Self RunningAvg

#pragma push_macro("p")
#undef p
#define p (*this)

template<class ArrayType, class SumTypeArg>
class Self;

#if 1
template<class ArrayTypeArg, class SumTypeArg>
class Self<ArrayTypeArg[1], SumTypeArg> {
  public:
  typedef ArrayTypeArg ArrayType;
  typedef SumTypeArg SumType;
  static const Size size = 1;
  
  private:
  ArrayType value;
  
  public:
  void add(ArrayType v) {
    p.value = v;
  }
  
  ArrayType computeAvg() const {
    return p.value;
  }
};
#endif

template<class ArrayTypeArg, Size sizeArg, class SumTypeArg>
class Self<ArrayTypeArg[sizeArg], SumTypeArg> {
  public:
  typedef ArrayTypeArg ArrayType;
  typedef SumTypeArg SumType;
  static const Size size = sizeArg;
  
  private:
  ArrayType data[size];
  SumType sum; 
  FU8 index;
  
  public:
  
  Self(): index(FU8(~0)) {  }
  
  void add(ArrayType v) {
    if(p.index == FU8(~0)) {
      std::fill_n(p.data, size, v);
      p.sum = v * size;
      p.index = 0;
    }
    else {
      p.sum += v;
      p.sum -= p.data[p.index];
      p.data[p.index] = v;
      //# avr-gcc bug
      Size size2 = size;
      cycleInc(p.index, size2);
    }
  }
  
  ArrayType computeAvg() const {
    return p.sum / size;
  }
};

#pragma pop_macro("p")
#pragma pop_macro("Self")
