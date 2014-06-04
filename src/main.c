/*
 * main.c
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
#include<menu.h>
#include<ncurses.h>
#include<form.h>
#include<string.h>
#include<stdlib.h>
#include"display.h"
#include"search.h"
#include"remove.h"
#include"add.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
char *str;
char *choices[] = {
                        "[1] Adding a contact",
                        "[2] Removing a contact",
                        "[3] Searching for a contact by name",
                        "[4] Searching for a contact by number",
                        "[5] Displaying contact list",
			"[6] Exit",
                        (char *)NULL,
                  };
int x,y;
//void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void func(char *name);
void upon(char par[100]);
int uponadd();
int main()
{	ITEM **my_items;
	int c;
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	clear();	
	refresh();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	getmaxyx(stdscr,y,x);
	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i=0;i<n_choices;++i)
	{
                my_items[i] = new_item(choices[i],"");
		set_item_userptr(my_items[i], func);
	}
	my_items[n_choices] = (ITEM *)NULL;
	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);
	/* Create the window to be associated with the menu */
        my_menu_win = newwin(10, 45, (y/2)-6,(x/2)-22 );
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " * ");
	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Ncurses Phone Book (NPB)", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
	mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
	mvprintw(LINES - 2, 0, "Press ESC to exit");
	refresh();
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
//upon();
	while((c = wgetch(my_menu_win)) != 27)
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			{	ITEM *cur;
				void (*p)(char *);
				cur = current_item(my_menu);
				p = item_userptr(cur);
				p((char *)item_name(cur));
				refresh();
				//printw("%s",item_name(cur));
				if(!strcmp("[6] Exit",item_name(cur)))
				{
					unpost_menu(my_menu);
				        free_menu(my_menu);
					endwin();
					return 0;
				}
				else if(!strcmp("[3] Searching for a contact by name",item_name(cur)))
				{
					upon("Search by name");
					//if(strlen(str)>1)
					
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
				}
				else if(!strcmp("[4] Searching for a contact by number",item_name(cur)))
				{
					upon("Search by number");
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
				}
				else if(!strcmp("[2] Removing a contact",item_name(cur)))
				{
					upon("Enter contact name to remove");
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
				}
				else if(!strcmp("[5] Displaying contact list",item_name(cur)))
				{
					show();
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
				}
				else if(!strcmp("[1] Adding a contact",item_name(cur)))
				{
					int ret=uponadd();			
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
					if(ret==1)
					{
					int trash=outprint();
					clear();
					set_menu_sub(my_menu, derwin(my_menu_win, 6, 40, 3, 1));
					/* Set menu mark to the string " * " */
				        set_menu_mark(my_menu, " * ");
					/* Print a border around the main window and print a title */
				        box(my_menu_win, 0, 0);
					print_in_middle(my_menu_win, 1, 0, 45, "Welcome to Simple Phone Book Application", COLOR_PAIR(1));
					mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
					mvwhline(my_menu_win, 2, 1, ACS_HLINE, 43);
					mvwaddch(my_menu_win, 2, 44, ACS_RTEE);
					mvprintw(LINES - 2, 0, "Press ESC to exit");
					refresh();
					/* Post the menu */
					post_menu(my_menu);
					wrefresh(my_menu_win);
					}
				}
				pos_menu_cursor(my_menu);
				break;
			}
		}
                wrefresh(my_menu_win);
	}	
	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
//        for(i = 0; i < n_choices; ++i)
  //              free_item(my_items[i]);
	endwin();
}

