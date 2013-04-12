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
 * DistoCacheConnectionFactory.cpp
 *
 *  Created on: 04-Apr-2013
 *      Author: sumeetc
 */

#include "DistoCacheConnectionFactory.h"

DistoCacheConnectionFactory* DistoCacheConnectionFactory::instance = NULL;

DistoCacheConnectionFactory::DistoCacheConnectionFactory(string host, int port, bool isSSL) {
	this->host = host;
	this->port = port;
	this->isSSL = isSSL;
}

DistoCacheConnectionFactory::~DistoCacheConnectionFactory() {
	// TODO Auto-generated destructor stub
}

void DistoCacheConnectionFactory::init(string host, int port, bool isSSL) {
	if(instance==NULL)
	{
		instance = new DistoCacheConnectionFactory(host, port, isSSL);
	}
}

void DistoCacheConnectionFactory::destroy() {
	if(instance==NULL)
	{
		delete instance;
	}
}

DistoCacheClientUtils* DistoCacheConnectionFactory::getConnection() {
	if(instance!=NULL)
	{
		return new DistoCacheClientUtils(instance->host, instance->port, instance->isSSL);
	}
	throw "DistoCacheConnectionFactory not initialized";
}
