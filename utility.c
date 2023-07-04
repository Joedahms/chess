#include <curses.h>
#include <stdio.h>
#include <math.h>

#include "utility.h"

void see_color_content(int y_pos, int x_pos, int color_num) {
	short red;
	short green;
	short blue;

	char red_label[6] = "red: ";
	char green_label[8] = "green: ";
	char blue_label[7] = "blue: ";

	color_content(color_num, &red, &green, &blue);

	char red_str[3];
	char green_str[3];
	char blue_str[3];
	sprintf(red_str, "%d", red);	
	sprintf(green_str, "%d", green);	
	sprintf(blue_str, "%d", blue);	

	mvaddstr(y_pos, x_pos, red_label);
	mvaddstr(y_pos + 1, x_pos, green_label);
	mvaddstr(y_pos + 2, x_pos, blue_label);

	mvaddstr(y_pos, x_pos + 5, red_str);
	mvaddstr(y_pos + 1, x_pos + 7, green_str);
	mvaddstr(y_pos + 2, x_pos + 6, blue_str);
	refresh();
}

void print_array(int y_pos, int x_pos, int *array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		mvprintw(y_pos, x_pos, "%d", *array);
		x_pos += 2;
		mvaddch(y_pos, x_pos, ',');
		x_pos++;
		array++;
	}
	refresh;
}

void print_int(int y_pos, int x_pos, int integer) {	// print an integer
	char *string;					// mvaddstr wants a string
	sprintf(string, "%d", integer);			// convert integer to string so it can be printed
	mvaddstr(y_pos, x_pos, string);			// print it
}

int *int_to_bin64(unsigned long integer) {
	int i;
	int index = 0; // start point in array
	int power = 63;
	unsigned long rem; // remainder
	int bin_num[64];

	bin_num[index] = integer / (unsigned long)pow(2, power); // msb
	index++; // index = 1
	
	rem = integer % (unsigned long)pow(2, power); 
	power--;

	while (power >= 0) { // 2^n, n >= 0
		bin_num[index] = rem / (unsigned long)pow(2, power); // bit 
		rem = rem % (unsigned long)pow(2, power); // remainder
		power--;
		index++;
	}
	int *bin_num_ptr = &bin_num[0];
	return bin_num_ptr;
}


// take a decimal number and convert it to binary
int *int_to_bin(int integer) {
	int i;
	int index = 0; // start point in array
	int power = floor(log2f(integer)); // power of bit under msb
	int rem; // remainder
	int bin_num[64];

	bin_num[index] = integer / (int)pow(2, power); // msb
	index++; // index = 1
	
	rem = integer % (int)pow(2, power); 
	power--;

	while (power >= 0) { // 2^n, n >= 0
		bin_num[index] = rem / pow(2, power); // bit 
		rem = rem % (int)pow(2, power); // remainder
		power--;
		index++;
	}
	int *bin_num_ptr = &bin_num[0];
	return bin_num_ptr;
}
