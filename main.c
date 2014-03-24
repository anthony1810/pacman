#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"
#include "command.h"


void int_window();

int main(int argc, char *argv[])
{	
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	height = 6;
	width = 5;
	starty = 10;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	refresh();

	my_win = create_new_win(height, width, starty, startx);

    waddch(my_win,ACS_ULCORNER);
    waddch(my_win,ACS_LLCORNER);
    waddch(my_win,ACS_URCORNER);
    waddch(my_win,ACS_LRCORNER);
    waddch(my_win,ACS_LTEE);
    waddch(my_win,ACS_RTEE);
    waddch(my_win,ACS_BTEE);
    waddch(my_win,ACS_TTEE);
    waddch(my_win,ACS_HLINE);
    waddch(my_win,ACS_VLINE);
    waddch(my_win,ACS_BULLET);
    waddch(my_win,ACS_DEGREE);
    waddch(my_win,ACS_STERLING);
    int map_row;
    map_row = 12;
    int map_col;
    map_col = 16;

	wrefresh(my_win);
	write_to_file("level3", "Anthony", "qquang269@gmail.com", my_win,6, 5);
	getch();
	
		
	endwin();			/* End curses mode		  */
	return 0;
}

