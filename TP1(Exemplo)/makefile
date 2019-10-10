all:	shellso

shellso:	main.o	shellso.o	io.o
	gcc	main.o	shellso.o	io.o	-o	shellso

main.o:	main.c	shellso.c	io.c
	gcc	-c	-Wall	shellso.c
	gcc	-c	-Wall	main.c
	gcc	-c	-Wall	io.c

clean:
	rm main.o	shellso.o	io.o	shellso