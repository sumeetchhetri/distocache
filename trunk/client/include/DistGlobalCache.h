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
 * DistGlobalCache.h
 *
 *  Created on: 07-Apr-2013
 *      Author: sumeetc
 */

#ifndef DISTGLOBALCACHE_H_
#define DISTGLOBALCACHE_H_
#include "DistoCacheConnectionFactory.h"
#include "Serialize.h"

class DistGlobalCache {
	string cacheKey;
	DistoCacheClientUtils* cl;
public:
	DistGlobalCache(string cacheKey)
	{
		this->cacheKey = cacheKey;
		cl = DistoCacheConnectionFactory::getConnection();
	}
	template <class T> void add(string key, T value)
	{
		string serValue = Serialize::serialize<T>(value);
		cl->addObjectEntry(cacheKey, serValue);
	}
	template <class T> void get(string key)
	{
		string serValue = cl->getObjectEntryValue(key);
		return Serialize::unserialize<T>(serValue);
	}
	void erase(string key)
	{
		cl->removeObjectEntry(key);
	}
	~DistGlobalCache()
	{
		delete cl;
	}
};

#endif /* DISTGLOBALCACHE_H_ */
