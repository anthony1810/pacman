#include "utility.h"
#include <stdlib.h>
//#include <curses.h>
#include <string.h>
#include "constant.h"

WINDOW create_new_win(int height, int width, int starty, int startx)
{	
	WINDOW local_win;
	local_win = *newwin(height, width, starty, startx);
	return local_win;

}
void init_screen(WINDOW *title_window, WINDOW *game_window, WINDOW *command_window, WINDOW *note_window,
 WINDOW *wall, WINDOW *user_window, char user[], char user_email[]){
	initscr();	

	if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WALL,    COLOR_BACKGROUND);
        init_pair(2, COLOR_PACMAN,  COLOR_BACKGROUND);
		init_pair(3, COLOR_GHOST,  COLOR_BACKGROUND);
		init_pair(4, COLOR_FRUIT,  COLOR_BACKGROUND);
		init_pair(5, COLOR_PELLET,  COLOR_BACKGROUND);
		init_pair(6, COLOR_YELLOW, COLOR_BACKGROUND);
		init_pair(7, 5, COLOR_BACKGROUND);
		init_pair(8, COLOR_GREEN, COLOR_BACKGROUND);
    }
    int counter =0;
    printw("Welcome to");
	attron(COLOR_PAIR(6) | A_BOLD);
	printw(" Pacman Editor");
	attroff(COLOR_PAIR(6) | A_BOLD);
	printw(" powered by");
	attron(COLOR_PAIR(5) | A_BOLD);
	printw(" The Thunder Corp");
	attroff(COLOR_PAIR(5) | A_BOLD);
	printw(".\n\n");
	printw("Please Tell me your name (30 letters) and email (50 letters) so i can save new map under your\nidentity, Thank you! \n\n");
	//getch();

    while(strlen(user) < 2 && strlen(user_email) < 2){
    	if(counter >= 1){
    		attron(COLOR_PAIR(3) | A_BOLD);
    		printw("Don't do that trick on me, Laziness is a big crime. Be mature! \n");
    		attroff(COLOR_PAIR(3) | A_BOLD);
    	}
    	counter +=1;
		attron(A_UNDERLINE);
		printw("Your Name:");
		attroff(A_UNDERLINE);
		printw(" ");
		getnstr(user,30);
		attron(A_UNDERLINE);
		printw("Your Email:");
		attroff(A_UNDERLINE);
		printw(" ");
		getnstr(user_email,50);
	}
	clear();
	int row,col;
	getmaxyx(stdscr,row,col);
	raw();			/**< Line buffering disabled	 */
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();

	


	int note_length = strlen(pacman) + strlen(ghost) + strlen(pellet) + strlen(super_pellet) + strlen(fruit) + (strlen(sepChar)*5)+5;
	
	*title_window = create_new_win(TITLE_HEIGHT, col, 0, 0);
	*game_window = create_new_win(GAME_HEIGHT, GAME_WIDTH, GAME_STARTY, col/2);
	*command_window = create_new_win(COMMAND_HEIGHT, col, COMMAND_STARTY, 0);
	*note_window = create_new_win(TITLE_HEIGHT, col, 4, (col - note_length)/2);
	int user_window_width = 27;
	int user_window_startY = TITLE_HEIGHT+3;
	*user_window = create_new_win(10, user_window_width, user_window_startY,1) ;
	*wall = create_new_win(GAME_HEIGHT+2,1,user_window_startY-2,user_window_width+2);
	refresh();
	wrefresh(user_window);

	for(int i=0;i<GAME_HEIGHT;i++){
		mvwprintw(wall,i,0,"%s", "|");
	}
	wrefresh(wall);
	wattron(title_window,A_BOLD);
	wattron(title_window,COLOR_PAIR(6));
	mvwprintw(title_window,0,(col-strlen(TITLE))/2,"%s",TITLE);
	wattroff(title_window,A_BOLD);  
	mvwprintw(title_window,1,col/2 + strlen(TITLE)/2,"%s",VERSION);
	mvwprintw(title_window,2,col/2 + strlen(TITLE)/2,"%s",CREATOR);
	wattroff(title_window,COLOR_PAIR(6)); 

	wattron(note_window,COLOR_PAIR(2));
	waddch(note_window,ACS_DIAMOND);
	wattron(note_window,COLOR_PAIR(1));
	wprintw(note_window,pacman);
	wprintw(note_window,sepChar);


	wattron(note_window,COLOR_PAIR(3));
	waddch(note_window, ACS_CKBOARD);
	wattron(note_window,COLOR_PAIR(1));
	wprintw(note_window, ghost);
	wprintw(note_window,sepChar);
	

	wattron(note_window,COLOR_PAIR(5));
	waddch(note_window, ACS_BULLET);
	wattron(note_window,COLOR_PAIR(1));
	wprintw(note_window, pellet);
	wprintw(note_window,sepChar);
	
	
	wattron(note_window,COLOR_PAIR(4));
	waddch(note_window, ACS_STERLING);
	wattron(note_window,COLOR_PAIR(1));
	wprintw(note_window, fruit);
	wprintw(note_window,sepChar);


	wattron(note_window,COLOR_PAIR(5));
	waddch(note_window, ACS_DEGREE);
	wattron(note_window,COLOR_PAIR(1));
	wprintw(note_window, super_pellet);
	
	
	wrefresh(note_window);

	init_user_info(user_window,user, user_email, "",0,0,"","");
	int i;

	for(i =0; i< col;i++){
		mvprintw(5,i,"%s","-");
	}

	wrefresh(title_window);
	wprintw(game_window,"");
	wrefresh(game_window);
	wprintw(command_window,"\n");

	for(i =0; i< col;i++){
		mvprintw(41,i,"%s","-");
	}
	curs_set(0);
	wattron(command_window,COLOR_PAIR(6));
	mvwprintw(command_window,0,0,"%s", "To enable command mode, type ':' ");
	wattroff(command_window,COLOR_PAIR(6));
	wrefresh(command_window);
}

void init_user_info(WINDOW* user_window,char user[], char user_email[], char map_name[], int map_row, int map_col, char author[], char author_email[]){
	wclear(user_window);
	wattron(user_window,A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
	wprintw(user_window, "User Info\n");
	wattroff(user_window,A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
	wprintw(user_window, "User:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window, user);
	wattroff(user_window,COLOR_PAIR(2));
	wprintw(user_window, "\n");

	wprintw(user_window,"Email:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window, user_email);
	wattroff(user_window,COLOR_PAIR(2));


	wprintw(user_window,"\n\n");
	wattron(user_window,A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
	wprintw(user_window, "Map Info\n");
	wattroff(user_window,A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);

	wprintw(user_window, "Title:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window,map_name );
	wattroff(user_window,COLOR_PAIR(2));
	wprintw(user_window, "\n");

	wprintw(user_window,"Creator:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window, author);
	wattroff(user_window,COLOR_PAIR(2));
	wprintw(user_window, "\n");

	wprintw(user_window,"Email:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window, author_email);
	wattroff(user_window,COLOR_PAIR(2));
	wprintw(user_window, "\n");

	wprintw(user_window,"Dimesion:");
	wprintw(user_window, " ");
	wattron(user_window,COLOR_PAIR(2));
	wprintw(user_window,"%i" ,map_row);
	wprintw(user_window,"x");
	wprintw(user_window,"%i" ,map_col);
	wattroff(user_window,COLOR_PAIR(2));
	wprintw(user_window, "\n");

	wrefresh(user_window);


}