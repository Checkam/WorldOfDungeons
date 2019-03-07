#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

int main () {

	/*cbreak();*/
	/*initscr();
	timeout(1000);

	long int i;
	int c = -1;
	

	for ( i = 0; i < 1000000000; i++);

	c = getch();

	printf("\n%d\n", c);

	endwin();*/

	

	/*int i = -1;

	while ( i == -1 )
		i = getch();

	printf("\n%d\n", i);*/

	/*initscr();
	timeout(1000);
	int c = getch();
	endwin();
	printf ("%d %c\n", c, c);

	printf("fin du programme\n");

	return 0;*/

	/*int t[100];

	long long i;
	int j, max;
	int c;

	initscr();

	while ( 1 ) {

		for ( i = 0; i < 1000000000; i++ );
		
		timeout(1);
		c = getch();
		j = 0;
		while ( c != -1 ) {
			
			/*printf ("%c\n", c);
			t[j] = getch();
			j++;
		}

		system("clear");

		max = j;
		j = 0;

		while ( j < max ) {
			printf("%c", t[j]);

		}

	}

	endwin();*/

	int t[100];

	long long i;
	int j, max;
	int c;

	initscr();

	while ( 1 ) {

		for ( i = 0; i < 2000000000; i++ );
		
		timeout(1);
		c = getch();
		j = 0;
		while ( c != -1 ) {
			
			t[j] = c;
			c = getch();
			j++;
		}

		clear();

		max = j;
		j = 0;

		mvprintw(0, 0, "affichage : ");

		while ( j < max ) {
			printw("%c", t[j]);
			j++;

		}

	}

	endwin();
}
