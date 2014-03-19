#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "write_file.h"
#include "read_file.h"
#include "command.h"




void init_screen();
WINDOW *title_window;
WINDOW *game_window;
WINDOW *command_window;
WINDOW *note_window;
const char TITLE[] = "PACMAN EDITOR";
const char VERSION[] = "@version 1.0";
const char CREATOR[] = "@created by THE THUNDER";	



const int TITLE_HEIGHT = 3;

const int GAME_WIDTH = 65;
const int GAME_HEIGHT = 35;
const int GAME_STARTY = 6;

const int COMMAND_HEIGHT = 3;
const int COMMAND_STARTY = 41;
// typedef struct _WIN_struct {

// 	int startx, starty;
// 	int height, width;

// }WIN;

int main(int argc, char *argv[])
{
    init_screen();
    int ch;
    while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	
			case ':':

				start_command_window(command_window, COMMAND_STARTY);
				int isEnter=0;
				int input;
				const char s[2] = " ";
				while((input = getch())!=27){
					isEnter = 0;
					start_command_window(command_window, COMMAND_STARTY);
					waddch(command_window,input);
					wrefresh(command_window);
					if(input == KEY_BACKSPACE || input == KEY_DC){
						wclear(command_window);
						waddch(command_window, ':');
						wrefresh(command_window);
					}else if(input == 10 && isEnter == 0){
						isEnter =1;
						wclear(command_window);
						waddch(command_window, ':');
						wrefresh(command_window);
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
						wclear(command_window);
						waddch(command_window, ':');
						if(strcmp(commands,"q")==0){
							endwin();			/* End curses mode		  */
							//return 0;
						}else if(strcmp(commands,"w")==0 && str_recieve[1]== NULL){
							wprintw(command_window,"write to this file ");
							wrefresh(command_window);
							getch();
							start_command_window(command_window, COMMAND_STARTY);
						}else if(strcmp(str_recieve[0],"w") == 0 && str_recieve[1] != NULL){
							wprintw(command_window,"sucessfully write to ");
							wprintw(command_window, str_recieve[1]);
							wrefresh(command_window);
							getch();
							start_command_window(command_window, COMMAND_STARTY);
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]== NULL){
							wprintw(command_window,"write to this file and will quit");
							wrefresh(command_window);
							getch();
							stop_command_window(command_window, 0,0);
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]!= NULL){
							wprintw(command_window,"sucessfully write to ");
							wprintw(command_window, str_recieve[1]);
							wprintw(command_window, " and will quit");
							wrefresh(command_window);
							getch();
							stop_command_window(command_window, 0,0);
						}else if(strcmp(str_recieve[0],"r") == 0 && str_recieve[1] != NULL){

							FILE *f = fopen("../levels/level1.pac", "r");
						    fgets(s, 100, f);
						    //memcpy(author, s, 100);
						    fgets(s, 100, f);
						    //memcpy(map_name, s, 100);
						    fgets(s, 100, f);
						    int map_col;
						  	int map_row;
						    map_row=atoi(s);
						    fgets(s, 100, f);
						    map_col=atoi(s)+1;
						    //4 is the right
						    char map[map_row][map_col];
						   	readFile(game_window,map_row,map_col,map,s);
						    fclose(f);
						    


							wprintw(command_window,"sucessfully read from ");
							wprintw(command_window, str_recieve[1]);
							wrefresh(command_window);
							getch();
							start_command_window(command_window, COMMAND_STARTY);
						}else if(strcmp(str_recieve[0],"n") == 0 && str_recieve[1] != NULL 
							&& str_recieve[2] != NULL && str_recieve[3] != NULL){
							int height = atoi(str_recieve[2]);
							int width = atoi(str_recieve[3]);
							wprintw(command_window,"sucessfully create new file with height =");
							waddch(command_window, height);
							wprintw(command_window," and width = ");
							waddch(command_window, width);
							wrefresh(command_window);
							getch();
							start_command_window(command_window, COMMAND_STARTY);
						}else {
							wprintw(command_window, "Can't recognise that commands! Sorry!");
							wrefresh(command_window);
							getch();
							isEnter = 0;
							start_command_window(command_window, COMMAND_STARTY);
						}
					}
					}
				}
				isEnter = 0;
				stop_command_window(command_window, 0, 0);
				refresh();
				break;
		}
	}
		
	endwin();			/* End curses mode		  */
	return 0;
}

void init_screen(){
	initscr();	
	int row,col;
	getmaxyx(stdscr,row,col);
	cbreak();
	keypad(stdscr, TRUE);

	char pacman[] = "pacman | ";
	char ghost[] = "ghost | ";
	char pellet[] = "pellet | ";
	char super_pellet[] ="super pellet | ";
	char fruit[] = "fruit";

	int note_length = strlen(pacman) + strlen(ghost) + strlen(pellet) + strlen(super_pellet) + strlen(fruit) + 5;

	
	getmaxyx(stdscr,row,col);
	title_window = create_new_win(TITLE_HEIGHT, col, 0, 0);
	game_window = create_new_win(GAME_HEIGHT, GAME_WIDTH, GAME_STARTY, col/2);
	command_window = create_new_win(COMMAND_HEIGHT, col, COMMAND_STARTY, 0);
	note_window = create_new_win(TITLE_HEIGHT, col, 4, (col - note_length)/2);
	refresh();
	
	mvwprintw(title_window,0,(col-strlen(TITLE))/2,"%s",TITLE);
	mvwprintw(title_window,1,col/2 + strlen(TITLE)/2,"%s",VERSION);
	mvwprintw(title_window,2,col/2 + strlen(TITLE)/2,"%s",CREATOR);


	waddch(note_window,ACS_DIAMOND);
	wprintw(note_window,pacman);
	
	waddch(note_window, ACS_CKBOARD);
	wprintw(note_window, ghost);

	waddch(note_window, ACS_BULLET);
	wprintw(note_window, pellet);

	waddch(note_window, ACS_DEGREE);
	wprintw(note_window, super_pellet);

	waddch(note_window, ACS_STERLING);
	wprintw(note_window, fruit);
	wrefresh(note_window);
	int i;

	for(i =0; i< col;i++){
		mvprintw(5,i,"%s","-");
	}

	wrefresh(title_window);
	wprintw(game_window,"");
	wrefresh(game_window);
	wprintw(command_window,"\n");

	for(i =0; i< col;i++){
		mvprintw(40,i,"%s","-");
	}

	mvwprintw(command_window,0,0,"%s", " To enable command mode, type ':' ");
	wrefresh(command_window);


}
