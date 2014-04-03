
#ifndef WRITE_FILE_H
#define WRITE_FILE_H
/* http://www.tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/#ABOUTINIT */

#define MAX_NAME_SZ 256

char getTranslatedChar(int ch);

void write_to_file(char file_name[],char author_name[], char author_email[], WINDOW *my_win,int map_col, int map_row);


#endif