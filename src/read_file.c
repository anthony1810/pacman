#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "read_file.h"
#include "write_file.h"
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
void readFile(WINDOW *map_win,int row,int col,char map[row][col], char s[],char file_name[]){
    wclear(map_win);
    FILE *f ;
    char path[] = "levels/";
    char extension[] =".pac";
    str_combine(path,file_name);
    str_combine(path,extension);
    f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "Cannot open the file!\n");
    }
    char ch;
    int r=0;int c=0;
    //print Author info, map info, row ,column 
    fgets(s, 100, f);
    fgets(s, 100, f);
    fgets(s, 100, f);
    fgets(s, 100, f);

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
            case 'g':
                wattron(map_win,COLOR_PAIR(2));
                waddch(map_win,ACS_CKBOARD);
                map[r][c]='G';
                c++;
                wattron(map_win,COLOR_PAIR(1));
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
            case 'p':
				wattron(map_win,COLOR_PAIR(2));
				waddch(map_win,ACS_DIAMOND);                  
				map[r][c]='P';
                c++;
				wattron(map_win,COLOR_PAIR(1));                   	
				break;
            case 'f':
            case 'F':
                waddch(map_win,ACS_STERLING);
                map[r][c]='f';
                c++;
                break;  
            case ':':
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
            case 'g':
                wattron(map_win,COLOR_PAIR(2));
                waddch(map_win,ACS_CKBOARD);
                wattron(map_win,COLOR_PAIR(1));                     
                break;
            case 's':
                waddch(map_win,ACS_BULLET);
                break;
            case 'S':
                waddch(map_win,ACS_DEGREE);
                break;  
			case 'P':
            case 'p':
				wattron(map_win,COLOR_PAIR(2));
				waddch(map_win,ACS_DIAMOND);                  
				wattron(map_win,COLOR_PAIR(1));                   	
				break;
            case 'f':
            case 'F':
                waddch(map_win,ACS_STERLING);
                break; 
            case ' ':
                waddch(map_win,169);
                break;
        	}

		}

	}
    wmove(map_win,cursorY,cursorX);
	refresh();
    wrefresh(map_win);
}
void cursorMove(WINDOW *game_window,int map_row,int map_col,char map[map_row][map_col]){

    int c;
    int cursorX;
    int cursorY;

    while((c=getch())!=':'){
        cursorX=getcurx(game_window);
        cursorY=getcury(game_window);
        switch(c){
            case ' ':
                wmove(game_window,cursorY,cursorX);;
                map[getcury(game_window)][getcurx(game_window)]=c;
                updateMap(game_window,map_row,map_col,map,cursorY,cursorX);
                break;
            case KEY_UP:
                wmove(game_window,--cursorY,cursorX);
                break; 
            case KEY_DOWN:
                cursorY= (cursorY==map_row-1) ? map_row-1 : cursorY+1;
                wmove(game_window,cursorY,cursorX);                     
                break;
            case KEY_LEFT:
                wmove(game_window,cursorY,--cursorX);          
                break;
            case KEY_RIGHT:
                cursorX= (cursorX==map_col-2) ? map_col-2 : cursorX+1;
                wmove(game_window,cursorY,cursorX);
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
            case 'f':
            case 'F':
                map[getcury(game_window)][getcurx(game_window)]=c;
                updateMap(game_window,map_row,map_col,map,cursorY,cursorX);
                break;
            }
            wrefresh(game_window);
    }
}
void get_author_name_and_email(char fullString[],char author[], char email[]){
    int emailBegin=0;
    int i;
    for (i = 0; fullString[i+1]!='>'; i++)
    {
        if(fullString[i]=='<'){
            emailBegin=i;
        }
        if(emailBegin==0){
            author[i]=fullString[i];
        }
        if(emailBegin!=0){
            email[i-emailBegin]=fullString[i+1];
        }
    }
    email[i-(emailBegin)]='\0';
    author[emailBegin-1]='\0';
}
void initialize_map_array(int map_row,int map_col,char map[map_row][map_col]){
    for (int i = 0; i < map_row; i++)
    {
        for (int j = 0; i < map_col; j++)
        {
            // map[i][j]=' ';
        }
    }
}
