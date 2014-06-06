Vektor Graphics Engine
==============

Installation
==============

Run `./make.sh && sudo ./make.sh install && ./make.sh clean` to build, install, and clean Vektor Graphics Engine

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

Compile with:

`cc -o vektor_test vektor_test.c -l:libvektor.a -I/usr/local/include -L/usr/local/lib -lGL -lncurses -lthr`
