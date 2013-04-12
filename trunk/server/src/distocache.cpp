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

#include <iostream>
#include <stdio.h>
#include "map"
#include "vector"
#include "set"
#include "queue"
#include "deque"
#include "list"
#include "string"
#include "string"
#include "vector"
#include "map"
#include <algorithm>
#include <cstdlib>
#include <dlfcn.h>
#include "sstream"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <queue>
#include <sys/uio.h>
#include <sys/un.h>
#include <stdexcept>
#include <dlfcn.h>
#include <cxxabi.h>
#include <stdio.h>
#include <stdlib.h>
#include "string"
#include <sstream>
#include <typeinfo>
#include "Server.h"
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "PropFileReader.h"
#include <openssl/engine.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Thread.h"
#include "CastUtil.h"
#include "Logger.h"
#include "SelEpolKqEvPrt.h"
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "ServiceHandler.h"
using namespace std;

#define MAXEPOLLSIZE 100
#define MAXBUFLENM 32768
#define PORT "9992"
#define NUM_PROC 2
#define SKEYFILE "server.pem"
#define SPASSWORD "password"
#define SDHFILE "dh1024.pem"
#define SCA_LIST "root.pem"

using namespace std;

Logger logger;

void sigchld_handlergf(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void sigpipe_handle(int x){
}

int byteArrayToInt(char *b) {
	return ((b[0] & 0xFF) << 24)
		+ ((b[1] & 0xFF) << 16)
		+ ((b[2] & 0xFF) << 8)
		+ (b[3] & 0xFF);
}

char* intToByteArray(int value) {
	char *b = new char[4];
	for (int i = 0; i < 4; i++) {
		int offset = (4 - 1 - i) * 8;
		b[i] = (char) ((value >> offset) & 0xFF);
	}
	return b;
}

void signalSIGPIPE(int dummy)
{
	signal(SIGPIPE,signalSIGPIPE);
	logger << "Broken pipe ignore it" << getpid() << "\n" << flush;
}


void signalSIGSEGV(int dummy)
{
	signal(SIGSEGV,signalSIGSEGV);
	logger << "segmentation fault" << getpid() << "\n" << flush;
	exit(0);
}

void* service(void* arg)
{
	ServiceHandler *task = (ServiceHandler*)arg;
	task->run();
	delete task;
	return NULL;
}

void* serviceAdmin(void* arg)
{
	return NULL;
}


int main() {

	SSL_CTX *ctx;
	logger = Logger::getLogger("DistoCache");

	signal(SIGPIPE,signalSIGPIPE);
	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;

	int nfds;
	PropFileReader pread;
	propMap props = pread.getProperties("distocache.prop");
	string prot_type = props["PROT_TYPE"];//TCP or UDP
	string serv_addrs = props["SERV_ADDRS"];//localhost:8080;10.101.10.10:9999
	bool isServerSSL = false;
	string ssl_enb = props["SSL_ENAB"];//is SSL enabled
	if(ssl_enb=="true" || ssl_enb=="TRUE")
		isServerSSL = true;
	string port_no = props["PORT"];//Distocache listening port number
	string admin_port_no = props["ADMIN_PORT"];//Distocache listening port number
	strVec ipprts;
	StringUtil::split(ipprts, serv_addrs, ";");

	SSLHandler sSLHandler;
	if(isServerSSL)
	{
		string key_file = props["KEYFILE"];
		string dh_file = props["DHFILE"];
		string ca_list = props["CA_LIST"];
		string rand_file = props["RANDOM"];
		string sec_password = props["PASSWORD"];
		string tempcl = props["CLIENT_SEC_LEVEL"];
		/*HTTPS related*/
		//client_auth=CLIENT_AUTH_REQUIRE;
		/* Build our SSL context*/
		ctx = sSLHandler.initialize_ctx((char*)key_file.c_str(), (char*)sec_password.c_str(), (char*)ca_list.c_str());
		sSLHandler.load_dh_params(ctx, (char*)dh_file.c_str());

		SSL_CTX_set_session_id_context(ctx,
		  (const unsigned char*)&SSLHandler::s_server_session_id_context,
		  sizeof SSLHandler::s_server_session_id_context);

		/* Set our cipher list */
		/*if(ciphers){
		  SSL_CTX_set_cipher_list(ctx,ciphers);
		}*/
	}

	sockfd = Server::createListener(port_no, false);

    SelEpolKqEvPrt selEpolKqEvPrtHandler;
    selEpolKqEvPrtHandler.initialize(sockfd);

    ofstream ofs("serv.ctrl");
    ofs << "Process" << flush;
    ofs.close();
    logger << "listening on port "<< port_no;

    //Server server(admin_port_no,false,500,&serviceAdmin,2);

    CacheMap::init();

    ifstream ifs("serv.ctrl");
    while(ifs.is_open())
	{
    	nfds = selEpolKqEvPrtHandler.getEvents();
		if (nfds == -1)
		{
			perror("event handler main process");
			if(errno==EBADF)
				logger << "\nInavlid fd" <<flush;
			else if(errno==EFAULT)
				logger << "\nThe memory area pointed to by events is not accessible" <<flush;
			else if(errno==EINTR)
				logger << "\ncall was interrupted by a signal handler before any of the requested events occurred" <<flush;
			else if(errno==EINVAL)
				logger << "not a poll file descriptor, or maxevents is less than or equal to zero" << endl;
			else
				logger << "\nnot an epoll file descriptor" <<flush;
		}
		for(int n=0;n<nfds;n++)
		{
			int descriptor = selEpolKqEvPrtHandler.getDescriptor(n);
			if (descriptor == sockfd)
			{
				new_fd = -1;
				sin_size = sizeof their_addr;
				new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
				if (new_fd == -1)
				{
					perror("accept");
					continue;
				}
				else
				{
					selEpolKqEvPrtHandler.reRegisterServerSock();
					selEpolKqEvPrtHandler.registerForEvent(new_fd);
				}
			}
			else if (descriptor!=-1)
			{
				selEpolKqEvPrtHandler.unRegisterForEvent(descriptor);
				char buf[10];
				int err;
				if((err=recv(descriptor,buf,10,MSG_PEEK))==0)
				{
					close(descriptor);
					continue;
				}

				fcntl(descriptor, F_SETFL, O_SYNC);

				ServiceHandler *task = new ServiceHandler(descriptor, &props, isServerSSL, ctx, sSLHandler);
				Thread pthread(&service, task);
				pthread.execute();
			}
		}
	}
    ifs.close();
}
