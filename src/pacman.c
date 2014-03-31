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

//fdsfds

void init_screen();
void init_file_window();
WINDOW *title_window;
WINDOW *game_window;
WINDOW *command_window;
WINDOW *note_window;
WINDOW *file_window;
WINDOW *user_window;
const char TITLE[] = "PACMAN EDITOR";
const char VERSION[] = "@version 1.7.5";
const char CREATOR[] = "@created by THE THUNDER";	



const int TITLE_HEIGHT = 3;

const int GAME_WIDTH = 65;
const int GAME_HEIGHT = 35;
const int GAME_STARTY = 6;

const int COMMAND_HEIGHT = 3;
const int COMMAND_STARTY = 41;
char user[30] ="";
char user_email[50]="";

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

	if (has_colors()) {
        start_color();
		init_pair(7, 5, COLOR_BACKGROUND);
		init_pair(8, COLOR_GREEN, COLOR_BACKGROUND);
    }


	const char str_error[8] = "Error: ";
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
					//int characters
					char commands[100] = "";
						for(int k=0;k<100;k++){
							int characters = (int)mvwinch(command_window, 0, k);
							char Str;	
							if(k==1 && characters==32){
								break;
							}else{
								if(characters!=58 && characters!=4555){
									sprintf(&Str, "%c", characters);
									strcat(commands,&Str);
								}
							}
						}																
						
					// wclear(command_window);
					// wprintw(command_window, "I recieved followings: ");
					// wprintw(command_window, commands);
					 //wrefresh(command_window);
						// wprintw(command_window,"%i",strlen(commands));
						// wrefresh(command_window);

					if(strlen(commands)>0){
						char *token;
						char *str_recieve[4];
						// wprintw(command_window, "i'm in here with");
						// wprintw(command_window, commands);
						// wp
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
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, game_window,map_col-1, map_row);
							}
							wattron(command_window,COLOR_PAIR(8));
							wprintw(command_window,"Successfully write to ");
								
							wattron(command_window, A_UNDERLINE);
							wprintw(command_window, map_name);	
							wprintw(command_window,".pac");
							wattroff(command_window, A_UNDERLINE);
							wprintw(command_window," ! press any key to continue!");
							wattroff(command_window,COLOR_PAIR(8));
							wrefresh(command_window);			
							
							getch();
							stop_command_window(command_window, game_window,map_row,map_col);
							break;
						}else if(strcmp(str_recieve[0],"w") == 0 && str_recieve[1] != NULL){
							strcpy(map_name,str_recieve[1]);
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, game_window,map_col-1, map_row);
							}
							wattron(command_window,COLOR_PAIR(8));
							wprintw(command_window,"Sucessfully write to ");
							wattron(command_window,A_UNDERLINE);
							wprintw(command_window, str_recieve[1]);
							wprintw(command_window,".pac");
							wattroff(command_window,A_UNDERLINE);
							wprintw(command_window, " ! press any key to continue!");		
							wattroff(command_window,COLOR_PAIR(8));						
							wrefresh(command_window);
							getch();
							stop_command_window(command_window, game_window,map_row,map_col);	
							
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]== NULL){
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, game_window,map_col-1, map_row);
							}
							wattron(command_window,COLOR_PAIR(8));	
							wprintw(command_window,"Successfully write to ");
							wattron(command_window,A_UNDERLINE);	
							wprintw(command_window, map_name);
							wprintw(command_window,".pac");
							wattroff(command_window,A_UNDERLINE);	
							wprintw(command_window," and will quit by typing any key");
							getch();
							wattroff(command_window,COLOR_PAIR(8));	
							endwin();
							return 0;
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]!= NULL){
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, game_window,map_col-1, map_row);
							}
							wattron(command_window,COLOR_PAIR(8));	
							wprintw(command_window,"Sucessfully write to ");
							wprintw(command_window, str_recieve[1]);
							wattron(command_window,A_UNDERLINE);	
							wprintw(command_window,".pac");
							wattroff(command_window,A_UNDERLINE);	
							wprintw(command_window, " and will quit by typing any key");
							wrefresh(command_window);
							getch();
							wattroff(command_window,COLOR_PAIR(8));	
							endwin();			/* End curses mode		  */
							return 0;
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
									wattron(command_window,COLOR_PAIR(7));
									wprintw(command_window, str_error);
									wattroff(command_window,COLOR_PAIR(7));
									wprintw(command_window, "File not found! type any key to continue!");
									
									
									//mvprintw(COMMAND_STARTY,9,"%s", "Map not found, type ':' to return command mode");
									stop_command_window(command_window, game_window,map_row,map_col);
									continue;								
								}else{
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
								    game_window=create_new_win(map_row,map_col,GAME_STARTY,(scr_x)/2);
								   	readFile(game_window,map_row,map_col,map,s,str_recieve[1]);
								    fclose(f);
								    wattron(command_window,COLOR_PAIR(8));	
								    wprintw(command_window,"Sucessfully read from ");
								    wattron(command_window,A_UNDERLINE);	
									wprintw(command_window, str_recieve[1]);
									wprintw(command_window,".pac");
									wattroff(command_window,A_UNDERLINE);	
									wprintw(command_window, ", press any key to edit..");
									wattroff(command_window,COLOR_PAIR(8));	
									wrefresh(command_window);
									getch();
									isEnter = 0;
									stop_command_window(command_window,game_window, map_row, map_col);	
								    cursorMove(game_window,map_row,map_col,map);
								    start_command_window(command_window, COMMAND_STARTY);
								}
						}else if(strcmp(str_recieve[0],"n") == 0 && str_recieve[1] != NULL 
								&& str_recieve[2] != NULL && str_recieve[3] != NULL){
								if(atoi(str_recieve[2]) > 0 && atoi(str_recieve[2]) <= 35 && atoi(str_recieve[3]) > 0 && atoi(str_recieve[3]) <=65){
									wclear(game_window);
							    	wrefresh(game_window);
									strcpy(map_name,str_recieve[1]);
									map_row = atoi(str_recieve[2]);
									map_col = atoi(str_recieve[3])+1;

									//FILE *fp;
									char path[100] = "levels/";
									char extension[100] =".pac";
								 	strcat(path,map_name);
									strcat(path,extension);

									char map[map_row][map_col];
									initialize_map_array(map_row,map_col,map);

									//write_to_file(map_name, "CaoAnh", "s3357672@rmit.edu.vn", game_window,map_col-1, map_row);
									wattron(command_window,COLOR_PAIR(8));	
									wprintw(command_window,"Sucessfully create a map called ");
									wattron(command_window,A_UNDERLINE);	
									wprintw(command_window,map_name);
									wprintw(command_window,".pac ");
									wattroff(command_window,A_UNDERLINE);	
									wprintw(command_window,"with row = ");
									wprintw(command_window, "%d",map_row);
									wprintw(command_window," and col = ");
									wprintw(command_window,"%d", map_col);
									wattroff(command_window,COLOR_PAIR(8));	
									//getch();
									wrefresh(command_window);
									wclear(game_window);
								    stop_command_window(command_window,game_window, map_row, map_col);	
								    game_window=create_new_win(map_row,map_col,GAME_STARTY,(scr_x)/2);
								    wmove(game_window,map_row-1,map_col-2);
								    updateMap(game_window,map_row,map_col,map,getcury(game_window),getcurx(game_window));
								    refresh();
								    wrefresh(game_window);
								    getch();
									isEnter = 0;
								    cursorMove(game_window,map_row,map_col,map);
								    continue;
								}else{
									wattron(command_window,COLOR_PAIR(7));
									wprintw(command_window,str_error);
									wattroff(command_window,COLOR_PAIR(7));
									wprintw(command_window,"Map rows or cols is invalid! type any key to continue");
									wrefresh(command_window);
									getch();
									stop_command_window(command_window,game_window, map_row, map_col);	
								}
								start_command_window(command_window, COMMAND_STARTY);

						}else{
								wattron(command_window,COLOR_PAIR(7));
								wprintw(command_window,str_error);
								wattroff(command_window,COLOR_PAIR(7));
								wprintw(command_window, "Can't recognise that commands! type any key to continue!");
								wrefresh(command_window);
								getch();
								stop_command_window(command_window,game_window, map_row, map_col);
								isEnter = 0;
						}
					}else {
								wclear(command_window);
								wattron(command_window,COLOR_PAIR(7));
								wprintw(command_window,str_error);
								wattroff(command_window,COLOR_PAIR(7));
								wprintw(command_window, "Can't recognise that commands! type any key to continue!");
								wrefresh(command_window);
								getch();
								stop_command_window(command_window,game_window, map_row, map_col);
								isEnter = 0;
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
			//continue;		
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

	if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WALL,    COLOR_BACKGROUND);
        init_pair(2, COLOR_PACMAN,  COLOR_BACKGROUND);
		init_pair(3, COLOR_GHOST,  COLOR_BACKGROUND);
		init_pair(4, COLOR_FRUIT,  COLOR_BACKGROUND);
		init_pair(5, COLOR_PELLET,  COLOR_BACKGROUND);
		init_pair(6, COLOR_YELLOW, COLOR_BACKGROUND);
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
	getch();

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

	char sepChar[] = "    ";
	char pacman[] = " Pacman";
	char ghost[] = " Ghost";
	char pellet[] = " Pellet";
	char super_pellet[] =" Super Pellet";
	char fruit[] = " Fruit";


	int note_length = strlen(pacman) + strlen(ghost) + strlen(pellet) + strlen(super_pellet) + strlen(fruit) + (strlen(sepChar)*5)+5;
	char str_user[] = "User Name:";
	char str_user_email[] = "User Email:";
	
	getmaxyx(stdscr,row,col);
	title_window = create_new_win(TITLE_HEIGHT, col, 0, 0);
	game_window = create_new_win(GAME_HEIGHT, GAME_WIDTH, GAME_STARTY, col/2);
	command_window = create_new_win(COMMAND_HEIGHT, col, COMMAND_STARTY, 0);
	note_window = create_new_win(TITLE_HEIGHT, col, 4, (col - note_length)/2);
	int user_window_width = row - GAME_WIDTH;
	int user_window_startY = 0;
	user_window = create_new_win(10, user_window_width, TITLE_HEIGHT+5,user_window_startY) ;
	//box(user_window, 1 , 1);
	refresh();
	wrefresh(user_window);

	
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

	wprintw(user_window, "User Info\n");
	wprintw(user_window, str_user);
	wprintw(user_window, " ");
	wprintw(user_window, user);
	wprintw(user_window, "\n");
	wprintw(user_window,str_user_email);
	wprintw(user_window, " ");
	wprintw(user_window, user_email);
	wrefresh(user_window);

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
	mvwprintw(command_window,0,0,"%s", "To enable command mode, type ':' ");
	wrefresh(command_window);
}
