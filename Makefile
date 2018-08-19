/*
 * 
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
 * GNU General Public License for more details. <http://www.gnu.org/licenses/>
 * 
 * 
 */
main:
	cd src; gcc -O3 -o ../main main.c -lncurses -lsqlite3 -lform -lmenu
	cd src; cp contact.sqlite ../contact.sqlite
run:
	 ./main

clean:
	rm -f main contact.sqlite
