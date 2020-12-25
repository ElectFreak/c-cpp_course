hw_01: obj/main.o obj/bmp.o obj/stego.o
	gcc obj/main.o obj/bmp.o obj/stego.o -o hw_01

obj/main.o: src/main.c | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -c -I include src/bmp.c -o obj/bmp.o

obj/stego.o: src/stego.c include/stego.h | obj
	gcc -c -I include src/stego.c -o obj/stego.o

obj: 
	mkdir obj

.PHONY: clean
clean: 
	rm -rf obj hw_01