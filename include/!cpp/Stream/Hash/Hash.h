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
#include <!cpp/newKeywords.h>

#pragma push_macro("Self")
#undef Self
#define Self Hash

namespace Bga { namespace Stream { namespace Hash {  

template<class AlgoArg>
struct Self {
	typedef AlgoArg Algo;
	typedef typename Algo::Value Value;
	typedef typename Algo::Value HashValue;
	

	Algo algo;
	HashValue hash;
	
	Self(Algo const& algo_): algo(algo_) {
		
	} 
	
	
	Self& init() {
		this->hash = Algo::hashInit;
		return *this;
	}
	HashValue update(Value data, HashValue hash_) const {
		return this->algo.update(data, hash_);
	}
	Self& add(Value const data) {
		this->hash = this->update(data, this->hash);
		return *this;
	}
	Self& add(Value const* data, Size n) {
		forInc(Size, i, 0, n) {
			this->add(data[i]);
		}
		return *this;
	}
	
	HashValue getResult() const {
		return this->algo.finalize(this->hash);
	}
	
	HashValue bulkCalc(Value const* data, Size n) {
		return Self(this->algo).init().add(data, n).getResult();
	}
	HashValue bulkCalc_charWithPad(Char const* data, Size n) {
		Self p(this->algo);
		
		p.init();
		p.add(reinterpret_cast<Value const*>(data), n / sizeof(Value));
		if(0 < n % sizeof(Value)) {
			Value x = 0;
			::std::copy_n(reinterpret_cast<Char const*>(&(reinterpret_cast<Value const*>(data)[n / sizeof(Value)])), n % sizeof(Value), reinterpret_cast<Char*>(&x));
			p.add(x);
		};
		return p.getResult();
	}
	template<class TArg>
	HashValue bulkCalc_charWithPad(TArg const& data) {
		return this->bulkCalc_charWithPad(reinterpret_cast<Char const*>(&data), sizeof(data));
	}
};

template<class AlgoArg> Self<AlgoArg> makeHash(AlgoArg algo) {
	return Self<AlgoArg>(algo);
}

} } } //# namespace

#pragma pop_macro("Self")
