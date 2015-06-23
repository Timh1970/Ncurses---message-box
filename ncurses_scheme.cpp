#include <cstring>
#include <string>
#include <ncurses.h>

#include "ncurses_scheme.h"

#define STD_HEADER = 5
#define PICKLIST_HEADER = 2

void init_scheme() {

//SET UP NCURSES
	slk_init(3);
	initscr();
	cbreak();
	noecho();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();

//SET UP THE COLOURS	
	init_pair(RBK, COLOR_RED, COLOR_BLACK);
	init_pair(GBK, COLOR_GREEN, COLOR_BLACK);
	init_pair(CBK, COLOR_CYAN, COLOR_BLACK);
	init_pair(CBK235, COLOR_CYAN, COLOR_BLACK_235);
	init_pair(YBK, COLOR_YELLOW, COLOR_BLACK);
	init_pair(YBK235, COLOR_YELLOW, COLOR_BLACK_235);
	init_pair(GBK235, COLOR_GREEN, COLOR_BLACK_235);
	init_pair(BRBK235, COLOR_BROWN, COLOR_BLACK_235);
	init_pair(RBK235, COLOR_RED, COLOR_BLACK_235);
	init_pair(ORAK235, COLOR_ORANGE, COLOR_BLACK_235);
	
	init_pair(GWH, COLOR_GREEN, COLOR_WHITE);
	init_pair(MWH, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(BKG, COLOR_BLACK, COLOR_GREEN);
	
}



