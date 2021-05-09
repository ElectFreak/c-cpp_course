FLAGS=-std=c++17 -I include

hw_02: obj/main.o
	g++ obj/main.o -o huffman

obj/main.o: src/main.cpp include/HuffmanArchiver.h include/Hufftree.h | obj
	g++ -c src/main.cpp $(FLAGS) -o obj/main.o

obj: 
	mkdir obj

clean:
	rm -rf obj hw_02