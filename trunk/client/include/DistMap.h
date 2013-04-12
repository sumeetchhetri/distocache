/*
	Copyright 2009-2013, Sumeet Chhetri

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
/*
 * DistMap.h
 *
 *  Created on: 05-Apr-2013
 *      Author: sumeetc
 */

#ifndef DISTMAP_H_
#define DISTMAP_H_
#include "DistoCacheConnectionFactory.h"
#include "Serialize.h"
#include "map"

template <class K, class V> class DistMap {
	string cacheKey;
	DistoCacheClientUtils* cl;
public:
	DistMap(string cacheKey)
	{
		this->cacheKey = cacheKey;
		cl = DistoCacheConnectionFactory::getConnection();
		try {
			cl->allocate(cacheKey, "map");
		} catch(const string& err) {
			if(err!="Entry already exists") {
				throw err;
			}
		}
	}
	void insert(pair<K, V> entry)
	{
		string serValue = Serialize::serialize<V>(entry.second);
		cl->addMapEntry(cacheKey, CastUtil::lexical_cast<string>(entry.first), serValue);
	}
	const V operator[](K key) const
	{
		string serValue = cl->getMapEntryValue(cacheKey, CastUtil::lexical_cast<string>(key));
		return Serialize::unserialize<V>(serValue);
	}
	V at(K key)
	{
		string serValue = cl->getMapEntryValue(cacheKey, CastUtil::lexical_cast<string>(key));
		return Serialize::unserialize<V>(serValue);
	}
	void erase(K key)
	{
		cl->removeMapEntry(cacheKey, CastUtil::lexical_cast<string>(key));
	}
	size_t size()
	{
		return cl->size(cacheKey);
	}
	bool isEmpty()
	{
		return cl->isEmpty(cacheKey);
	}
	void clear()
	{
		cl->clear(cacheKey);
	}
	void free()
	{
		cl->deallocate(cacheKey);
	}
	virtual ~DistMap()
	{
		delete cl;
	}

	class iterator {
			friend class DistMap;
			int position;
			string cacheKey;
			DistoCacheClientUtils* cl;
			iterator(string cacheKey, DistoCacheClientUtils* cl)
			{
				this->cacheKey = cacheKey;
				this->cl = cl;
			}
		public:
			iterator()
			{
				position = -1;
			}
			V get()
			{
				if(position>=0)
				{
					string serValue = cl->getMapEntryValueByPosition(cacheKey, position);
					return Serialize::unserialize<V>(serValue);
				}
				else
				{
					throw "Position value is less than 0";
				}
			}
			void set(V v)
			{
				if(position>=0)
				{
					string serValue = Serialize::serialize<V>(v);
					cl->setMapEntryValueByPosition(cacheKey, position, serValue);
				}
				else
				{
					throw "Position value is less than 0";
				}
			}
			iterator& operator++()
			{
				position++;
				return *this;
			}
			iterator& operator+=(int incValue)
			{
				position += incValue;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp;
				temp.position = position;
				++position;
				return temp;
			}
			iterator& operator--()
			{
				position--;
				return *this;
			}
			iterator& operator-=(int incValue)
			{
				position -= incValue;
				return *this;
			}
			iterator operator--(int)
			{
				iterator temp;
				temp.position = position;
				--position;
				return temp;
			}
			bool operator!=(const iterator& b)
			{
				return position!=b.position;
			}
		};

	iterator begin()
	{
		iterator it(cacheKey, cl);
		it.position = 0;
		return it;
	}
	iterator end()
	{
		iterator it(cacheKey, cl);
		it.position = size();
		return it;
	}
};

#endif /* DISTMAP_H_ */
