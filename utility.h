#ifndef UTILITY_H
#define UTILITY_H

void see_color_content(int y_pos, int x_pos, int color_num);
void print_array(int y_pos, int x_pos, int *array, int size);
void print_int(int y_pos, int x_pos, int integer);
int *int_to_bin64(unsigned long integer);
int *int_to_bin(int integer);

#endif
