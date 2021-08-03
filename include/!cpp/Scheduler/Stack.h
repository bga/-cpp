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

namespace Scheduler {

#pragma push_macro("Self")
#undef Self
#define Self Stack


template<class CallArgArg, class IndexArg>
struct Self {
	typedef CallArgArg CallArg;
	typedef IndexArg Index;

	typedef void (*Task)(CallArg callArg);

	Self(Task* tasks_, Index size_): tasks(tasks_), tasks_size(size_), tasks_end(0) {

	}

	Task *tasks;
	Index tasks_end;
	Index tasks_size;

	Bool isFull() const {
		return this->tasks_end == this->tasks_size;
	}

	void push(Task task) {
		if(tasks_end < this->tasks_size) {
			this->tasks[this->tasks_end++] = task;
		};

	}

	void dispatch(CallArg callArg) {
		if(0 < this->tasks_end) {
			Task task = this->tasks[--this->tasks_end];
			task(callArg);
		};
	}
};
#pragma pop_macro("Self")

} //# namespace
