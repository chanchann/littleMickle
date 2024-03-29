#include <vector>
#include <cmath>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;

void die(const string& msg);

int main(void)
{
	initscr();

	vector<string> options;
	options.push_back("Register");
	options.push_back("Login");
	options.push_back("Other ...");
	options.push_back("Exit");

	mvaddstr(0, 0, "Main Menu");

	for (unsigned int i = 0; i < options.size(); i++) {
		mvprintw(4+(i*2), 10, "%d. %s", i+1, options[i].c_str());
	}

	mvprintw(4+(options.size()*2)+1, 10, "Use arrow keys to move; Enter to select:");

	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();

	int selection = 0;
	while(true) {
		int ch = getch();
		mvchgat(4+(selection*2), 10+3, options[selection].length(), 0, 0, NULL);
		switch(ch) {
			case KEY_DOWN:
				selection++;
				break;
			case KEY_UP:
				selection--;
				break;
		}
		selection=std::min(std::max(selection, 0), (int)(options.size()-1));
		mvchgat(4+(selection*2), 10+3, options[selection].length(), A_REVERSE, 0, NULL);
	}

	endwin();
	return 0;
}

void die(const string& v)
{
	endwin();
	std::cerr << v << std::endl;
	exit(1);
}
