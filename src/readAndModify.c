#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

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
WINDOW *create_newwin(int height, int width, int starty, int startx);
void readFile(WINDOW *map_win,int row,int col,char map [row][col],char s[]);
void updateMap(WINDOW *map_win,int row,int col,char map[row][col]);
int cursorX;
int cursorY;
int row;
int col;
int main(int argc, char *argv[])
{ 	WINDOW *main_win;
    WINDOW *map_win;
    int startx, starty, width, height;
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
    // add a bunch of characters
    // you should probably use the function mvaddch and other similar function
    // the move the cursor to some position
    // attrset(COLOR_PAIR(1));
    // addch(ACS_ULCORNER);
    // addch(ACS_HLINE);
    // addch(ACS_HLINE);
    // addch(ACS_HLINE);
    // addch(ACS_TTEE);
    // addch(ACS_HLINE);
    // addch(ACS_HLINE);
    // attrset(COLOR_PAIR(2));
    // addch(ACS_DIAMOND);
    // attrset(COLOR_PAIR(1));
    
    height = 7;
	width = 6;
	starty = 4;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	map_win = create_newwin(height, width, starty, startx);
	char s[100];
    
    FILE *f = fopen("../levels/level1.pac", "r");
    if (!f) {
        fprintf(stderr, "Cannot open the file!\n");
    }
    
    fgets(s, 100, f);
    fgets(s, 100, f);
    fgets(s, 100, f);
    row=atoi(s);
    fgets(s, 100, f);
    col=atoi(s)+1;
    char map[row][col];
   	readFile(map_win,row,col,map,s);
    // fclose(f);
    int c;
    // for (;;) {
    //     int c = getch();     /* refresh, accept single keystroke of input */
    //     /* process the command keystroke */
    //     if (c == 'q') {
    //         break;
    //     }
    //     sprintf(out, "%i", c);
    //     addch(c);
    //     if (c == KEY_DOWN) {
    //         addstr("down");
    //     }
        
	   //  attrset(COLOR_PAIR(num % 8));
	   //  num++;
	    
	   //  // sleep 
    //     nanosleep(&delay, &rem);
        
        
    // }

      while((c=getch())!='q'){
      	cursorX=getcurx(main_win);
      	cursorY=getcury(main_win);
    //   		if(c==KEY_BACKSPACE){
    //   			mvaddch(cursorY,cursorX,' ');
    //   			move(cursorY,--cursorX);
    //   		}
    //   		if(c==KEY_UP){
				// move(--cursorY,cursorX);
    //   		}
    //   		if(c!=KEY_BACKSPACE && c!=KEY_LEFT && c!=KEY_DOWN && c!=KEY_UP){
    //   			addch(c);
    //   			map[getcury(main_win)-4][getcurx(main_win)-1]=c;
    //   			updateMap(map_win,row,col,map);
    //   		}
      		switch(c){
      			case KEY_BACKSPACE:
    	  			mvaddch(cursorY,cursorX,' ');
     	 			move(cursorY,--cursorX);
     	 			break;
     	 		case KEY_UP:
     	 			move(--cursorY,cursorX);
     	 			break;	
				case KEY_DOWN:
					move(++cursorY,cursorX);     	 			
					break;
				case KEY_LEFT:
					move(cursorY,--cursorX);
					break;
				case KEY_RIGHT:
					move(cursorY,++cursorX);
					break;
				case 'b':
					move(cursorY,cursorX);	
					break;
				default:
					addch(c);
      				map[getcury(main_win)-4][getcurx(main_win)-1]=c;
      				updateMap(map_win,row,col,map);
      				break;

      		}
			// nanosleep(&delay, &rem);

      }
    finish(0);               /* we're done */
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}


