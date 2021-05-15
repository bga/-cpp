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

#define _DEBUG_DONT_EXEC 0 &&

#ifndef NDEBUG
  #ifndef Debug_logUrl
    #define Debug_logUrl ((char *)0)
  #endif
  
  #ifdef __GCC__
    #define _DEBUG_LIKE_PRINTF __attribute__ ((format (printf, 1, 2)))
  #else
    #define _DEBUG_LIKE_PRINTF 
  #endif
  
  #include <!cpp/wrapper/cstdio>
  #include <!cpp/wrapper/cstdarg>
  void Debug_vPrintRaw(const char *s, va_list args) {
    FILE *f = (Debug_logUrl == 0) ? stderr : fopen(Debug_logUrl, "a");
    vfprintf(f, s, args);
    fflush(f);
    if(Debug_logUrl != 0) fclose(f);
  }
  void Debug_printRaw(const char *s, ...) _DEBUG_LIKE_PRINTF {
    va_list args;
    va_start(args, s);
    Debug_vPrintRaw(s, args);
    va_end(args);
  }
#else
  #define Debug_vPrintRaw _DEBUG_DONT_EXEC
  #define Debug_printRaw _DEBUG_DONT_EXEC
#endif

#define Debug_print(format, args...) Debug_printRaw("[%s:%i] " format "%c", __FILE__, __LINE__, ##args, 0x0A)

#ifndef NDEBUG
  #include <!cpp/wrapper/cassert>
  #define doAndAssert assert
#else
  #define assert _DEBUG_DONT_EXEC
  #define doAndAssert 1 &&
#endif


#ifndef NDEBUG
  #define debug if(1)
#else
  #define debug if(0)
#endif
