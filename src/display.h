/*
 * display.h
 * 
 * Copyright 2013 Kasra Madadipouya <kasra@madadipouya.com>
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
#include<curses.h>
#include<menu.h>
#include<stdlib.h>
#include<string.h>
#ifndef DISPLAY_H_
#define DISPLAY_H_
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
char subchoices[4096][4096];
static int counter=0;
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
strcpy(subchoices[counter],argv[0]);
strcat(subchoices[counter]," ");
strcat(subchoices[counter],argv[1]);
counter++;
return 0;
}
void show()
{
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		//printf("\n");
		rc = sqlite3_open("contact.sqlite", &db);
		if(rc)
		{
		      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		      sqlite3_close(db);
		      //return(1);
	    }
		//printf("Name\t\tNumber\n");
		//printf("**************************\n");
		rc = sqlite3_exec(db, "SELECT * FROM list WHERE 1=1 ORDER BY LOWER(name) ASC;", callback, 0, &zErrMsg);
		//printf("**************************\n\n");
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
		int temp=printing();
		counter=0;
//int i=0;
//for(i=0;i<x;i++)
//printf("%s\n",choices[i]);
}
int printing()
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	int x,y;
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
//strcpy(choices[2],"BIGGIE");
//strcpy(choices[ARRAY_SIZE(choices)],(char *)NULL);
	/* Create items */
clear();
refresh();
        n_choices = ARRAY_SIZE(subchoices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < counter; ++i)
                my_items[i] = new_item(subchoices[i],subchoices[i]);
//                my_items[i] = new_item("Ka","");

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Set menu option not to show the description */
	menu_opts_off(my_menu, O_SHOWDESC);

	/* Create the window to be associated with the menu */
	getmaxyx(stdscr,y,x);
        my_menu_win = newwin(y-2, x, 0, 0);
        keypad(my_menu_win, TRUE);
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
	printw("%d",x);
        set_menu_sub(my_menu, derwin(my_menu_win, (y-10), x-1, (x/25), 1));
	set_menu_format(my_menu, (y-10), (x/25));
	set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1,x/2-(strlen("Contact displaying")/2),strlen("Contact displaying"), "Contact displaying", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, x-2);
	mvwaddch(my_menu_win, 2, x-1, ACS_RTEE);
	attron(COLOR_PAIR(2));
//	mvprintw(LINES - 3, 0, "Use PageUp and PageDown to scroll %d",y);
	mvprintw(LINES - 2, 0, "Use Arrow Keys to navigate (ESC to Back)");
	attroff(COLOR_PAIR(2));
	refresh();

	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	while((c = wgetch(my_menu_win)) != 27)
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(my_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(my_menu, REQ_SCR_UPAGE);
				break;
			case 9:
				menu_driver(my_menu,REQ_NEXT_ITEM);
				break;
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < counter; ++i)
                free_item(my_items[i]);
	endwin();
	clear();
	refresh();
}
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;
	if(win == NULL)
	win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
#endif /* DISPLAY_H_ */
