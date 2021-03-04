lab_07: obj/matrix.o obj/main.o
	g++ obj/matrix.o obj/main.o -o lab_07

obj: 
	mkdir obj

obj/main.o: include/matrix.h src/main.cpp | obj
	g++ -c -I include src/main.cpp -o obj/main.o

obj/matrix.o: include/matrix.h src/matrix.cpp | obj
	g++ -c -I include src/matrix.cpp -o obj/matrix.o

.PHONY: clean
clean: 
	rm -rf obj lab_07