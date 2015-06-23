#include <string>
#include <ncurses.h>

#include "msg_box.h"
#include "ncurses_scheme.h"
#include "ncurses_utils.h"
using std::string;

int main() {
//INITIALISE CURSES
	init_scheme();
	
	string welcome("Welcome to my message box class, Please read the readme file and review main to see how the class works");
	msg_box().info(welcome, "Welcome", 30);
	refresh();
	
	
	//The msg_box objecgts args are (string "message", string "message title", int width)
	//Note: the box is padded so if you tell the object that the width is 40 chars then 
	//the true with of the box will be 44 which is 2 padding + 40chars + 2 padding.
	

//TEST THE QUESTION MESSAGE BOX
	
	string question_string("We are now testing that the question message box is working correctly " \
		"the result will be printed to the standard screen: \n\n1 for yes and 0 for no");
	bool q = msg_box().question(question_string, "LONG STRING ALERT", 35);
	refresh();
	mvprintw(LINES -2, 1, "The value returned was %d", q);
	mvprintw(LINES -1, 0, "Press any key to continue.");
	refresh();
	getch();
	move(LINES -2, 0);
	clrtobot();
	
	
	
//SHOULD NOT FIT ON SCREEN, (IF IT DOES MAKE THE SCREEN SMALLER AND RESTART THE PROGRAM TO GET THE ERROR MESSAGE)
	string line_string("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec" 
		"odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh" 
		"elementum imperdiet. Duis sagittis ipsum.\n\n\nPraesent mauris. Fusce nec tellus sed augue" 
		"semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti" 
		"sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur" 
		"sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque" 
		"nibh. Aenean quam. In scelerisque sem at dolor.\n\nMaecenas mattis. Sed convallis" 
		"tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus," 
		"iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia" 
		"aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in," 
		"nibh. Quisque volutpat condimentum velit."); 
	msg_box().info(line_string, "LONG STRING: Should not fit", 30);
	refresh();
	
	
//BY MAKING THE BOX LARGER THE STRING SHOULD NOW FIT IN IT AND NO ERROR SHOULD BE RETURNED
	msg_box().info(line_string, "LONG NEW LINE TEST STRING", 60);
	refresh();

//HERE IS SOMETHING A BIT MORE ELABORATE 	
	string helpstring("NAVIGATION -\n  |Previous Field:\n  |--> [up] arrow\n  |--> <shift> + " \
	"<tab>\n\n  |Next Field:\n  |--> [down] arrow\n  |--> <tab>\n  |--> <enter>\n\nFIELDS -\n" \
	"      Clear Field:  <delete>\n      Delete Character:  <backspace>\n      Move Left:  " \
	"[left] arrow\n      Move Right:  [right] arrow\n\nFORM -\n      Clear Form [F9]\n      " \
	"Save [F5]");
	msg_box().info(helpstring, "Customer form - quick help");
	refresh();

//DEFAULT DEBUG MESSAGE BOX  (create a brake point)
	nutil::db();
	refresh();	
//DEBUG MESSAGE BOX RETURNING A NUMBER
	int mynum = 123;
	nutil::db(mynum);
	refresh();	
//AND FINALLY STRING
	string mystr("extremely useful for debugging sql statements: \n\nSELECT customer_name, customer_tel WHERE customer_id = 153");
	nutil::db(mystr);
	refresh();	
	
	endwin();
	
return 0;
}