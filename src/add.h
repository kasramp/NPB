/*
 * add.h
 * 
 * Copyright 2013-2018 Kasra Madadipouya <kasra@madadipouya.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include<sqlite3.h>
#include<stdio.h>
#include<string.h>
#ifndef ADD_H_
#define ADD_H_
void newcontact(char name[1024],char number[1024])
{
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char querystring[2048];
		strcpy(querystring,"INSERT INTO list(name,number) VALUES ('");
		strcat(querystring,name);
		strcat(querystring,"','");
		strcat(querystring,number);
		strcat(querystring,"')");
		//printf("\n");
		rc = sqlite3_open("contact.sqlite", &db);
		if(rc)
		{
		      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		      sqlite3_close(db);
		      //return(1);
	    }
		rc = sqlite3_exec(db, querystring, callback, 0, &zErrMsg);
		//printf("New contact is added successfully!\n\n");
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
//int temp=outprint();
counter=0;
}
int outprint()
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;
	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	height=5;
	width=44;
	starty = (LINES - height) / 2;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
//	printw(
	mvprintw(LINES - 2, 0,"Press Enter to return              ");
	refresh();
int x,y;
getmaxyx(stdscr,y,x);

	my_win = create_newwin(height,width,(y/2),(x/2)-18);
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattron(my_win,COLOR_PAIR(1));
	mvwprintw(my_win,2,1,"The contact is added successfully!");
	wrefresh(my_win);
	wattroff(my_win,COLOR_PAIR(1));
	while((ch = getch()) != 10);
	endwin();
	return 0;
}
#endif /* ADD_H_ */
