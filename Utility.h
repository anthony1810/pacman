#define CAOANH 4
WINDOW *create_newwin(int height, int width, int starty, int startx);
void readFile(WINDOW *map_win,int row,int col,char map [row][col],char s[]);
void updateMap(WINDOW *map_win,int row,int col,char map[row][col],int cursorY,int cursorX);