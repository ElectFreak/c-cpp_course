lab_06: obj/main.o
	g++ --std=c++14 obj/main.o -o lab_06

obj/main.o: include/my_vector.h | obj
	g++ --std=c++14 src/main.cpp -c -I include -o obj/main.o

obj: 
	mkdir obj

clean: 
	rm -rf obj/main.o lab_06
