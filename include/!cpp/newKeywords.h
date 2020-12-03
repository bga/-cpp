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
#include <!cpp/common.h>

#define var auto
#define val auto const
#define null nullptr
#define abstract

#if 0
#if 0
  //# assume { i } is { int }
  forInc(i, 0, 8) {
    printf("\n%i", i);
  }
#endif
//#define forInc(kNameArg, beginArg, endArg) val CONCAT(_end, __LINE__) = (endArg); for(var kNameArg = (beginArg); kNameArg < CONCAT(_end, __LINE__); kNameArg += 1)
#define forInc(kNameArg, beginArg, endArg) for(decltype(+(endArg)) kNameArg = (beginArg), _end = (endArg); kNameArg < _end; kNameArg += 1)
#endif

#if 0
  forInc(U8, i, 0, 8) {
    printf("\n%i", i);
  }
#endif
#define forInc(typeArg, kNameArg, beginArg, endArg) for(typeArg kNameArg = (beginArg), _end = (endArg); kNameArg < _end; kNameArg += 1)

#if 0
  forDec(U8, i, 0, 8) {
    printf("\n%i", i);
  }
#endif
#define forDec(typeArg, kNameArg, beginArg, endArg) for(typeArg kNameArg = typeArg(endArg), _begin = typeArg(beginArg); kNameArg-- != _begin;)

#define yes true
#define no false

#if 0
  U8 i = 0;
  loop {
    if(i == 8) {
      break;
    }
    else {
      i += 1;
    }
  }
#endif
#define loop for(;;)

#if 0
  wait((someRegister & _BV(someBit)) == 0);
#endif
#define wait while

#if 0
  ifLet(U8 i = foo(); i != 0;) {
    
    break;
  }
  for(U8 i = foo();;) if(i != 0) {
    
    
  break;} 
  else for(U8 i = foo();;) if(i != 0) {
    
  break;} 
  
  let(U8 i = foo()) if(i != 0) {
    
  ifLetEnd;}
  else let(U8 i = foo()) if(i != 0) {
    
  letEnd;}
  
  //# one extra indention
  block {
    U8 i = foo();
    if(i != 0) {
      
    }
  }
  
  do {
    i = foo();
    check(i == 1) {
      ...
      break;
    }
    j = bar();
    check(j == 2) {
      
    }
  } while(0);
#endif
#define ifLet for
#define block

//# because { if } requires { else }  
#if 0
  check(i == 1) {
    i = 2;
  }
#endif
#define check if


#define as static_cast
#define ref(vArg) (&(vArg))

#if 0
  DEFINE_NESTED_FUNCTION(int bar(int x) {
    return x + 1;
  })
  int foo = NF(bar)(1);
#endif
#ifdef __cplusplus
  #define DEFINE_NESTED_FUNCTION(...) struct _nf { static __VA_ARGS__ }; 
  #define NF(fnNameArg) _nf::fnNameArg
#elif __GNUC__
  #define DEFINE_NESTED_FUNCTION(...) __VA_ARGS__;
  #define NF(fnNameArg) fnNameArg
#endif
