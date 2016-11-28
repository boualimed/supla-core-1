#!/bin/sh

OS=`uname -s`

case $OS in
Darwin)
	export CFLAGS=-I/opt/local/include
	export CPPFLAGS=-I/opt/local/include
	export LDFLAGS=-L/opt/local/lib
	;;
Linux)
	export CFLAGS=
	export CPPFLAGS=
	export LDFLAGS=
	;;
esac


make -C Release clean
make -C Release all
