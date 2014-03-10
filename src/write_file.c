#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"

WINDOW *create_new_win(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	return local_win;
}

void write_to_file(char file_name[],char author_name[], char author_email[], WINDOW *my_win, int width, int height){
	FILE *fp;
	char path[] = "../levels/";
	char extension[] =".pac";
	str_combine(path,file_name);
	str_combine(path,extension);
	
	fp=fopen(path, "rb+");
	if(fp == NULL){
		fp = fopen(path, "wb");
	}
	//put name and email
	str_combine(author_name, " <");
	str_combine(author_name, author_email);
	str_combine(author_name,">");
	fputs(author_name,fp);
	fputc('\n',fp);

	//put file name
	fputs(file_name,fp);
	fputc('\n',fp);

	//put rows
	fprintf(fp, "%d", height);
	fputc('\n',fp);

	//put height
	fprintf(fp, "%d", width);
	fputc('\n',fp);
	// fputs(,fp);
	int i;
	int k;
	for(i=0; i<height; i++){
		for(k=0;k<width;k++){
			int characters = (int) mvwinch(my_win, i, k);
			fputc(getTranslatedChar(characters), fp);
		}
		printw("\n");
		fputc('\n', fp);
		refresh();	
	}
	fputc('\n',fp);
	fclose(fp);
}


char getTranslatedChar(int ch){
	//pacman
	if(ch == 4194400){
		return 'p';
	}
	//ghost
	else if(ch == 4194401){
		return 'g';
	}
	// upper left corner
	else if(ch == 4194412){
		return 'q';
	}
	// lower left corner
	else if(ch == 4194413){
		return 'z';
	}
	// upper right corner
	else if(ch == 4194411){
		return 'e';
	}
	// lower right corner
	else if(ch == 4194410){
		return 'c';
	}
	// right T line
	else if(ch == 4194420){
		return 'D';
	}
	// left T line
	else if(ch == 4194421){
		return 'A';
	}
	// top T line
	else if(ch == 4194422){
		return 'W';
	}
	// bottom T line
	else if(ch == 4194423){
		return 'X';
	}
	// Horizontal line
	else if(ch == 4194417){
		return 'w';
	}
	// vertical line
	else if(ch == 4194424){
		return 'a';
	}
	// pelet
	else if(ch == 4194430){
		return 's';
	}
	// power pellet
	else if(ch == 4194406){
		return 'S';
	}
	// fruit
	else if(ch == 4194429){
		return 'f';
	}
	// space
	else
		return 32;
}

void str_combine(char s1[], char s2[]){
	char i,j;
	for(i=0; s1[i]!='\0'; ++i);  /* i contains length of string s1. */
    for(j=0; s2[j]!='\0'; ++j, ++i)
    {
        s1[i]=s2[j];
    }
    s1[i]='\0';
}

