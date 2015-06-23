# Ncurses---message-box

This code creates a popup message box with a title and a message.  The box is sized automatically although a width can be specified.  There are 2 versions of the box 1. an info() version where you press any key to exit; and 2. a question version that returns a boolean depending on whether 'y' or 'n' has been pressed.

As ncurses is a C library and I am working in c++ you may find that poetic licence has been used from time to time.  The code may need some error catching but it demonstrates the principle.

You can call the object anonymously and even has a demo mode if you call it without passing any arguments.

  msg_box().info();
  
Both the info() and question() versions have the same paramethers in the same order which are:

  (
    std::string message_box_text,
    std::string message_box_title,
    int number_of_columns
  )

The defaults are:
  
  question("Demo Mode", "QUESTION ?", 50);
  
and

  info("Demo Mode", "ALERT", 50);
  
The justifcation is left and there is no hyphenation.

The width of the message box (number_of_columns) can be set to any size you like however setting it small than the title string or larger than the size of the standard screen [getmaxyx(stdscr)] will cause undefined behaviour.

If the message_box_text string will not fit in a box of the given width then an alternate message will appear advising you of this error.

If this serves no other purpose in your program, it can make an excellent debuging tool and is great for setting brake points.

REQUIREMENTS
------------
<string>
<cstdlib>
<cstring>
<sstream>	
<algorithm>
<iomanip>
<cctype>
<ncurses.h>

ncurses_scheme   //included
msg_box          //included
ncurses_utils    //included

xterm-256color terminal (it may not need this, but it hasn't been tried without)

When I write my ncurses programs I use a style sheet type of structure so that I define colors (I'll leave the 'u' out to keep the American audience happy) in the same place, especially as I write programs that utilise all 256 colors and like to define the pairs without using magic numbers.  There's nothing special about it, it just makes it easier to alter.  This is done in ncurses_scheme which is included in this repo.

The only other thing of note is ncurses_utils which has a hand full of functions; some of which are not used at all for msg_box, but you will notice that there is an overloaded db() function that calls the msg_box class.  The things to note are as follows:

1.  All of the functions within ncurses_utils are placed within the nutil:: namespace.
2.  The db() function is written with the panels library in mind.  update_panels() and doupdate() are called before msg_box().info() in order to display the message box correctly whenever it is called.  If you are not using panels then it is easy enough to amend the code to use refresh(), wrefresh(), or whatever.
3.  You can call db() without arguments in which case it will just put up a message that says "Break Point", Pass it an integer, in which case you will get "The value returned is: " followed by the return value, or you can simply pass in a string or, thanks to std::string doing the converting, a c-string.


Note that I have built this and only ever tested it on AIX so it may not work with your platform, but the code and functionality are so basic that it should work on anything.  Please feel free to play with it and if you have to make any amendments to get it to run then please post them.


