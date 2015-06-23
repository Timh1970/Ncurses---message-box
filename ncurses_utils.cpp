#include "ncurses_utils.h"
#include "msg_box.h"
#include <string>
#include <cstring>
#include <sstream>
#include <string>
#include <panel.h>
#include <algorithm>

using namespace std;


				//**************************************************************//
				//	PRINT IN THE MIDDLE											//
				//**************************************************************//

//Print a string in the centre of a given ncurses window
void nutil::print_in_middle(WINDOW *win, int starty, int startx, int width, 
	const char *string, chtype color) {
//DECLARATIONS	
	int length, x, y;
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

}

				//**************************************************************//
				//	DRAW A BOX INSIDE A WINDOW									//
				//**************************************************************//
void nutil::sub_box(WINDOW *win, int height, int width, int y_pos, int x_pos) {

//place a T in the left location to mark the end of the header
	//TOP LINE
	mvwaddch(win, y_pos, x_pos, ACS_ULCORNER);
	mvwhline(win, y_pos, x_pos +1, ACS_HLINE, width -2);
	mvwaddch(win, y_pos, x_pos + width -1, ACS_URCORNER);

	//VERTICALS
	mvwvline(win, y_pos +1, x_pos, ACS_VLINE, height -2);
	mvwvline(win, y_pos +1, x_pos + width -1, ACS_VLINE, height -2);

	//BOTTOM LINE
	mvwaddch(win, y_pos + height -1, x_pos, ACS_LLCORNER);
	mvwhline(win, y_pos + height -1, x_pos +1, ACS_HLINE, width -2);
	mvwaddch(win, y_pos + height -1, x_pos + width -1, ACS_LRCORNER);

	update_panels();
	doupdate();


}

				//**************************************************************//
				//	CLEAN STRING												//
				//**************************************************************//
string nutil::CleanString(string name){	

//REMOVE LEADING WHITESPACE
	name.erase(name.begin(), std::find_if(name.begin(), \
		name.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
	
//REMOVE TRAILING WHITESPACE
	name.erase(std::find_if(name.rbegin(), name.rend(), \
		std::bind1st(std::not_equal_to<char>(), ' ')).base(), name.end());
					
	return name;
}

				//**************************************************************//
				//	DEBUG MESSAGE BOX FUNCTIONS									//
				//**************************************************************//
void nutil::db() {
	update_panels();
	doupdate();
	msg_box().info("Break Point", "DEBUG");
	update_panels();
	doupdate();
}

void nutil::db(int number) {
	update_panels();
	doupdate();
	std::stringstream ss;
	ss << "The value returned is: " << number;
	msg_box().info(ss.str(), "DEBUG: ");
	update_panels();
	doupdate();
}

void nutil::db(std::string msg_string) {
	update_panels();
	doupdate();
	msg_box().info(msg_string, "DEBUG");
	update_panels();
	doupdate();
}