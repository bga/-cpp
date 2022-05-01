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

#if defined(BGA__CXX__NO_NULLPTR)

namespace std {

//# [https://stackoverflow.com/a/44517878]
class nullptr_t {
	public:
	
	//# convertible to any type of null non-member pointer...
	template<class T>
	operator T*() const {
		return 0;
	}

	//# or any type of null member pointer...
	template<class C, class T>
	operator T C::*() const {
		return 0;
	}

	private:
  
  //# Can't take address of nullptr
  void operator&() const;

};

} //# namespace

::std::nullptr_t const nullptr;

#endif
