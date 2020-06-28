#pragma once

#include <!cpp/common.h>

#define Self AddlerCrc
#include <!cpp/classHelpers.h>
#define p (*this)
class Self {
  public:
  typedef U8 CrcValue;
  
  private:
  //# a[0] + a[1] + ... + a[n]
  U16 sum;
  //# n * a[0] + (n - 1) * a[1] + ... + 1 * a[n]
  U16 weightedSum;
  
  public:
  Self& init() {
    p.sum = 0;
    p.weightedSum = 0;
    
    return p;
  } 
  
  template<class T> T update(T v) {
    const U8 vByte = v;
    p.sum += vByte;
    p.weightedSum += p.sum;
    
    return v;
  }
  
  //# warning. Only 1 undo is possible. But it useful for undo added crc itself 
  void undo() {
    p.weightedSum -= p.sum; 
  }
  
  CrcValue getCrcValue() const {
    return (p.weightedSum & 0xFF) ^ (p.weightedSum >> 8);
  }
};
#undef p
#undef Self