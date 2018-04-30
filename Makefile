#ICP projekt 2017/2018
CC=g++
CFLAGS= -Wall -Werror -Wextra

all: beditor

beditor:
	@cd src && qmake -o Makefile && make
	mv src/blockeditor ./

clean:
	rm src/*.o -rf
	rm src/Makefile -rf
	rm ./blockeditor -rf	

run: beditor
	./blockeditor

doxygen:
	doxygen src/Doxyfile
