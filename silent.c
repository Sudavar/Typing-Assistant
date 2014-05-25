#include "silent.h"

int getchar_silent(){
    int ch;
    struct termios oldt, newt;

    /* Retrieve old terminal settings */
    tcgetattr(STDIN_FILENO, &oldt);

    /* Disable canonical input mode, and input character echoing. */
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );

    /* Set new terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /* Read next character, and then switch to old terminal settings. */
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

void treat_character(int next, string *line, Trie* dictionary, bool flag, int &caps){
	/* If it is the end of a word */
	if (!isalpha(next)) {
		dictionary->insert(dictionary->get_prefix());
		dictionary->clear_prefix();
		caps = 0;
	} else {
		dictionary->add_prefix(next);
		if (isupper(next))
			caps++;
	}
	*(line) += (char)next;
	if (flag)
		cout << *line;
	else
		cout << (char)next;
	/* If it is the end of the line */
	if (next == '\n') {
		line->clear();
	}
}

