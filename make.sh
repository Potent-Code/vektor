#!/bin/sh

# if no arguments are given, we just want to build
if [ "$1" == "" ]; then
	echo "Building Vektor..."
	bam $BAMFLAGS -a Mode=Debug
elif [ "$1" == "install" ]; then
	cp libvektor.a /usr/local/lib/ &&
	cp libvektor.so /usr/local/lib/ &&
	cp src/include/vektor.h /usr/local/include/ &&
	cp vektor_maketexture /usr/local/bin/ &&
	cp vektor_makemodel /usr/local/bin || exit 1
	echo "libvektor.a -> /usr/local/lib/"
	echo "libvektor.so -> /usr/local/lib/"
	echo "src/include/vektor.h -> /usr/local/include/"
	echo "vektor_maketexture -> /usr/local/bin/"
	echo "vektor_makemodel -> /usr/local/bin/"
elif [ "$1" == "clean" ]; then
	echo "removing obj/"
	echo "removing libvektor.*"
	echo "removing vektor_maketexture"
	echo "removing vektor_makemodel"
	rm -fR obj libvektor.* vektor_maketexture vektor_makemodel
else
	echo "Usage:"
	echo -e "\t$0\t\tBuild"
	echo -e "\t$0 install\tInstall to /usr/local/lib, /usr/local/include, and /usr/local/bin"
	echo -e "\t$0 clean\t\tClean build outputs"
fi
