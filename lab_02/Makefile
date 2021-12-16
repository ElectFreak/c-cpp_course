test: obj/str.o obj/test_str.o obj/test.o
	gcc obj/str.o obj/test_str.o obj/test.o -o test

obj: 
	mkdir obj

obj/str.o: src/str.c include/str.h | obj
	gcc -c -I include src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c include/test_str.h | obj
	gcc -c -I include src/test_str.c -o obj/test_str.o

obj/test.o: src/test.c | obj
	gcc -c -I include src/test.c -o obj/test.o


.PHONY: clean
clean: 
	rm -rf obj test