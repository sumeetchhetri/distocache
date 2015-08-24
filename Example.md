## Example Code ##

```
//============================================================================
// Name        : distocacheclient.cpp
// Author      : Sumeet Chhetri
//============================================================================

#include <iostream>
#include "DistVector.h"
#include "DistMap.h"
using namespace std;

int main() {

	DistoCacheConnectionFactory::init("192.168.56.102", 7001);

	DistMap<string, int> dmap("MyMap");

	DistMap<string, int>::iterator it;
	dmap.insert(pair<string, int>("123", 123));
	dmap.insert(pair<string, int>("1234", 124));
	cout << dmap.size() <<endl;
	cout << dmap.at("123") << endl;
	cout << dmap["123"] << endl;

	for (it = dmap.begin();it!=dmap.end();it++) {
		cout << "map iter = " << it.get() << endl;
	}

	DistVector<string> dvec("MyVector");
	dvec.push_back("first");
	dvec.push_back("second");

	cout << dvec.size() << endl;

	//cout << dvec.at(10) << endl;
	cout << dvec.size() << endl;
	cout << dvec.isEmpty() << endl;

	dvec.erase(1);
	cout << dvec.size() << endl;

	DistVector<string>::iterator vit;
	for (vit = dvec.begin();vit!=dvec.end();vit++) {
		cout << "vector iter = " << vit.get() << endl;
	}

	dvec.clear();

	DistoCacheConnectionFactory::destroy();
	return 0;
}

```