#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"
#include "read_file.h"

void start_command_window(WINDOW *command_win,int y_cor){
	cbreak();
	wclear(command_win);
	waddch(command_win,':');
	wprintw(command_win, "Commands enabled..type enter to begin!");
	move(y_cor,1);
	refresh();
	wrefresh(command_win);
}

void stop_command_window(WINDOW *command_win,WINDOW *game_window, int y_cor, int x_cor){
	wclear(command_win);
	wrefresh(command_win);
	wmove(game_window,y_cor-1,x_cor-2);
	refresh();
	wrefresh(game_window);
	noecho();
}



