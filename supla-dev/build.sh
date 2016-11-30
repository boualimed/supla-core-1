#!/bin/sh

OS=`uname -s`

case $OS in
Darwin)
	echo
	echo "macOS not supported!"
	echo
	;;
Linux)
	export CFLAGS=
	export CPPFLAGS=
	export LDFLAGS=
	;;
esac


make -C Release clean
make -C Release all
