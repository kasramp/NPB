/*
 * search.h
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
#include<curses.h>
#include<menu.h>
#include<stdlib.h>
#include<string.h>
#ifndef SEARCH_H_
#define SEARCH_H_
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
char subchoices[4096][4096];
//static int counter=0;
/*static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
strcpy(subchoices[counter],argv[0]);
strcat(subchoices[counter]," ");
strcat(subchoices[counter],argv[1]);
counter++;
return 0;
}*/
void find(char name[1024])
{
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char querystring[2048];
		strcpy(querystring,"SELECT name,number FROM list WHERE name LIKE '");
		strcat(querystring,name);
		strcat(querystring,"'");
		printf("\n");
		rc = sqlite3_open("contact.sqlite", &db);
		if(rc)
		{
		      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		      sqlite3_close(db);
		      //return(1);
	    }
		//printf("Name\t\tNumber\n");
		//printf("**************************\n");
		rc = sqlite3_exec(db, querystring, callback, 0, &zErrMsg);
		//printf("**************************\n\n");
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
		int temp=printing();
		counter=0;
}
void findnumber(char name[1024])
{
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		char querystring[2048];
		strcpy(querystring,"SELECT name,number FROM list WHERE number LIKE '");
		strcat(querystring,name);
		strcat(querystring,"'");
		printf("\n");
		rc = sqlite3_open("/home/kixz/Desktop/contact.sqlite", &db);
		if(rc)
		{
		      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		      sqlite3_close(db);
		      //return(1);
	    }
		printf("Name\t\tNumber\n");
		//printf("**************************\n");
		rc = sqlite3_exec(db, querystring, callback, 0, &zErrMsg);
		//printf("**************************\n\n");
		if( rc!=SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
		int temp=printing();
		counter=0;
}
#endif /* SEARCH_H_ */
