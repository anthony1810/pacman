#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "Utility.h"
// define your own colors: the numbers correspond to the colors defined
// in the terminal configuration
#define COLOR_BACKGROUND 0
#define COLOR_WALL       1
#define COLOR_PACMAN     2

/**
  * Based on an example taken on this site:
  * http://invisible-island.net/ncurses/ncurses-intro.html
  *
  * @author http://invisible-island.net/ncurses/ncurses-intro.html
  * @author Denis Rinfret
  */
static void finish(int sig);

int row;
int col;
int startx, starty, width, height;
int main(int argc, char *argv[])
{ 	WINDOW *main_win;
    WINDOW *map_win;   
    int cursorX;
    char author[100];
    char map_name[50];
    int cursorY;
    int num = 0;
    char out[75];
    struct timespec delay = {0, 500000000L}, 
                     rem;
    
    //delay.tv_sec = 0;
    //delay.tv_nsec = 500000000L;
    
    /* initialize your non-curses data structures here */
    
    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

    main_win= initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) noecho();         /* echo input - in color */

    if (has_colors()) {
        start_color();
        // in theory, you can change the value of the 8 predefined colors
        // but it works only some times
        //assert(init_color(COLOR_YELLOW, 200, 200, 1000) == OK);
        // instead, you have to redefine the colors in the terminal

        // initialise you colors pairs (foreground, background)
        init_pair(1, COLOR_WALL,    COLOR_BACKGROUND);
        init_pair(2, COLOR_PACMAN,  COLOR_BACKGROUND);

    }
  
    
  
	char s[100];
    
    FILE *f = fopen("../levels/level1.pac", "r");
    if (!f) {
        fprintf(stderr, "Cannot open the file!\n");
    }
    
    fgets(s, 100, f);
    memcpy(author, s, 100);
    fgets(s, 100, f);
    memcpy(map_name, s, 100);
    fgets(s, 100, f);
    row=atoi(s);
    fgets(s, 100, f);
    col=atoi(s)+1;
    map_win = create_newwin(row, col, 4, 0);
    char map[row][col];
   	readFile(map_win,row,col,map,s);
    fclose(f);
    int c;

      while((c=getch())!='b'){
      	cursorX=getcurx(map_win);
      	cursorY=getcury(map_win);
      	switch(c){
      		case ' ':
              waddch(map_win,' ');
              // wmove(map_win,cursorY,--cursorX);
              map[getcury(map_win)][getcurx(map_win)]=c;
              updateMap(map_win,row,col,map,cursorY,cursorX);
     	 			break;
     	 	case KEY_UP:
     	 			wmove(map_win,--cursorY,cursorX);
     	 			break;	
				case KEY_DOWN:
					wmove(map_win,++cursorY,cursorX);     	 			
					break;
				case KEY_LEFT:
					wmove(map_win,cursorY,--cursorX);
					break;
				case KEY_RIGHT:
					wmove(map_win,cursorY,++cursorX);
					break;
				case 'q':
        case 'Q':
        case 'E':
        case 'e':
        case 'w':
        case 'W':
        case 'a':
        case 'A':
        case 's':
        case 'S':
        case 'd':
        case 'D':
        case 'z':
        case 'Z':
        case 'x':
        case 'X':
        case 'c':
        case 'C':
        case 'G':
        case 'P':
      			map[getcury(map_win)][getcurx(map_win)]=c;
      			updateMap(map_win,row,col,map,cursorY,cursorX);
      			break;
      		}

            wrefresh(map_win);
			// nanosleep(&delay, &rem);

      }
    finish(0);               /* we're done */
}


static void finish(int sig)
{
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
