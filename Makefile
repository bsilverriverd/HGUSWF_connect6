all:
	gcc src/*.c -ICONNSIX-c/include -Iinclude -LCONNSIX-c/lib -lconnsix
