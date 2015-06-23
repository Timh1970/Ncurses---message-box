/*
This file allows access to some basic functions that I have created to enhance some ncurses
features.
*/
#ifndef _GUARD_NCURSES_UTILS
#define _GUARD_NCURSES_UTILS

#include <string>

#include <panel.h>
#include <form.h>
#include <menu.h>




namespace nutil {
	
	void print_in_middle(WINDOW *win, int starty, int startx, int width, 
		const char *string, chtype color);
	
	/*
	Remove the whitespace from the leading and trailing ends of a string
	*/
	std::string CleanString(std::string name);
	
	/*
	Draw a box inside a window
	*/
	void sub_box(WINDOW *win, int height, int width, int y_pos, int x_pos);
	
	/*
	Debug pass int to message box
	*/
	void db(int number);
	
	/*
	Debug standare breakpoint
	*/
	void db();
	
	/*
	Debug string;
	*/
	void db(std::string msg_string);
	
	
	
}

#endif