main: obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab_03

mainG: obj/mergesort.o obj/main.o
	gcc -g obj/mergesort.o obj/main.o -o lab_03

obj: 
	mkdir obj

obj/main.o: src/main.c include/mergesort.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc -c -I include src/mergesort.c -o obj/mergesort.o

.PHONY: clean
clean: 
	rm -rf lab_03 obj
