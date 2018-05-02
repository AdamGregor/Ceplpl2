# ICP projekt 2017/2018 
# Makefile
# Adam Gregor, xgrego18
# Zdenek Jelinek, xjelin47
CC=g++
CFLAGS= -Wall -Werror -Wextra

all: beditor

beditor:
	@cd src && qmake -o Makefile && make
	mv src/blockeditor ./

pack: clean
	zip xjelin47-xgrego18.zip Makefile ./doc ./src/* examples README.txt

clean:
	rm src/*.o -rf
	rm src/Makefile -rf
	rm ./blockeditor -rf
	rm ./doc/* -rf
	rm -rf xjelin47-xgrego18.zip
	rm src/*.user -rf	

run: beditor
	./blockeditor

doxygen:
	-mkdir doc
	doxygen src/Doxyfile
