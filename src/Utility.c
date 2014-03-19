#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "Utility.h"
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
void readFile(WINDOW *map_win,int row,int col,char map[row][col], char s[]){

    FILE *f = fopen("../levels/level1.pac", "r");
    if (!f) {
        fprintf(stderr, "Cannot open the file!\n");
    }
    char ch;
    int r=0;int c=0;
    //print Author info, map info, row ,column 
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
    //move the cursor to the lower right of the map 
    wmove(map_win,row-1,col-2);
    
    refresh();
    wrefresh(map_win);

}
void updateMap(WINDOW *map_win,int row,int col,char map[row][col],int cursorY,int cursorX){
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
    wmove(map_win,cursorY,cursorX);
	refresh();
    wrefresh(map_win);

}
