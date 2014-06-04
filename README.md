Vektor Game Engine
==============

Installation
==============

Run `./make.sh && sudo ./make.sh install` to build and install Vektor Game Engine

Usage
==============
`
#include <vektor.h>

int main(void)
{
	vektor_init("Hello, World!");
	vektor_run();

	// add stuff to scenegraph

	vektor_quit(NULL);
	return 0;
}
`
