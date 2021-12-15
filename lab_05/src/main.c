#include <string.h>
#include <stdio.h>

#include "point_list.h"

static void int_to_little_endian(const int n, unsigned char* const buf) {
    for (int i = 0; i < 3; i++) {
        buf[i] = (unsigned char)((n >> 8*i) & 0xFF);
    }
}

static void little_endian_to_int(const unsigned char* buf, int* const n) {
    *n = 0;
    for (int i = 0; i < 3; i++) {
        *n |= ((int)buf[i]) << 8*i;
    }

    if (buf[2] & 0x80) { // complement to two case
        *n |= 0xFF000000;
    }
}

static void save_point_text(intrusive_node* node, void* outfile) {
    if (ftell((FILE*)outfile) != 0) 
        fprintf((FILE*)outfile, "\n");
    point_node* point = get_point(node);
    fprintf((FILE*)outfile, "%d %d", point->x, point->y);

}

static void save_point_bin(intrusive_node* node, void* outfile) {
    point_node* point = get_point(node);  
    unsigned char to_write[3];
    int_to_little_endian(point->x, to_write);
    fwrite(to_write, sizeof(unsigned char), 3, (FILE*)outfile);
    int_to_little_endian(point->y, to_write);
    fwrite(to_write, sizeof(unsigned char), 3, (FILE*)outfile);
}

static void print_point(intrusive_node* node, void* fmt) {
    point_node* point = get_point(node);
    printf((char*)fmt, point->x, point->y);
}

static void count(intrusive_node* node, void* counter) {
    (void)node;
    (*(int*)counter)++;
}

int main(int argc, char** argv) {
    intrusive_list list;
    init_list(&list);

    if (strcmp(argv[1], "loadtext") == 0) {
        FILE* infile = fopen(argv[2], "r");
        int x, y;
        while (fscanf(infile, "%d %d", &x, &y) == 2) {
            add_point(&list, x, y);
        }
        fclose(infile);
    }

    if (strcmp(argv[1], "loadbin") == 0) {
        FILE* infile = fopen(argv[2], "rb");
        unsigned char buf[6];
        int x, y;
        while (fread(buf, sizeof(unsigned char), 6, infile) == 6) {            
            little_endian_to_int(&buf[0], &x);
            little_endian_to_int(&buf[3], &y);

            add_point(&list, x, y);
        } 
        fclose(infile);
    }

    if (strcmp(argv[3], "savetext") == 0) {
        FILE* outfile = fopen(argv[4], "w");
        apply(&list, save_point_text, (void*)outfile);
        fclose(outfile);
    }

    if (strcmp(argv[3], "savebin") == 0) {
        FILE* outfile = fopen(argv[4], "wb");
        apply(&list, save_point_bin, (void*)outfile);
        fclose(outfile);
    }

    if (strcmp(argv[3], "print") == 0) {
        apply(&list, print_point, argv[4]);
        printf("\n");
    }

    if (strcmp(argv[3], "count") == 0) {
        int counter = 0;
        apply(&list, count, &counter);
        printf("%d\n", counter);
    }

    remove_all_points(&list);

    return 0;
}