static void finish(int sig)
{
    endwin();

    /* do your non-curses wrapup here */

    exit(0);
}
void readFile(WINDOW *map_win,int row,int col,char map[row][col], char s[]){

    FILE *f = fopen("../levels/level1.pac", "r");
    if (!f) {
        fprintf(stderr, "Cannot open the file!\n");
    }
    char ch;
    int r=0;int c=0;
    fgets(s, 100, f);
    addstr(s);
    fgets(s, 100, f);
    addstr(s);
    fgets(s, 100, f);
    addstr(s);
    fgets(s, 100, f);
    addstr(s);
    do{
        ch=fgetc(f);
        addch(ch);
        wattron(map_win,COLOR_PAIR(1));
        
        switch(ch){
            case 'q':
            case 'Q':
                waddch(map_win,ACS_ULCORNER);
                map[r][c]='q';
                c++;
                break;
            case 'e':
            case 'E':
                waddch(map_win,ACS_URCORNER);
                map[r][c]='e';
                c++;
                break;
            case 'w':
            case 'x':
                waddch(map_win,ACS_HLINE);
                map[r][c]='w';
                c++;
                break;
            case 'a':               
            case 'd':
                waddch(map_win,ACS_VLINE);
                map[r][c]='a';
                c++;
                break;
            case 'z':
            case 'Z':
                waddch(map_win,ACS_LLCORNER);
                map[r][c]='z';
                c++;
                break; 
            case 'c':
            case 'C':
                waddch(map_win,ACS_LRCORNER);                            
                map[r][c]='c';
                c++;
                break;
            case 'A':
                waddch(map_win,ACS_LTEE);                
                map[r][c]='A';
                c++;
                break;
            case 'D':
                waddch(map_win,ACS_RTEE);
                map[r][c]='D';
                c++;
                break;
            case 'W':
                waddch(map_win,ACS_TTEE);                    
                map[r][c]='W';
                c++;
                break;
            case 'X':
                waddch(map_win,ACS_BTEE);    
                map[r][c]='X';
                c++;
                break;
            case '\n':
                waddch(map_win,'\n');
                map[r][c]='\n';
                r++;
                c=0;
                break;    
            case 'G':
                waddch(map_win,ACS_CKBOARD);
                map[r][c]='G';
                c++;
                break;
            case 's':
                waddch(map_win,ACS_BULLET);
                map[r][c]='s';
                c++;
                break;
            case 'S':
                waddch(map_win,ACS_DEGREE);
                map[r][c]='S';
                c++;
                break;  
			case 'P':
				wattron(map_win,COLOR_PAIR(2));
				waddch(map_win,'P');                  
				map[r][c]='P';
                c++;
				wattron(map_win,COLOR_PAIR(1));                   	
				break;
        }
    }while(ch!=EOF);
    refresh();
    wrefresh(map_win);
    //10 is the final row, 5(6) is the map column+1
    cursorX=col;
    cursorY=row+3;
    move(cursorY,cursorX);    
}
void updateMap(WINDOW *map_win,int row,int col,char map[row][col]){
	wclear(map_win);
	refresh();
    wrefresh(map_win);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			switch(map[i][j]){
            case 'q':
            case 'Q':
                waddch(map_win,ACS_ULCORNER);
                break;
            case 'e':
            case 'E':
                waddch(map_win,ACS_URCORNER);
                break;
            case 'w':
            case 'x':
                waddch(map_win,ACS_HLINE);
                break;
            case 'a':               
            case 'd':
                waddch(map_win,ACS_VLINE);                
                break;
            case 'z':
            case 'Z':
                waddch(map_win,ACS_LLCORNER);
                break; 
            case 'c':
            case 'C':
                waddch(map_win,ACS_LRCORNER);
                break;
            case 'A':
                waddch(map_win,ACS_LTEE);                
                break;
            case 'D':
                waddch(map_win,ACS_RTEE);
                break;
            case 'W':
                waddch(map_win,ACS_TTEE);                    
                break;
            case 'X':
                waddch(map_win,ACS_BTEE);    
                break;
            case '\n':
                waddch(map_win,'\n');
                break;    
            case 'G':
                waddch(map_win,ACS_CKBOARD);
                break;
            case 's':
                waddch(map_win,ACS_BULLET);
                break;
            case 'S':
                waddch(map_win,ACS_DEGREE);
                break;  
			case 'P':
				wattron(map_win,COLOR_PAIR(2));
				waddch(map_win,'P');                  
				wattron(map_win,COLOR_PAIR(1));                   	
				break;
        	}

		}

	}
	refresh();
    wrefresh(map_win);

}
