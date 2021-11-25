all:
	gcc src/*.c -g -ICONNSIX-c/include -Iinclude -LCONNSIX-c/lib -lconnsix
