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
 * DistQueue.h
 *
 *  Created on: 04-Apr-2013
 *      Author: sumeetc
 */

#ifndef DISTQUEUE_H_
#define DISTQUEUE_H_
#include "DistoCacheConnectionFactory.h"
#include "Serialize.h"

template <class T> class DistQueue {
	string cacheKey;
	DistoCacheClientUtils* cl;
public:
	DistQueue(string cacheKey)
	{
		this->cacheKey = cacheKey;
		cl = DistoCacheConnectionFactory::getConnection();
		try {
			cl->allocate(cacheKey, "queue");
		} catch(const string& err) {
			if(err!="Entry already exists") {
				throw err;
			}
		}
	}
	void push(T t)
	{
		string serValue = Serialize::serialize<T>(t);
		cl->addCollectionEntry(cacheKey, serValue);
	}
	T front()
	{
		string serValue = cl->getFrontValue(cacheKey);
		return Serialize::unserialize<T>(serValue);
	}
	T back()
	{
		string serValue = cl->getBackValue(cacheKey);
		return Serialize::unserialize<T>(serValue);
	}
	void pop()
	{
		cl->popValueQueue(cacheKey);
	}
	string get_pop()
	{
		cl->popGetValueQueue(cacheKey);
	}
	size_t size()
	{
		return cl->size(cacheKey);
	}
	bool isEmpty()
	{
		return cl->isEmpty(cacheKey);
	}
	void free()
	{
		cl->deallocate(cacheKey);
	}
	virtual ~DistQueue()
	{
		delete cl;
	}
};

#endif /* DISTQUEUE_H_ */
