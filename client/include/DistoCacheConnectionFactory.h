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
 * DistoCacheConnectionFactory.h
 *
 *  Created on: 04-Apr-2013
 *      Author: sumeetc
 */

#ifndef DISTOCACHECONNECTIONFACTORY_H_
#define DISTOCACHECONNECTIONFACTORY_H_
#include "DistoCacheClientUtils.h"

class DistoCacheConnectionFactory {
	static DistoCacheConnectionFactory* instance;
	string host;
	int port;
	bool isSSL;
	DistoCacheConnectionFactory(string host, int port, bool isSSL= false);
public:
	virtual ~DistoCacheConnectionFactory();
	static void init(string host, int port, bool isSSL= false);
	static void destroy();
	static DistoCacheClientUtils* getConnection();
};

#endif /* DISTOCACHECONNECTIONFACTORY_H_ */
