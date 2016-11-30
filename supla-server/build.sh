#!/bin/sh

OS=`uname -s`

case $OS in
Darwin)
	export CFLAGS="-I/opt/local/include -I/opt/local/include/mysql"
	export CPPFLAGS="-I/opt/local/include -I/opt/local/include/mysql"
	export LDFLAGS=-L/opt/local/lib
	;;
Linux)
	export CFLAGS="-I/usr/include/mysql"
	export CPPFLAGS="-I/usr/include/mysql"
	export LDFLAGS=
	;;
esac


make -C Release clean
make -C Release all
