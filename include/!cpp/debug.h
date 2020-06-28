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
  
  #include <stdio.h>
  #include <stdarg.h>
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
  #include <assert.h>
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