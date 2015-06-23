#ifndef _GUARD_MSG_BOX
#define _GUARD_MSG_BOX

#include <ncurses.h>

class msg_box {

	private:
	
		WINDOW *Nwindow;
		int maxx, maxy;
		int winheight;
		std::string outputstring;
	
		//FUNCTIONS
		std::string Format_Output(std::string &wokstring, const int Columns);
		std::string Split_Output(const std::string &strMessage, const int nFieldLength);
		//void print_in_middle(WINDOW *win, int starty, int startx, int width, 
			//const char *string, chtype color);	
	
	public:
		//CONSTRUTORS
		msg_box();
		
		//FUNCTIONS		
		bool question(std::string strMsg="Demo Mode", std::string title="QUESTION ?", int nCols=50);
		void info(std::string strMsg="Demo Mode", std::string title="ALERT", int nCols=50);
		
		//DESTRUCTOR
		~msg_box();
};

#endif