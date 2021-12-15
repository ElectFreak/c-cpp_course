lab_05: obj/clist.o obj/main.o obj/point_list.o 
	gcc obj/clist.o obj/point_list.o obj/main.o -o lab_05

obj: 
	mkdir obj

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c -I include src/clist.c -o obj/clist.o

obj/main.o: src/main.c include/point_list.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/point_list.o: src/point_list.c include/point_list.h | obj
	gcc -c -I include src/point_list.c -o obj/point_list.o

.PHONY: clean
clean: 
	rm -rf obj lab_05 