/*void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
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
}*/
void func(char *name)
{	//move(20, 0);
//	clrtoeol();
	//mvprintw(20, 0, "Item selected is : %s", name);
}
void upon(char par[100])
{
	FIELD *field[2];
	FORM  *my_form;
	WINDOW *my_form_win;
	int ch, rows, cols;
	int ext=0;
	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize few color pairs */
   	init_pair(1, COLOR_RED, COLOR_BLACK);

	/* Initialize the fields */
	field[0] = new_field(1,40,0,0,0,0);
	//field[1] = new_field(1, 10, 8, 1, 0, 0);
	field[1] = NULL;

	/* Set field options */
	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
					      /* Field is filled up 		*/
	if(!strcmp("Search by number",par))
		set_field_type(field[0],TYPE_INTEGER,1);
	else
		set_field_type(field[0],TYPE_ALPHA,1);
//	set_field_back(field[1], A_UNDERLINE); 
//	field_opts_off(field[1], O_AUTOSKIP);
//	wmove(WINDOW *win, int y, int x);
	/* Create the form and post it */
	my_form = new_form(field);
	/* Calculate the area required for the form */
	scale_form(my_form, &rows, &cols);
	/* Create the window to be associated with the form */
        my_form_win = newwin(rows + 4, cols + 4, (y/2), (x/2)-18);
        keypad(my_form_win, TRUE);
	/* Set main window and sub window */
        set_form_win(my_form, my_form_win);
//        set_form_sub(my_form, derwin(my_form_win, rows, cols,2,2));
        set_form_sub(my_form, derwin(my_form_win,rows,cols,2,2));
	/* Print a border around the main window and print a title */
        box(my_form_win,0,0);
	print_in_middle(my_form_win, 1, 0, cols + 4,par, COLOR_PAIR(1));
	//mvwhline(my_form_win, 2, 1, ACS_HLINE, 43);
	post_form(my_form);
	wrefresh(my_form_win);
	mvprintw(LINES - 2, 0, "Press ESC to close the window");
	move((y/2)+2,(x/2)-16);
	refresh();

	/* Loop through to get user requests */
	while((ch = wgetch(my_form_win)) != 27)
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_BACKSPACE:
				/* Go to previous field */
				form_driver(my_form,REQ_DEL_PREV);
				break;
			case KEY_DC:
				form_driver(my_form,REQ_DEL_CHAR);
				break;
			case KEY_HOME:
				form_driver(my_form,REQ_BEG_FIELD);
				break;
			case KEY_END:
				form_driver(my_form,REQ_END_FIELD);
				break;
			case KEY_LEFT:
				form_driver(my_form,REQ_LEFT_CHAR);
				break;
			case KEY_RIGHT:
				form_driver(my_form,REQ_RIGHT_CHAR);
				break;
			case 10:
				{
				str=malloc(1000);
				form_driver(my_form,REQ_BEG_FIELD);
				sprintf(str, "%s", field_buffer(field[0],0));
				size_t len = 0;
			        char *frontp = str - 1;
    				char *endp = NULL;
				len = strlen(str);
    				endp = str + len;
				while( isspace(*(++frontp)) );
				while( isspace(*(--endp)) && endp != frontp );
				if( str + len - 1 != endp )		
            			*(endp + 1) = '\0';
				else if( frontp != str &&  endp == frontp )
				*str = '\0';
				endp = str;
			        if( frontp != str )
			        {
			            while( *frontp ) *endp++ = *frontp++;
			            *endp = '\0';
			        }
//				mvprintw(LINES - 2, 0, "%s %d",str,strlen(str));
//				refresh();
				ext=1;
				if(!strcmp("Search by name",par))				
				find(str);
				else if (!strcmp("Search by number",par))
				findnumber(str);	
				else if (!strcmp("Enter contact name to remove",par))
				del(str);		
				break;
				}
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				break;
		}
		if(ext==1)
		break;
	}
	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]); 
