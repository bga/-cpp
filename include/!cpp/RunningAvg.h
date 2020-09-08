#pragma once

#include <stddef.h>
#include <!cpp/bitManipulations.h>
#include <!cpp/newKeywords.h> 
#include <!cpp/common.h> 

#define Self RunningAvg
#define p (*this)
template<class ArrayType, class SumTypeArg>
class Self;

#if 1
template<class ArrayTypeArg, class SumTypeArg>
class Self<ArrayTypeArg[1], SumTypeArg> {
  public:
  typedef ArrayTypeArg ArrayType;
  typedef SumTypeArg SumType;
  static const size_t size = 1;
  
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

template<class ArrayTypeArg, size_t sizeArg, class SumTypeArg>
class Self<ArrayTypeArg[sizeArg], SumTypeArg> {
  public:
  typedef ArrayTypeArg ArrayType;
  typedef SumTypeArg SumType;
  static const size_t size = sizeArg;
  
  private:
  ArrayType data[size];
  SumType sum; 
  U8 index = ~0;
  
  public:
  
  Self(): index(U8(~0)) {  }
  
  void add(ArrayType v) {
    if(p.index == U8(~0)) {
      forInc(int, i, 0, size) {
        p.data[i] = v;
      }
      p.sum = v * size;
    }
    else {
      p.sum += v - p.data[p.index];
      p.data[p.index] = v;
      //# avr-gcc bug
      val size2 = size;
      cycleInc(p.index, size2);
    }
  }
  
  ArrayType computeAvg() const {
    return p.sum / size;
  }
};

#undef p
#undef Self