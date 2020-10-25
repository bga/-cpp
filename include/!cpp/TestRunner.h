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

#if 0
int x = 0;
example("x") {
  assert_eq(1, 2);
  assert_not_eq(2, 3);
};
#endif

#ifdef TESTRUNNER_ON

#include <iostream>
#include <string>
#include <unordered_map>

#ifndef TESTRUNNER_OUTPUT_STREAM
  #define TESTRUNNER_OUTPUT_STREAM std::cerr
#endif  

template<typename AArg, typename BArg> 
void _assert_not_eq(const char* fileName, int lineNo, const AArg& a, const BArg& b) {
  if(a != b) {
  
  }
  else {
    TESTRUNNER_OUTPUT_STREAM << '[' << fileName << ':' << lineNo << "] FAILED: " << a << " != " << b << std::endl;
  }
}
#define assert_not_eq(aArg, bArg) _assert_not_eq(__FILE__, __LINE__, (aArg), (bArg))
template<typename AArg, typename BArg> 

void _assert_eq(const char* fileName, int lineNo, const AArg& a, const BArg& b) {
  if(a == b) {
  
  }
  else {
    TESTRUNNER_OUTPUT_STREAM << '[' << fileName << ':' << lineNo << "] FAILED: " << a << " == " << b << std::endl;
  }
}
#define assert_eq(aArg, bArg) _assert_eq(__FILE__, __LINE__, (aArg), (bArg))

namespace TestRunnerNS {
  class Test {
    public:
    virtual void runTest() = 0;
  };
  
  std::unordered_map<const char * /* testName */, Test *> testNameToTestPtr;

  void runTests(std::string prefix) {
    //for(const auto& [testName, testPtr] : TestRunnerNS::testNameToTestPtr) {
    for(auto i = TestRunnerNS::testNameToTestPtr.begin(); i != TestRunnerNS::testNameToTestPtr.end(); ++i) { const auto& testName = (*i).first; const auto& testPtr = (*i).second; 
      if(std::string(testName).substr(0, prefix.size()) == prefix) {
        TESTRUNNER_OUTPUT_STREAM << "Running test '" << testName << "'" << std::endl;
        testPtr->runTest();
      }
      else {
        
      }
    }
  }
}

extern "C" int testRunnerMain(int argc, const char* argv[]) {
  std::string prefix = (2 <= argc) ? argv[1] : "";
  
  TestRunnerNS::runTests(prefix);
  // TODO return actual test success result 
  return 0;
}

#if 0
void TestRunner_userTestRun2();
namespace TestRunnerNS { class UserTest2: Test {
  public:
  UserTest2() { TestRunnerNS::testNameToTestPtr.insert({ "test2", this }); } 
  virtual void runTest() {
    TestRunner_userTestRun2();
  } 
} _test2; }
void TestRunner_userTestRun2() {
  assert_eq(2, 3);
}
#endif

#define _TESTRUNNER_EXAMPLE_ID(ID, testNameArg) _TESTRUNNER_EXAMPLE(CONCAT(UserTest, ID), CONCAT(TestRunner_userTestRun, ID), CONCAT(_test, ID), testNameArg) 
#define _TESTRUNNER_EXAMPLE(_classNameArg, _methodNameArg, _instanceNameArg, testNameArg) \
void _methodNameArg(); \
namespace TestRunnerNS { class _classNameArg: Test { \
  public:\
  _classNameArg() { TestRunnerNS::testNameToTestPtr.insert({ (testNameArg), this }); } \
  virtual void runTest() {\
    _methodNameArg();\
  } \
} _instanceNameArg; }\
void _methodNameArg() 

#ifdef __COUNTER__
  #define example(testNameArg) _TESTRUNNER_EXAMPLE_ID(__COUNTER__, testNameArg)
#else  
  #define example(testNameArg) _TESTRUNNER_EXAMPLE_ID(__LINE__, testNameArg)
#endif

#else // no { TESTRUNNER_ON }. Zero API

template<typename AArg, typename BArg> 
void assert_not_eq(const AArg& a, const BArg& b) {
}
template<typename AArg, typename BArg> 
void assert_eq(const AArg& a, const BArg& b) {
}

#define _TESTRUNNER_EXAMPLE_ID(ID, testNameArg) _TESTRUNNER_EXAMPLE(CONCAT(UserTest, ID), CONCAT(TestRunner_userTestRun, ID), CONCAT(_test, ID), testNameArg) 
#define _TESTRUNNER_EXAMPLE(_classNameArg, _methodNameArg, _instanceNameArg, testNameArg) \
inline void _methodNameArg() 

#ifdef __COUNTER__
  #define example(testNameArg) _TESTRUNNER_EXAMPLE_ID(__COUNTER__, testNameArg)
#else  
  #define example(testNameArg) _TESTRUNNER_EXAMPLE_ID(__LINE__, testNameArg)
#endif
 
#endif // TESTRUNNER_ON
