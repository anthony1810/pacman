#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "write_file.h"
#include "read_file.h"
#include "command.h"
#include "constant.h"



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

int main(){
	init_screen();
    int isEnter=0;
	char author[50];
	char map_name[50];
	char author_email[50];
	int map_row=0;
    int map_col=0;
    
    int scr_x, scr_y;
    getmaxyx(stdscr, scr_y, scr_x);
	
	int ch;
	int input;
	const char s[2] = " ";
	while((ch = getch()) != 'q'){
		if(ch == ':'){
			curs_set(1);
			wclear(command_window);
			waddch(command_window, ':');
			wrefresh(command_window);
			while((input = getch())!= 27){
				waddch(command_window,input);
				wrefresh(command_window);
				if(input == KEY_BACKSPACE || input == KEY_DC){
					wclear(command_window);
					waddch(command_window, ':');
					wrefresh(command_window);
				}else if(input == 10 && isEnter == 0){
					isEnter = 1;
					char commands[100] = "";
						for(int k=0;k<100;k++){
							int characters = (int)mvwinch(command_window, 0, k);
							char Str;												
							if(characters!=58 && characters!=4555){
								sprintf(&Str, "%c", characters);
								strcat(commands,&Str);
							}
						}
					// wclear(command_window);
					// wprintw(command_window, "I recieved followings: ");
					// wprintw(command_window, commands);
					 //wrefresh(command_window);

					if(strlen(commands)>0){
						char *token;
						char *str_recieve[4];
						wprintw(command_window, "i'm in here with");
						wprintw(command_window, commands);
						wrefresh(command_window);		   
						/* get the first token */
						token = strtok(commands,s);
						str_recieve[0] = token;
						token = strtok(NULL, s);
						str_recieve[1] = token;
						token = strtok(NULL, s);
						str_recieve[2] = token;
						token = strtok(NULL, s);
						str_recieve[3] = token;

						wclear(command_window);
						if(strcmp(commands,"q")==0){
							endwin();			/* End curses mode		  */
							return 0;
						}else if(strcmp(commands,"w")==0 && str_recieve[1]== NULL){
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, game_window,map_col-1, map_row);
								wprintw(command_window,"successfully write to ");
								wprintw(command_window, map_name);	
								wprintw(command_window,".pac !");
								wrefresh(command_window);			
							}else{
								wprintw(command_window, "File info is inadequate! type any key to continue!");
							}
							wrefresh(command_window);
							getch();
							stop_command_window(command_window, game_window,map_row,map_col);
						}else if(strcmp(str_recieve[0],"w") == 0 && str_recieve[1] != NULL){
								if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
									write_to_file(str_recieve[1], author, author_email, game_window,map_col-1, map_row);
									wprintw(command_window,"sucessfully write to ");
									wprintw(command_window, str_recieve[1]);
									wprintw(command_window,".pac !");
									wprintw(command_window, " press any key to continue!");								
								}else {
									wprintw(command_window, "File info is inadequate!");
								}
								wrefresh(command_window);
								getch();
								stop_command_window(command_window, game_window,map_row,map_col);	
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]== NULL){
								if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
									write_to_file(map_name, author, author_email, game_window,map_col-1, map_row);
									wprintw(command_window,"successfully write to ");
									wprintw(command_window, map_name);
									wprintw(command_window,".pac");
									wprintw(command_window," and will quit by typing any key");
									getch();
									endwin();
									return 0;
								}else {
									wprintw(command_window, "File info is inadequate! type any key to continue!");
									wrefresh(command_window);
									getch();									
									stop_command_window(command_window, game_window,map_row,map_col);		
								}		

						}else if(strcmp(commands,"wq")==0 && str_recieve[1]!= NULL){
								if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
									write_to_file(str_recieve[1], author, author_email, game_window,map_col-1, map_row);
									wprintw(command_window,"sucessfully write to ");
									wprintw(command_window, str_recieve[1]);
									wprintw(command_window,".pac");
									wprintw(command_window, " and will quit by typing any key");
									wrefresh(command_window);
									getch();
									endwin();			/* End curses mode		  */
									return 0;
								}else{
									wprintw(command_window, "File info is inadequate! type any key to continue!");
									getch();
									stop_command_window(command_window, game_window,map_row,map_col);	
								}
						}else if(strcmp(str_recieve[0],"r") == 0 && str_recieve[1] != NULL){
								char s[100];
								FILE *f ;
							    char path[100]="";
							    strcpy(map_name,str_recieve[1]);
							    strcat(path,PATH);
							    strcat(path,str_recieve[1]);
							    strcat(path,EXTENSION);
							    f = fopen(path, "r");
								if(!f){
									stop_command_window(command_window,game_window, map_row, map_col);	
									mvprintw(COMMAND_STARTY,0,"%s", " Map not found, type ':' to return command mode");
									wrefresh(command_window);
									break;
								}
							    fgets(s, 100, f);
							    get_author_name_and_email(s,author,author_email);
							    fgets(s, 100, f);
							    fgets(s, 100, f);
							    map_row=atoi(s);
							    fgets(s, 100, f);
							    map_col=atoi(s)+1;

							    char map[map_row][map_col];
							    //re-create game_window to fit the column and row
							    wclear(game_window);
							    wrefresh(game_window);
							    game_window=create_new_win(map_row,map_col,GAME_STARTY,(scr_x- map_col)/2);
							   	readFile(game_window,map_row,map_col,map,s,str_recieve[1]);
							    fclose(f);
							    wprintw(command_window,"sucessfully read from ");
								wprintw(command_window, str_recieve[1]);
								wprintw(command_window,".pac");
								wprintw(command_window, ", press any key to edit..");
								wrefresh(command_window);
								getch();
								isEnter = 0;
								stop_command_window(command_window,game_window, map_row, map_col);	
							    cursorMove(game_window,map_row,map_col,map);
							    start_command_window(command_window, COMMAND_STARTY);
						}else if(strcmp(str_recieve[0],"n") == 0 && str_recieve[1] != NULL 
								&& str_recieve[2] != NULL && str_recieve[3] != NULL){
								if(atoi(str_recieve[2]) > 0 && atoi(str_recieve[2]) <= 35 && atoi(str_recieve[3]) > 0 && atoi(str_recieve[3]) <=65){
									wclear(game_window);
							    	wrefresh(game_window);
									strcpy(map_name,str_recieve[1]);
									map_row = atoi(str_recieve[2]);
									map_col = atoi(str_recieve[3])+1;

									FILE *fp;
									char path[100] = "levels/";
									char extension[100] =".pac";
								 	strcat(path,map_name);
									strcat(path,extension);

									char map[map_row][map_col];
									initialize_map_array(map_row,map_col,map);

									write_to_file(map_name, "CaoAnh", "s3357672@rmit.edu.vn", game_window,map_col-1, map_row);
									wprintw(command_window,"sucessfully create ");
									wprintw(command_window,map_name);
									wprintw(command_window,".pac ");
									 wprintw(command_window,"file with row = ");
									wprintw(command_window, "%d",map_row);
									wprintw(command_window," and col = ");
									wprintw(command_window,"%d", map_col);
									wrefresh(command_window);
									wclear(game_window);
								    stop_command_window(command_window,game_window, map_row, map_col);	
								    game_window=create_new_win(map_row,map_col,GAME_STARTY,(scr_x- map_col)/2);
								    wmove(game_window,map_row-1,map_col-2);
								    updateMap(game_window,map_row,map_col,map,getcury(game_window),getcurx(game_window));
								    refresh();
								    wrefresh(game_window);
								    getch();
									isEnter = 0;
								    cursorMove(game_window,map_row,map_col,map);
								}else{
									wprintw(command_window,"map rows or cols is invalid! type any key to continue");
									wrefresh(command_window);
									getch();
									//stop_command_window(command_window,game_window, map_row, map_col);	
								}
								start_command_window(command_window, COMMAND_STARTY);

						}else {
								wprintw(command_window, "Can't recognise that commands! type any key to continue!");
								wrefresh(command_window);
								getch();
								stop_command_window(command_window,game_window, map_row, map_col);
								isEnter = 0;
						}
					}
				}	
			}//line 55
			// wclear(command_window);
			// wprintw(command_window, "Escape is pressed");
			// wrefresh(command_window);
			// getch();
			stop_command_window(command_window,game_window, map_row, map_col);
			char map[map_row][map_col];
			for(int i=0;i<map_row;i++){
				for(int j=0;j<=map_col-1;j++){
					if(j==map_col){
						map[i][j]='\n';
					}else{
						int characters = (int)mvwinch(game_window, i, j);
						map[i][j]=getTranslatedChar(characters);
					}
				}
			}

			wmove(game_window,map_row-1,map_col-2);
			updateMap(game_window,map_row,map_col,map,getcury(game_window),getcurx(game_window));
			refresh();
			wrefresh(game_window);
			cursorMove(game_window,map_row,map_col,map);			
			// start_command_window(command_window, COMMAND_STARTY);
		}//line 50
	}
	endwin();
	return 0;
}

