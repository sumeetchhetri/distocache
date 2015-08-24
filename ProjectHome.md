## Introduction ##
<font size='3' face='Georgia, Arial'>
Provides an implementation for distributed STL containers<br>
</font>

## Features ##
<font size='3' face='Georgia, Arial'>
<ul><li>Implementations available for<br>
<ol><li>Vector<br>
</li><li>Deque<br>
</li><li>List<br>
</li><li>Set<br>
</li><li>Map<br>
</li><li>Queue<br>
</li></ol></li><li>Iterator available for the distributed containers<br>
</li><li>Conforms to the major STL functions<br>
</li><li>Can be used like an In memory cache<br>
</font></li></ul>

## Usage ##

<font size='3' face='Georgia, Arial'>
Include the required distributed stl headers<br>
</font>
```
#include "DistVector.h" //For Vector
#include "DistList.h"    //For List
#include "DistDeque.h"    //For Deque
#include "DistQueue.h"    //For Queue
#include "DistSet.h"    //For Set
#include "DistMap.h"    //For Map
```

<font size='3' face='Georgia, Arial'>
Initialize the Distributed cache connection factory<br>
</font>
```
DistoCacheConnectionFactory::init("loalhost", 7001); //Provide the ip and port for the cache
```

<font size='3' face='Georgia, Arial'>
Create/Get the distributed STL instance<br>
</font>
```
DistMap<string, int> dmap("MyMap"); //Get/create a distributed stl map instance
```

<font size='3' face='Georgia, Arial'>
Use the distributed STL instance normally<br>
</font>
```
DistMap<string, int>::iterator it; //Get the map iterator
dmap.insert(pair<string, int>("123", 123)); //Insert a key/value pair
dmap.insert(pair<string, int>("1234", 124));
cout << dmap.size() <<endl;  //Get the map size
cout << dmap.at("123") << endl; //Get a value
cout << dmap["123"] << endl; //Get value

//Use iterator
for (it = dmap.begin();it!=dmap.end();it++) {
	cout << "map iter = " << it.get() << endl;
}
```

<font size='3' face='Georgia, Arial'>
Destroy the Distributed cache connection factory<br>
</font>
```
DistoCacheConnectionFactory::destroy();
```

<font size='3' face='Georgia, Arial'>
That's all, its that simple...<br>
Show me the <a href='https://code.google.com/p/distocache/source/browse/'>code</a>

To build the code<br>
<ol><li>Download the code, <b>svn checkout <a href='http://distocache.googlecode.com/svn/trunk/'>http://distocache.googlecode.com/svn/trunk/</a></b>
</li><li>To build server Debug version, go to trunk/server/Debug <b>make all</b>
</li><li>To build client Debug version, go to trunk/client/Debug <b>make all</b>
</font>