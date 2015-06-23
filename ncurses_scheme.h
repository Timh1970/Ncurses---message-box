#ifndef _GUARD_NCURSES_SCHEME
#define _GUARD_NCURSES_SCHEME

#include <ncurses.h>
#include <string>

#define COLOR_ORANGE 202
#define COLOR_BLACK_233 233 //Darkest 233 - Lightest 252
#define COLOR_BLACK_234 234 
#define COLOR_BLACK_235 235
#define COLOR_BROWN 52

enum justify {
	LEFT,
	CENTRE,
	RIGHT
};

enum expressions {
	EMAIL,
	TELEPHONE,
	REQ_STRING
};

enum colours {
	/*
	Used to reference colour pairs.  Note that first colour pair
	starts at 1 rather than 0
	*/	
	RBK = 1,	//Cyan
	RBK235,		//Red on Dark Grey
	CBK,		//Red
	CBK235,		//Cyan on Dark Grey
	GBK,		//Green
	YBK,		//Yellow
	YBK235,		//Yellow on Dark Grey
	GWH,		//Green on white
	MWH,		//Magenta on white
	BKG,		//Black on green
	GBK233,		//Green on Dark Grey
	GBK235,		//Green on Dark Grey
	BRBK235,	//Brown on Dark Grey
	ORAK235		//Orange on Dark Grey
};

//FUNCTIONS			
void init_scheme();
std::string regex_validate(unsigned int regex_type); 


#endif