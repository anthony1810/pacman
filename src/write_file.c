#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include "write_file.h"
#include "constant.h"

WINDOW *create_new_win(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	return local_win;
}
	
void write_to_file(char file_name[],char author_name[], char author_email[], WINDOW *my_win, int width, int height){
	
	FILE *fp;
	char full_path[100]="" ;

	strcat(full_path,PATH);
 	strcat(full_path,file_name);
	strcat(full_path,EXTENSION);
	fp=fopen(full_path, "w");

	//put name and email
	fputs(author_name,fp);
	fputs(" <",fp);
	fputs(author_email, fp);
	fputs(">",fp);
	fputc('\n',fp);

	//put file name
	fputs(file_name,fp);
	fputc('\n',fp);

	//put rows
	fprintf(fp, "%d", height);
	fputc('\n',fp);

	//put col
	fprintf(fp, "%d", width);
	fputc('\n',fp);
	// fputs(,fp);
	int i;
	int k;

	for(i=0; i<height; i++){
		for(k=0;k<width;k++){
			int characters = (int)mvwinch(my_win, i, k);
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
	// printw("%9d",ch);
	//pacman
	if(ch == 4194912){
		return 'p';
	}
	//ghost
	else if(ch == 4194913){
		return 'g';
	}
	// upper left corner
	else if(ch == 4194668){
		return 'q';
	}
	// lower left corner
	else if(ch == 4194669){
		return 'z';
	}
	// upper right corner
	else if(ch == 4194667){
		return 'e';
	}
	// lower right corner
	else if(ch == 4194666){
		return 'c';
	}
	// right T line
	else if(ch == 4194677){
		return 'D';
	}
	// left T line
	else if(ch == 4194676){
		return 'A';
	}
	// top T line
	else if(ch == 4194679){
		return 'W';
	}
	// bottom T line
	else if(ch == 4194678){
		return 'X';
	}
	// Horizontal line
	else if(ch == 4194673){
		return 'w';
	}
	// vertical line
	else if(ch == 4194680){
		return 'a';
	}
	// pelet
	else if(ch == 4194686){
		return 's';
	}
	// power pellet
	else if(ch == 4194662){
		return 'S';
	}
	// fruit
	else if(ch == 4194685){
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

