all:
	gcc -o everrust_ai everrust_ai.c -L. -lconnsix

clean:
	rm everrust_ai
