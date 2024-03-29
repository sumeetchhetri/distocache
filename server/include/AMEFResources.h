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

#ifndef AMEFRESOURCES_H_
#define AMEFRESOURCES_H_

#include "AMEFEncoder.h"
#include "AMEFDecoder.h"

class AMEFResources
{
	AMEFResources(){}
	~AMEFResources();
public:

	static char* longTocharArray(long l,int ind)
	{
		char* result = new char[ind];
		for (int i = 0; i<ind; i++)
		{
			int offset = (ind - 1 - i) * 8;
            result[i] = (char) ((l >> offset) & 0xFF);
		}
        return result;
    }

	static string longTocharArrayS(long l,int ind)
	{
		char* result = new char[ind];
		for (int i = 0; i<ind; i++)
		{
			int offset = (ind - 1 - i) * 8;
            result[i] = (char) ((l >> offset) & 0xFF);
		}
		string tem(result);
		return tem;
    }

	static char* intTocharArray(int l,int ind)
	{
		char* result = new char[ind];
		for (int i = 0; i<ind; i++)
		{
			int offset = (ind - 1 - i) * 8;
            result[i] = (char) ((l >> offset) & 0xFF);
		}
        return result;
    }

	static char* intTocharArrayWI(int l)
	{
		int ind = 1;
		if(l<256)
			ind =1;
		else if(l<65536)
			ind = 2;
		else if(l<16777216)
			ind =3;
		else
			ind =4;
		char* result = new char[ind];
		for (int i = 0; i<ind; i++)
		{
			int offset = (ind - 1 - i) * 8;
            result[i] = (char) ((l >> offset) & 0xFF);
		}
        return result;
    }

	static int charArrayToInt(char l[])
	{
		int t = 0;
		int ind = sizeof l;
        for (int i = 0; i < ind; i++)
		{
        	int offset = (ind -1 - i) * 8;
        	t += (l[i] & 0x000000FF) << offset;
		}
        return t;
    }

	static int charArrayToInt(char* l,int off,int ind)
	{
		int t = 0;
		for (int i = 0; i < ind; i++)
		{
        	int offset = (ind -1 - i) * 8;
        	t += (l[off+i] & 0x000000FF) << offset;
		}
        return t;
    }

	static long charArrayToLong(char l[])
	{
		long t = 0;
		int ind = sizeof l;
        for (int i = 0; i < ind; i++)
		{
        	int offset = (ind -1 - i) * 8;
        	t += (l[i] & 0x000000FF) << offset;
		}
        return t;
    }
	static long charArrayToLong(char* l,int off,int ind)
	{
		long t = 0;
		for (int i = 0; i < ind; i++)
		{
        	int offset = (ind -1 - i) * 8;
        	t += (l[off+i] & 0x000000FF) << offset;
		}
        return t;
    }
	static long charArrayToLong(char* l,int ind)
	{
		long t = 0;
		for (int i = 0; i < ind; i++)
		{
        	int offset = (ind -1 - i) * 8;
        	t += (l[i] & 0x000000FF) << offset;
		}
        return t;
    }

	static string intTocharArrayS(int l, int ind)
	{
		char* result = new char[ind];
		for (int i = 0; i<ind; i++)
		{
			int offset = (ind - 1 - i) * 8;
            result[i] = (char) ((l >> offset) & 0xFF);
		}
		string tem(result);
        return tem;
    }
	#ifdef IS_64_BIT
		static string longTocharArrayWI(unsigned long long l)
		{
			int ind = 1;
			if(l<256)
				ind =1;
			else if(l<65536)
				ind = 2;
			else if(l<16777216)
				ind =3;
			else if(l<4294967296ULL)
				ind =4;
			else if(l<1099511627776ULL)
				ind =5;
			else if(l<281474976710656ULL)
				ind =6;
			else if(l<72057594037927936ULL)
				ind =7;
			else
				ind =8;
			string result;
			for (int i = 0; i<ind; i++)
			{
				int offset = (ind - 1 - i) * 8;
				result.push_back((char) ((l >> offset) & 0xFF));
			}
			return result;
		}
		static string longTocharArrayWI(long l)
		{
			int ind = 1;
			if(l<256)
				ind =1;
			else if(l<65536)
				ind = 2;
			else if(l<16777216)
				ind =3;
			else if(l<(long)4294967296ULL)
				ind =4;
			else if(l<(long)1099511627776ULL)
				ind =5;
			else if(l<(long)281474976710656ULL)
				ind =6;
			else if(l<(long)72057594037927936ULL)
				ind =7;
			else
				ind =8;
			string result;
			for (int i = 0; i<ind; i++)
			{
				int offset = (ind - 1 - i) * 8;
				result.push_back((char) ((l >> offset) & 0xFF));
			}
			return result;
		}
	#else
		static string longTocharArrayWI(unsigned long long l)
		{
			int ind = 1;
			if(l<256)
				ind =1;
			else if(l<65536)
				ind = 2;
			else if(l<16777216)
				ind =3;
			else if(l<4294967296ULL)
				ind =4;
			else if(l<1099511627776ULL)
				ind =5;
			else if(l<281474976710656ULL)
				ind =6;
			else if(l<72057594037927936ULL)
				ind =7;
			else
				ind =8;
			string result;
			for (int i = 0; i<ind; i++)
			{
				int offset = (ind - 1 - i) * 8;
				result.push_back((char) ((l >> offset) & 0xFF));
			}
			return result;
		}
		static string longTocharArrayWI(long l)
		{
			int ind = 1;
			if(l<256)
				ind =1;
			else if(l<65536)
				ind = 2;
			else if(l<16777216)
				ind =3;
			else
				ind =4;
			string result;
			for (int i = 0; i<ind; i++)
			{
				int offset = (ind - 1 - i) * 8;
				result.push_back((char) ((l >> offset) & 0xFF));
			}
			return result;
		}
	#endif
};

#endif /* AMEFRESOURCES_H_ */
