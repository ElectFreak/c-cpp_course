lab_13: obj/main.o 
	g++ -std=c++17 obj/main.o -o lab_13

obj/main.o: src/main.cpp include/my_array.h | obj
	g++ -c -std=c++17 -Iinclude src/main.cpp -o obj/main.o

obj: 
	mkdir obj

clean:
	rm -rf obj lab_13