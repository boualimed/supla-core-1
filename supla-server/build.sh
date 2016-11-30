#!/bin/sh

OS=`uname -s`

case $OS in
Darwin)
	echo
	echo "macOS not supported!"
	echo
	exit 1
	;;
Linux)
	export CFLAGS="-I/usr/include/mysql"
	export CPPFLAGS="-I/usr/include/mysql"
	export LDFLAGS=
	;;
esac


make -C Release clean
make -C Release all
