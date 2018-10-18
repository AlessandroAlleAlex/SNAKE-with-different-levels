#include <ncurses.h>

int main() {
	// Initialize ncurses
	initscr();
	clear();

	// Print a string on screen
	printw("Hi there.");

	// Wait until the user press a key
	getch();

	// Clear ncurses data structures
	endwin();
}