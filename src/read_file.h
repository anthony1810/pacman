#ifndef READ_FILE_H
#define READ_FILE_H
void readFile(WINDOW *map_win,int row,int col,char map [row][col],char s[],char file_name[]);
void updateMap(WINDOW *map_win,int row,int col,char map[row][col],int cursorY,int cursorX);
void cursorMove(WINDOW *game_window,int map_row,int map_col,char map[map_row][map_col]);
void get_author_name_and_email(char fullString[],char author[], char email[]);
void initialize_map_array(int map_row,int map_col,char map[map_row][map_col]);
#endif