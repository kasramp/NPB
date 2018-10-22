main:
	cd src; gcc -O3 -o ../main main.c -lncurses -lsqlite3 -lform -lmenu
	cd src; cp contact.sqlite ../contact.sqlite
run:
	 ./main

clean:
	rm -f main contact.sqlite