//	return 0;
}
int uponadd()
{
	FIELD *field[3];
	FORM  *my_form;
	WINDOW *my_form_win;
	int ch, rows, cols;
	int ext=0;
	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	/* Initialize few color pairs */
   	init_pair(1, COLOR_RED, COLOR_BLACK);
	/* Initialize the fields */
	field[0] = new_field(1, 40, 1, 0, 0, 0);
	field[1] = new_field(1, 40, 3, 0, 0, 0);
	field[2] = NULL;
	/* Set field options */
	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP); /* Don't go to next field when this */
					      /* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE); 
	field_opts_off(field[1], O_AUTOSKIP);
	int trash =set_field_type(field[0],TYPE_ALPHA,1);
	trash=set_field_type(field[1],TYPE_INTEGER,1);
	/* Create the form and post it */
	my_form = new_form(field);

	/* Calculate the area required for the form */
	scale_form(my_form, &rows, &cols);

	/* Create the window to be associated with the form */
	int xx,yy;
	getmaxyx(stdscr,yy,xx);
        my_form_win = newwin(rows + 4, cols + 4, (yy/2), (xx/2)-18);
        keypad(my_form_win, TRUE);

	/* Set main window and sub window */
        set_form_win(my_form, my_form_win);
        set_form_sub(my_form, derwin(my_form_win,rows,cols,2,2));

	/* Print a border around the main window and print a title */
        box(my_form_win, 0, 0);
	print_in_middle(my_form_win, 1, 0, cols + 4, "Add contact", COLOR_PAIR(1));
	post_form(my_form);
	wrefresh(my_form_win);
	mvprintw(LINES - 2, 0, "Use arrow keys to switch between fields | Press ESC to cancel");
	move((y/2)+3,(x/2)-16);
	refresh();
	/* Loop through to get user requests */
	while((ch = wgetch(my_form_win)) != 27)
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_BACKSPACE:
				/* Go to previous field */
				form_driver(my_form,REQ_DEL_PREV);
				break;
			case KEY_DC:
				form_driver(my_form,REQ_DEL_CHAR);
				break;
			case KEY_HOME:
				form_driver(my_form,REQ_BEG_FIELD);
				break;
			case KEY_END:
				form_driver(my_form,REQ_END_FIELD);
				break;
			case KEY_LEFT:
				form_driver(my_form,REQ_LEFT_CHAR);
				break;
			case KEY_RIGHT:
				form_driver(my_form,REQ_RIGHT_CHAR);
				break;
			case 9:
				form_driver(my_form,REQ_NEXT_FIELD);
				break;
			case 10:
				{
				char *str=malloc(1000);
				form_driver(my_form,REQ_BEG_FIELD);
				sprintf(str, "%s", field_buffer(field[0],0));
				size_t len = 0;
			        char *frontp = str - 1;
    				char *endp = NULL;
				len = strlen(str);
    				endp = str + len;
				while( isspace(*(++frontp)) );
				while( isspace(*(--endp)) && endp != frontp );
				if( str + len - 1 != endp )		
            			*(endp + 1) = '\0';
				else if( frontp != str &&  endp == frontp )
				*str = '\0';
				endp = str;
			        if( frontp != str )
			        {
			            while( *frontp ) *endp++ = *frontp++;
			            *endp = '\0';
			        }
				char *stp=malloc(1000);
				strcpy(stp,str);
				//mvprintw(LINES - 3, 0, "%s %d",stp,strlen(stp));
				//refresh();
				sprintf(str, "%s", field_buffer(field[1],0));
				len=0;
				frontp=str-1;
				endp=NULL;
				len = strlen(str);
    				endp = str + len;
				while( isspace(*(++frontp)) );
				while( isspace(*(--endp)) && endp != frontp );
				if( str + len - 1 != endp )		
            			*(endp + 1) = '\0';
				else if( frontp != str &&  endp == frontp )
				*str = '\0';
				endp = str;
			        if( frontp != str )
			        {
			            while( *frontp ) *endp++ = *frontp++;
			            *endp = '\0';
			        }
				if((strlen(stp)>0) && (strlen(str)>0))
				{
				newcontact(stp,str);
				ext=1;
				}
				else if(strlen(str)==0)
				form_driver(my_form, REQ_NEXT_FIELD);
				}
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				break;
		}
	if(ext==1)
	   break;
	}
	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]); 
	endwin();
	return ext;
}