/**
 * @brief Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
void init_screen(){
	initscr();	
	int row,col;
	getmaxyx(stdscr,row,col);
	raw();			/**< Line buffering disabled	 */
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();

	char pacman[] = "pacman | ";
	char ghost[] = "ghost | ";
	char pellet[] = "pellet | ";
	char super_pellet[] ="super pellet | ";
	char fruit[] = "fruit";

	if (has_colors()) {
        start_color();
        // in theory, you can change the value of the 8 predefined colors
        // but it works only some times
        //assert(init_color(COLOR_YELLOW, 200, 200, 1000) == OK);
        // instead, you have to redefine the colors in the terminal

        // initialise you colors pairs (foreground, background)
        init_pair(1, COLOR_WALL,    COLOR_BACKGROUND);
        init_pair(2, COLOR_PACMAN,  COLOR_BACKGROUND);
		init_pair(3, COLOR_GHOST,  COLOR_BACKGROUND);
		init_pair(4, COLOR_FRUIT,  COLOR_BACKGROUND);
		init_pair(5, COLOR_PELLET,  COLOR_BACKGROUND);
    }

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

	wattron(note_window,COLOR_PAIR(2));
	waddch(note_window,ACS_DIAMOND);
	wprintw(note_window,pacman);
	wattron(note_window,COLOR_PAIR(1));

	wattron(note_window,COLOR_PAIR(3));
	waddch(note_window, ACS_CKBOARD);
	wprintw(note_window, ghost);
	wattron(note_window,COLOR_PAIR(1));

	wattron(note_window,COLOR_PAIR(5));
	waddch(note_window, ACS_BULLET);
	wprintw(note_window, pellet);
	wattron(note_window,COLOR_PAIR(1));

	wattron(note_window,COLOR_PAIR(5));
	waddch(note_window, ACS_DEGREE);
	wprintw(note_window, super_pellet);
	wattron(note_window,COLOR_PAIR(1));

	wattron(note_window,COLOR_PAIR(4));
	waddch(note_window, ACS_STERLING);
	wprintw(note_window, fruit);
	wattron(note_window,COLOR_PAIR(1));
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
	curs_set(0);
	mvwprintw(command_window,0,0,"%s", " To enable command mode, type ':' ");
	wrefresh(command_window);
	

}
