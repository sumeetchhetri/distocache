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
 * ServiceHandler.h
 *
 *  Created on: 27-Mar-2013
 *      Author: sumeetc
 */

#ifndef SERVICEHANDLER_H_
#define SERVICEHANDLER_H_
#include "Logger.h"
#include "SSLHandler.h"
#include "AMEFDecoder.h"
#include "AMEFEncoder.h"
#include "CacheMap.h"
#define MAXBUFLENM 32768

class ServiceHandler {
	int fd;
	map<string,string> *params;
	bool isSSLEnabled;
	SSL_CTX *ctx;
	SSLHandler sslHandler;
	Logger logger;
	int getLength(string header,int size);
	bool validQuery(vector<string> parts, int size, string cmd1="", string cmd2="");
public:
	ServiceHandler(int fd, map<string,string> *params, bool isSSLEnabled, SSL_CTX *ctx, SSLHandler sslHandler);
	virtual ~ServiceHandler();
	void run();
};

#endif /* SERVICEHANDLER_H_ */
