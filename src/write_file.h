
/* http://www.tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/#ABOUTINIT */
#define MAX_NAME_SZ 256

WINDOW *create_new_win(int height, int width, int starty, int startx);

char getTranslatedChar(int ch);

void write_to_file(char file_name[],char author_name[], char author_email[], WINDOW *my_win,int width, int height);

void str_combine(char s1[], char s2[]);

