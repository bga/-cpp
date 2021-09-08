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

#include <!cpp/wrapper/algorithm>
#include <!cpp/bitManipulations.h>
#include <!cpp/newKeywords.h>
#include <!cpp/common.h>


#pragma push_macro("Self")
#undef Self
#define Self CircularBuffer

namespace details { namespace Self {
	template<class ArrayTypeArg, class IndexArg>
	struct DynamicStorage {
		typedef ArrayTypeArg ArrayType;
		typedef IndexArg Index;

		// private:
		Size size;
		ArrayType* data;

	};

	template<class ArrayArg, class IndexArg>
	struct StaticStorage;

	template<class ArrayTypeArg, class IndexArg, Size sizeArg>
	struct StaticStorage<ArrayTypeArg[sizeArg], IndexArg> {
		typedef ArrayTypeArg ArrayType;
		typedef IndexArg Index;

		// private:
		static const Size size = sizeArg;
		ArrayType data[size];
	};

	template<class StorageArg>
	struct Api: public StorageArg {
		typedef StorageArg Storage;

		typedef typename Storage::ArrayType ArrayType;
		typedef typename Storage::Index Index;

		Index index;

    Api(): index(Index(-1)) {

		}

		inline Bool isInited() const {
			return this->index != Index(-1);
		}
		inline Bool isCarry() const {
			return this->index == this->size - 1;
		}

		inline void init() {
			this->index = this->size - 1;
		}

		inline ArrayType getCurrent() const {
			return this->data[this->index];
		}
		inline void setCurrent(ArrayType v) {
			this->data[this->index] = v;
		}

		void prefill(ArrayType v) {
			std::fill_n(this->data, Size(this->size), v);
		}

		Bool initAndPrefill(ArrayType v) {
			if(this->isInited()) {
				return false;
			}
			else {
				this->init();
				this->prefill(v);

				return true;
			}
		}

		inline Bool cycleIndex() {
			//# avr-gcc bug
			Size size2 = this->size;
			cycleInc(this->index, size2);

			return this->isCarry();
		}

		inline ArrayType add(ArrayType v) {
			this->cycleIndex();
			this->setCurrent(v);
			return v;
		}
	};
} } //# namespace


template<class ArrayTypeArg, class IndexArg>
struct BGA__CONCAT(Self, _Dynamic): public details::Self::Api<details::Self::DynamicStorage<ArrayTypeArg, IndexArg> > {
	typedef details::Self::Api<details::Self::DynamicStorage<ArrayTypeArg, IndexArg> > Base;

	void from(ArrayTypeArg* data_, Size sizeArg) {
		this->data = data_;
		this->size = sizeArg;
	}

  template<Size sizeArg>
	void from(ArrayTypeArg data_[sizeArg]) {
		this->data = data_;
		this->size = sizeArg;
	}

	BGA__CONCAT(Self, _Dynamic)(ArrayTypeArg* data_, Size sizeArg): Base() {
		this->data = data_;
		this->size = sizeArg;
	}

};

template<class ArrayArg, class IndexArg>
struct StaticStorage;

template<class ArrayArg, class IndexArg>
struct BGA__CONCAT(Self, _Static);

template<class ArrayTypeArg, class IndexArg, Size sizeArg>
struct BGA__CONCAT(Self, _Static)<ArrayTypeArg[sizeArg], IndexArg>: public details::Self::Api<details::Self::StaticStorage<ArrayTypeArg[sizeArg], IndexArg> > {
	typedef details::Self::Api<details::Self::StaticStorage<ArrayTypeArg, IndexArg> > Base;

	BGA__CONCAT(Self, _Dynamic)<ArrayTypeArg, IndexArg> toDynamic() {
		return BGA__CONCAT(Self, _Dynamic)<ArrayTypeArg, IndexArg>(this->data, sizeArg);
	}
};

#pragma pop_macro("Self")
