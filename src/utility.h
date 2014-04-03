#ifndef UTILITY_H
#define UTILITY_H

#include "curses.h"

WINDOW create_new_win(int height, int width, int starty, int startx);
void init_screen(WINDOW *title_window, WINDOW *game_window, WINDOW *command_window, 
	WINDOW *note_window, WINDOW *wall, WINDOW *user_window, char user[], char user_email[]);
void init_user_info(WINDOW* user_window,char user[], char user_email[], char map_name[],
	 int map_row, int map_col, char author[], char author_email[]);

#endif