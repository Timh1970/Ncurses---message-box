//----------------------------//
// PREPROCESSOR DIRECTIVES    //
//----------------------------//
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>	//stringstream
#include <algorithm>  //count
#include <iomanip>
#include <cctype>
#include <ncurses.h>

#include "ncurses_scheme.h"
#include "msg_box.h"
#include "ncurses_utils.h"

using std::string;
using std::stringstream;

//----------------------------//
// CONSTRUCTOR		          //
//----------------------------//
msg_box::msg_box() {
//FORWARD DECLARATIONS
	WINDOW *Nwindow = NULL;
	maxx = 0; 
	maxy = 0;
	curs_set(0);	
	winheight = 0;
	string outputstring ="";
	
//GET SCREEN SIZE
	getmaxyx(stdscr, maxy, maxx);

}

//----------------------------//
// DESTRUCTOR		          //
//----------------------------//
msg_box::~msg_box() {
	delwin(Nwindow);
	touchwin(stdscr);
}

//----------------------------//
// FUNCTIONS		          //
//----------------------------//

				//**************************************************************//
				//	QUESTION BOX (return Y/N)									//
				//**************************************************************//
bool msg_box::question(string strMsg, string title, int nCols) {
	int ch = 0;
	bool answer = FALSE;
	if (nCols < 40) nCols = 40;
	
//CALL FORMATTING FUNCTION
	if (strMsg.find("\n") == std::string::npos) 
		outputstring = Format_Output(strMsg, nCols);
	else
		outputstring = Split_Output(strMsg, nCols);
		
	winheight = outputstring.length() / nCols;
	
//ERROR MESSAGE IF STRING WILL NOT FIT TO BOX HEIGHT
	if ((winheight +7) >= maxy) {
		nCols = 40;
		string ErrMsg = ("SYSTEM ERROR: The number of lines required to fit the message on the" \
		"window exceeds the size of the screen.\n\nEither make the filed wider or the message " \
		"shorter");
		outputstring.clear();
		outputstring = Split_Output(ErrMsg, nCols);
		winheight = outputstring.length() / nCols;
	}

//INITIALISE WINDOW
	Nwindow = newwin( winheight + 7, nCols + 4, ( (maxy - (winheight + 7)) / 2), \
		((maxx - (nCols + 4)) / 2) );
	box(Nwindow, 0, 0);	
	nutil::print_in_middle( Nwindow, 1, 0, nCols + 4, title.c_str(), COLOR_PAIR(GBK) );
	WINDOW *body = derwin(Nwindow, winheight, nCols, 3, 2);
	keypad(Nwindow, TRUE);
	wattron(body, COLOR_PAIR(CBK));
	
	waddstr(body, outputstring.c_str());
	
	wattroff(body, COLOR_PAIR(CBK));
	nutil::print_in_middle( Nwindow, winheight + 4, 0, nCols + 4, "<Press: \'y\' for yes,  \'n\' for no>", \
		COLOR_PAIR(GBK) );
	wrefresh(Nwindow);
	
	/*
	tolower converts input to lower case so that loop runs correctly even if caps lock is on 
	
	Note that this requires the inclusion of <cctype>
	*/
	while ( tolower(ch) != 'y' && tolower(ch) != 'n') {
		ch = getch();
	}
	switch (tolower(ch)) {
		case 'y':
			answer = TRUE;
			break;
		case 'n':
			answer = FALSE;
			break;
	}
	
	return (answer);
}

				//**************************************************************//
				//	INFORMATION BOX (no return)									//
				//**************************************************************//
