Vektor Game Engine
==============

Installation
==============

Run `./make.sh && sudo ./make.sh install && ./make.sh clean` to build, install, and clean Vektor Game Engine

Usage
==============
```C
#include <vektor.h>

int main(void)
{
	vektor_init("Hello, World!");
	vektor_run();

	// add stuff to scenegraph

	vektor_quit(NULL);
	return 0;
}

```
