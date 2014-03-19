#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"
#include "read_file.h"

void start_command_window(WINDOW *command_win,int y_cor){
	wclear(command_win);
	waddch(command_win,':');
	wprintw(command_win, "Commands enabled..type enter to begin!");
	noecho();
	move(y_cor,1);
	refresh();
	wrefresh(command_win);
}

void stop_command_window(WINDOW *command_win, int y_cor, int x_cor){
	wclear(command_win);
	wrefresh(command_win);
	move(y_cor,x_cor);
	refresh();
}

void command_loop(WINDOW *command_win, int starty){
	int isEnter =0;
	start_command_window(command_win, starty);
	int input;
	const char s[2] = " ";
	while((input = getch())!=27){
		isEnter = 0;
		start_command_window(command_win, starty);
		waddch(command_win,input);
		wrefresh(command_win);
		if(input == KEY_BACKSPACE || input == KEY_DC){
			wclear(command_win);
			waddch(command_win, ':');
			wrefresh(command_win);
		}else if(input == 10 && isEnter == 0){
			isEnter =1;
			wclear(command_win);
			waddch(command_win, ':');
			wrefresh(command_win);
			echo();
			char commands[60];
			getnstr(commands,59);

			if(strlen(commands)!=0){
			char *token;
			char *str_recieve[3];
						   
			/* get the first token */
			token = strtok(commands, s);
			str_recieve[0] = token;
			token = strtok(NULL, s);
			str_recieve[1] = token;
			token = strtok(NULL, s);
			str_recieve[2] = token;
			token = strtok(NULL, s);
			str_recieve[3] = token;
			wclear(command_win);
			waddch(command_win, ':');
			if(strcmp(commands,"q")==0){
				endwin();			/* End curses mode		  */
				//return 0;
			}else if(strcmp(commands,"w")==0 && str_recieve[1]== NULL){
				wprintw(command_win,"write to this file ");
				wrefresh(command_win);
				getch();
				start_command_window(command_win, starty);
			}else if(strcmp(str_recieve[0],"w") == 0 && str_recieve[1] != NULL){
				wprintw(command_win,"sucessfully write to ");
				wprintw(command_win, str_recieve[1]);
				wrefresh(command_win);
				getch();
				start_command_window(command_win, starty);
			}else if(strcmp(commands,"wq")==0 && str_recieve[1]== NULL){
				wprintw(command_win,"write to this file and will quit");
				wrefresh(command_win);
				getch();
				stop_command_window(command_win, 0,0);
			}else if(strcmp(commands,"wq")==0 && str_recieve[1]!= NULL){
				wprintw(command_win,"sucessfully write to ");
				wprintw(command_win, str_recieve[1]);
				wprintw(command_win, " and will quit");
				wrefresh(command_win);
				getch();
				stop_command_window(command_win, 0,0);
			}else if(strcmp(str_recieve[0],"r") == 0 && str_recieve[1] != NULL){




				wprintw(command_win,"sucessfully read from ");
				wprintw(command_win, str_recieve[1]);
				wrefresh(command_win);
				getch();
				start_command_window(command_win, starty);
			}else if(strcmp(str_recieve[0],"n") == 0 && str_recieve[1] != NULL 
				&& str_recieve[2] != NULL && str_recieve[3] != NULL){
				int height = atoi(str_recieve[2]);
				int width = atoi(str_recieve[3]);
				wprintw(command_win,"sucessfully create new file with height =");
				waddch(command_win, height);
				wprintw(command_win," and width = ");
				waddch(command_win, width);
				wrefresh(command_win);
				getch();
				start_command_window(command_win, starty);
			}else {
				wprintw(command_win, "Can't recognise that commands! Sorry!");
				wrefresh(command_win);
				getch();
				isEnter = 0;
				start_command_window(command_win, starty);
			}
		}
		}
	}
	isEnter = 0;
	stop_command_window(command_win, 0, 0);
	refresh();
}



