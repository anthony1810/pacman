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
#include "utility.h"


/*!
 *	@mainpage COSC2451 Pacman Editor
 *	@author The Thunder Corp (Tran Nhat Quang <s3312399@rmit.edu.vn> - Huynh Phung Cao Anh <s3357672@rmit.edu.vn>)
 *  @version 1.7.5
 *
 * \section intro_sec Introduction
 * Pacman Level Editor Project was started since the very first day back when this Project had just been release by Dr. Denis Rinfret, We had Holding an ambition of creating a
 * high quality and sophisticated program to outpass any other college teams.
 *
 * \section LICENSE 
 *	This Program is freeware as long as quoting both author, you can modify it, publish it but the 
 * copyright remains to The Thunder Corp.
 *
 * \section install_sec Installation
 * \subsection step1 Step 1: Opening the project folder location with terminal
 * \subsection step2 Step 2: typing make to compile sourcode
 * \subsection step3 Step 3: type ./pacman.sh <map_name> or ./pacman.sh
 * \subsection step4 Step 4: Enter your name and email as required
 * \subsection step5 Step 5: type ':'' to enter command mode and 'esc' to quit command mode
*/

/*! \file pacman.c 
	\brief this file is used to run all the seperate modules of this program and handle vi-command style
	\author Tran Nhat Quang <s3312399@rmit.edu.vn> 
*/

WINDOW title_window; 	/* window to display title, version and company name */
WINDOW game_window; 	/* window to display map game */
WINDOW command_window; 	/*window to display command and recieve command */
WINDOW note_window; 	/* window to explain special characters of the map */
WINDOW wall; 			/* window to seperate game map and user info window */
WINDOW user_window; 	/* window to display user info and map info */

char user[30] ="";
char user_email[50]="";
char path[100] = "";
int isEnter=0;
char author[50]="";
char map_name[50]="";
char author_email[50]="";
int map_row=0;
int map_col=0;    
int scr_x, scr_y;
FILE *f ;

