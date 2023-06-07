#! /usr/bin/sh

CFLAGS="-Wall -Wextra -pedantic"

if [ ! -d "bin/" ]; then
	mkdir bin
fi

gcc $CFLAGS -o bin/vec.out src/vec.c
gcc $CFLAGS -o bin/ll.out src/ll.c
