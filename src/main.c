#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"

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

	wrefresh(my_win);
	nocbreak();

	printw("Please Enter the name of the file: ");
	refresh();
	char name[100];
	fgets (name, MAX_NAME_SZ, stdin);
	/* Remove trailing newline, if there. */
    if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
        name[strlen (name) - 1] = '\0';
	printw("\n");
	refresh();

	printw("Please Enter the name of the author: ");
	refresh();
	char author_name[100];
	fgets (author_name, MAX_NAME_SZ, stdin);
	/* Remove trailing newline, if there. */
    if ((strlen(author_name)>0) && (author_name[strlen (author_name) - 1] == '\n'))
        author_name[strlen (author_name) - 1] = '\0';
	printw("\n");
	refresh();

	printw("Please Enter the email of the author: ");
	refresh();
	char author_email[200];
	fgets (author_email, MAX_NAME_SZ, stdin);
	/* Remove trailing newline, if there. */
    if ((strlen(author_email)>0) && (author_email[strlen (author_email) - 1] == '\n'))
        author_email[strlen (author_email) - 1] = '\0';


	write_to_file(name,author_name, author_email,my_win, width,height);
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	
			case KEY_LEFT:
				
				break;
			case KEY_RIGHT:
				
				break;
			case KEY_UP:
				
				break;
			case KEY_DOWN:
				
				break;	
		}
	}
		
	endwin();			/* End curses mode		  */
	return 0;
}
