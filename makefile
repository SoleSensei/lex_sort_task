func.o: ./funcs/func.c ./include/func.h
	gcc -g -Wall -c ./funcs/func.c -o ./funcs/func.o
start: main.c ./funcs/func.o
	gcc -Wall -g main.c ./funcs/func.o -o start