int main(int argc, char * argv[]){
	
	init_screen(&title_window, &game_window, &command_window, 
	&note_window, &wall, &user_window, user, user_email);
	wrefresh(&title_window);
	wrefresh(&game_window);

   	curs_set(1);
    getmaxyx(stdscr, scr_y, scr_x);
	
	int ch;
	int input;

	 if(argc==2){
        strcpy(path,PATH);
        strcat(path,argv[1]);
        strcat(path,EXTENSION);
        strcpy(map_name,argv[1]);     
        f = fopen(path, "r");
        if(!f){
            wprintw(&command_window,"%s", " ,File not found ");
            wrefresh(&command_window);
        }else{ wclear(&command_window);		
			read_command(f,path,&command_window,&game_window,&user_window,&map_row,&map_col,map_name,author,author_email,user,user_email,scr_x);		
			wclear(&command_window);
			wattron(&command_window,COLOR_PAIR(6));
			wprintw(&command_window,"To enable command mode, type ':' ");
			wattroff(&command_window,COLOR_PAIR(6));
			wrefresh(&command_window);
	 	}
    }


	const char str_error[8] = "Error: ";
	const char s[2] = " ";
	while((ch = getch()) != 'q'){
		if(ch == ':'){
			wclear(&command_window);
			waddch(&command_window, ':');
			wrefresh(&command_window);
			while((input = getch())!= 27){
				waddch(&command_window,input);
				wrefresh(&command_window);
				if(input == KEY_BACKSPACE || input == KEY_DC){
					wclear(&command_window);
					waddch(&command_window, ':');
					wrefresh(&command_window);
				}else if(input == 10 && isEnter == 0){
					isEnter = 1;
					//int characters
					char commands[100] = "";
						for(int k=0;k<100;k++){
							int characters = (int)mvwinch(&command_window, 0, k);
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
					if(strlen(commands)>0){
						char *token;
						char *str_recieve[4];
						wrefresh(&command_window);		   
						/* get the first token */
						token = strtok(commands,s);
						str_recieve[0] = token;
						token = strtok(NULL, s);
						str_recieve[1] = token;
						token = strtok(NULL, s);
						str_recieve[2] = token;
						token = strtok(NULL, s);
						str_recieve[3] = token;

						wclear(&command_window);
						if(strcmp(commands,"q")==0){
							endwin();			/* End curses mode		  */
							return 0;
						}else if(strcmp(commands,"w")==0 && str_recieve[1]== NULL){
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, &game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, &game_window,map_col-1, map_row);
							}
							
							wattron(&command_window,COLOR_PAIR(8));
							wprintw(&command_window,"Successfully write to ");
							wattron(&command_window, A_UNDERLINE);
							wprintw(&command_window, map_name);	
							wprintw(&command_window,".pac");
							wattroff(&command_window, A_UNDERLINE);
							wprintw(&command_window," ! press any key to continue!");
							wattroff(&command_window,COLOR_PAIR(8));
							wrefresh(&command_window);			
							isEnter=0;
							getch();
							stop_command_window(&command_window, &game_window,map_row,map_col);
							start_command_window(&command_window, COMMAND_STARTY);
						}else if(strcmp(str_recieve[0],"w") == 0 && str_recieve[1] != NULL){
							strcpy(map_name,str_recieve[1]);
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, &game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, &game_window,map_col-1, map_row);
							}

							wattron(&command_window,COLOR_PAIR(8));
							wprintw(&command_window,"Sucessfully write to ");
							wattron(&command_window,A_UNDERLINE);
							wprintw(&command_window, str_recieve[1]);
							wprintw(&command_window,".pac");
							wattroff(&command_window,A_UNDERLINE);
							wprintw(&command_window, " ! press any key to continue!");		
							wattroff(&command_window,COLOR_PAIR(8));						
							wrefresh(&command_window);
							getch();
							stop_command_window(&command_window, &game_window,map_row,map_col);	
							isEnter=0;
							start_command_window(&command_window, COMMAND_STARTY);
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]== NULL){
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, &game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, &game_window,map_col-1, map_row);
							}
							wattron(&command_window,COLOR_PAIR(8));	
							wprintw(&command_window,"Successfully write to ");
							wattron(&command_window,A_UNDERLINE);	
							wprintw(&command_window, map_name);
							wprintw(&command_window,".pac");
							wattroff(&command_window,A_UNDERLINE);	
							wprintw(&command_window," and will quit by typing any key");
							wrefresh(&command_window);
							getch();
							wattroff(&command_window,COLOR_PAIR(8));	
							endwin();
							return 0;
						}else if(strcmp(commands,"wq")==0 && str_recieve[1]!= NULL){
							strcpy(map_name,str_recieve[1]);
							if(strlen(map_name)>0 && strlen(author)>0 && strlen(author_email)>0){
								write_to_file(map_name, author, author_email, &game_window,map_col-1, map_row);
							}else if(strlen(map_name)>0 && strlen(user)>0 && strlen(user_email)>0){
								write_to_file(map_name, user, user_email, &game_window,map_col-1, map_row);
							}
							wattron(&command_window,COLOR_PAIR(8));	
							wprintw(&command_window,"Sucessfully write to ");
							wprintw(&command_window, str_recieve[1]);
							wattron(&command_window,A_UNDERLINE);	
							wprintw(&command_window,".pac");
							wattroff(&command_window,A_UNDERLINE);	
							wprintw(&command_window, " and will quit by typing any key");
							wrefresh(&command_window);
							getch();
							wattroff(&command_window,COLOR_PAIR(8));	
							endwin();			/* End curses mode		  */
							return 0;
						}else if(strcmp(str_recieve[0],"r") == 0 && str_recieve[1] != NULL){
							    strcpy(map_name,str_recieve[1]);
							    strcpy(path,PATH);
							    strcat(path,str_recieve[1]);
							    strcat(path,EXTENSION);
							    f = fopen(path, "r");
								if(!f){									
									wattron(&command_window,COLOR_PAIR(7));
									wprintw(&command_window, str_error);
									wattroff(&command_window,COLOR_PAIR(7));
									wprintw(&command_window, "File not found! type any key to continue!");
									wrefresh(&command_window);
									getch();
									wclear(&command_window);
									start_command_window(&command_window, COMMAND_STARTY);
								}else{
									read_command(f,path,&command_window,&game_window,&user_window,&map_row,&map_col,map_name,author,author_email,
                    					user,user_email,scr_x);	
									start_command_window(&command_window, COMMAND_STARTY);
								}
								isEnter=0;
						}else if(strcmp(str_recieve[0],"n") == 0 && str_recieve[1] != NULL 
								&& str_recieve[2] != NULL && str_recieve[3] != NULL){
								if(atoi(str_recieve[2]) > 0 && atoi(str_recieve[2]) <= 35 && atoi(str_recieve[3]) > 0 && atoi(str_recieve[3]) <=65){
									wclear(&game_window);
							    	wrefresh(&game_window);
									strcpy(map_name,str_recieve[1]);
									map_row = atoi(str_recieve[2]);
									map_col = atoi(str_recieve[3])+1;

									//FILE *fp;
									strcpy(path,PATH);
								 	strcat(path,map_name);
									strcat(path,EXTENSION);

									char map[map_row][map_col];
									initialize_map_array(map_row,map_col,map);
									strcpy(author,user);
									strcpy(author_email,user_email);
									//write_to_file(map_name, "CaoAnh", "s3357672@rmit.edu.vn", &game_window,map_col-1, map_row);
									wattron(&command_window,COLOR_PAIR(8));	
									wprintw(&command_window,"Sucessfully create a map called ");
									wattron(&command_window,A_UNDERLINE);	
									wprintw(&command_window,map_name);
									wprintw(&command_window,".pac ");
									wattroff(&command_window,A_UNDERLINE);	
									wprintw(&command_window,"with row = ");
									wprintw(&command_window, "%d",map_row);
									wprintw(&command_window," and col = ");
									wprintw(&command_window,"%d", map_col);
									wattroff(&command_window,COLOR_PAIR(8));	
									wrefresh(&command_window);
									init_user_info(&user_window,user, user_email, map_name,map_row,map_col-1,author,author_email);
								    // stop_command_window(&command_window,&game_window, map_row, map_col);	
								    game_window=create_new_win(map_row,map_col,GAME_STARTY,(scr_x)/3);

								    wmove(&game_window,map_row-1,map_col-2);
								    updateMap(&game_window,map_row,map_col,map,getcury(&game_window),getcurx(&game_window));
								    refresh();
								    wrefresh(&game_window);
								    cursorMove(&game_window,map_row,map_col,map);
								}else{
									wattron(&command_window,COLOR_PAIR(7));
									wprintw(&command_window,str_error);
									wattroff(&command_window,COLOR_PAIR(7));
									wprintw(&command_window,"Map rows or cols is invalid! type any key to continue");
									wrefresh(&command_window);
									getch();
									stop_command_window(&command_window,&game_window, map_row, map_col);	
								}
								isEnter=0;
								start_command_window(&command_window, COMMAND_STARTY);

						}else{
								wattron(&command_window,COLOR_PAIR(7));
								wprintw(&command_window,str_error);
								wattroff(&command_window,COLOR_PAIR(7));
								wprintw(&command_window, "Can't recognise that commands! type any key to continue!, upper");
								wrefresh(&command_window);
								wclear(&command_window);
								waddch(&command_window,':');
								isEnter = 0;
						}
					}else {
								wclear(&command_window);
								wattron(&command_window,COLOR_PAIR(7));
								wprintw(&command_window,str_error);
								wattroff(&command_window,COLOR_PAIR(7));
								wprintw(&command_window, "Can't recognise that commands! type any key to continue!,down");
								wrefresh(&command_window);
								wclear(&command_window);
								waddch(&command_window,':');
								isEnter = 0;
						}
				}	
			}
			stop_command_window(&command_window,&game_window, map_row, map_col);
			char map[map_row][map_col];
			for(int i=0;i<map_row;i++){
				for(int j=0;j<=map_col-1;j++){
					if(j==map_col){
						map[i][j]='\n';
					}else{
						int characters = (int)mvwinch(&game_window, i, j);
						map[i][j]=getTranslatedChar(characters);
					}
				}
			}

			wmove(&game_window,map_row-1,map_col-2);
			updateMap(&game_window,map_row,map_col,map,getcury(&game_window),getcurx(&game_window));
			refresh();
			wrefresh(&game_window);
			cursorMove(&game_window,map_row,map_col,map);	
			wattron(&command_window,COLOR_PAIR(6));
			mvwprintw(&command_window,0,0,"%s", "To enable command mode, type ':' ");
			wattroff(&command_window,COLOR_PAIR(6));
			wrefresh(&command_window);
			continue;
		}
	}
	endwin();
	return 0;
}


