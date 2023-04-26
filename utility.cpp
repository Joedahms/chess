#include <curses.h>
#include <stdio.h>

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