void msg_box::info(string strMsg, string title, int nCols) {
	
	if (nCols < 30) nCols = 30;
//CALL FORMATTING FUNCTION
	if (strMsg.find("\n") == std::string::npos) 
		outputstring = Format_Output(strMsg, nCols);
	else
		outputstring = Split_Output(strMsg, nCols);
		
	winheight = outputstring.length() / nCols;
	
//ERROR MESSAGE IF STRING WILL NOT FIT TO BOX HEIGHT
	if ((winheight +7) >= maxy) {
		nCols = 40;
		string ErrMsg = ("SYSTEM ERROR: The number of lines required to fit the message on the" \
		"window exceeds the size of the screen.\n\nEither make the filed wider or the message" \
		"shorter");
		outputstring.clear();
		outputstring = Split_Output(ErrMsg, nCols);
		winheight = outputstring.length() / nCols;
	}

//INITIALISE WINDOW
	Nwindow = newwin( winheight + 7, nCols + 4, ( (maxy - (winheight + 7)) / 2), \
		((maxx - (nCols + 4)) / 2) );
	box(Nwindow, 0, 0);	
	nutil::print_in_middle( Nwindow, 1, 0, nCols + 4, title.c_str(), COLOR_PAIR(RBK) );
	WINDOW *body = derwin(Nwindow, winheight, nCols, 3, 2);
	keypad(Nwindow, TRUE);
	wattron(body, COLOR_PAIR(CBK));
	
	waddstr(body, outputstring.c_str());
	
	wattroff(body, COLOR_PAIR(CBK));
	nutil::print_in_middle( Nwindow, winheight + 4, 0, nCols + 4, "<Press any key to continue>", \
		COLOR_PAIR(GBK) );
	wrefresh(Nwindow);
	getch();
}

				//**************************************************************//
				//	FORMAT STRING - Without new lines							//
				//**************************************************************//
string msg_box::Format_Output(string &workstring, const int Columns) {
//FORMAT THE STRING
	int str_length = workstring.length();
	
	for (int lines = 1; (lines * Columns) < str_length; ++lines) {
		unsigned nFound = workstring.find_last_of(" ", Columns * lines);
		int padding = (Columns * lines) - nFound;
		workstring.erase(nFound, 1);
		
		for (int i = 0; i < padding; ++i) {
			workstring.insert(nFound, " ");
		}
		
		str_length = workstring.length();
	}

	if ((str_length % Columns) != 0) {
		workstring.append( (Columns - (str_length % Columns)), ' ' );
	}
	
	return workstring;
}

				//**************************************************************//
				//	SPLIT STRING - With new lines								//
				//**************************************************************//
string msg_box::Split_Output(const string &strMessage, const int nFieldLength) {

//DECLARE A LOCAL COPY OF THE STRING
	string strTemp = strMessage;
		
//REMOGE ANY TRAILING NEW LINE CHARACTERS FROM THE STRING	
	strTemp.erase(std::find_if(strTemp.rbegin(), strTemp.rend(), \
	std::bind1st(std::not_equal_to<char>(), '\n')).base(), strTemp.end());	
				
//DECLARATIONS
	size_t newline_chars = count(strTemp.begin(), strTemp.end(), '\n');
	int substr_start = 0;
	int found = strTemp.find_first_of("\n", substr_start);
	//int str_len = strTemp.length();;
	int substr_len = 0;
	string workstring = "";
	stringstream ss;		
		
//FORMAT THE STRING
	for (unsigned int i = 0; i < newline_chars +1; ++i) {
		
		substr_len = (found - substr_start);		
		workstring = strTemp.substr(substr_start, substr_len);		
		ss << Format_Output(workstring, nFieldLength);
		
		for (; (strTemp.at(found +1) ==  '\n'); ++found) {
			ss.fill(' ');
			ss << std::setw(nFieldLength) << " ";
			++i;
		}
			
		++found;
		substr_start = found;
			
		if ( (strTemp.find_first_of("\n", substr_start)) != string::npos)
			found = strTemp.find_first_of("\n", substr_start);
		else
			found = strTemp.find_last_of("\n", substr_start);
			
		workstring.clear();				
	}
		
	return 	ss.str();
}
