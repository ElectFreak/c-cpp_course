lab_04: obj/main.o obj/clist.o
	gcc obj/clist.o obj/main.o -o lab_04

obj: 
	mkdir obj

obj/main.o: src/main.c include/clist.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c -I include src/clist.c -o obj/clist.o

.PHONY: clean
clean: 
	rm -rf lab_04 obj