/*
 * typing.cpp
 *
 *  Created on: May 6, 2014
 *      Author: Yury Kherimyan
 */
#include "Trie.h"
#include "silent.h"
#include <cstring>
#include <algorithm>

int main(int argc, char** argv){
	Trie *dictionary = new Trie;
	string line;
	char* tmp = NULL;
	string tmp_2 = string(getenv("HOME"));
	tmp_2 += "/.dict";

	if (argc == 2 || (argc == 3 && (string)argv[1] != "-d")) {
		cerr << argc << " Wrong Arguments. Usage: program_name [-d PATH]\n\t"
			"Where PATH is the location to dictionary" << endl;
		return EXIT_FAILURE;
	} else if (argc == 3 && (string)argv[1] == "-d") {
		tmp = argv[2];
		if (tmp != NULL)
	    		cout << "Current dictionary path is: " << tmp << endl;
	} else if (argc == 1) {
		cout << "Current dictionary path is: " << tmp_2 << endl;
	}
	string path = (tmp) ? string(tmp) : tmp_2;
	/* Reading dictionary from file */
	ifstream read(path.c_str());
	if(!read.is_open()) {
		cerr << "Problem loading dictionary, please check your PATH (" << path << ") value\n\t"
			"No dictionary loaded, no suggestion will be available at first" << endl;
	}
	cout << "Loading dictionary into memory" << endl;
	while( getline(read, line) ){
		dictionary->insert(line);
	}
	read.close();
	cout << "Done. You can start typing now, press TAB to display suggestions" << endl;

	int next;
	line.clear();
	bool no_suggestions = false;
	bool stop = false;
	int caps = 0;
	/* Keep reading one character at a time */
	while ((next = getchar_silent()) != EOF) {
		
		/* Print normal characters */
		if (isalpha(next) || ispunct(next) || next == ' ' || next == '\n') {
			treat_character(next, &line, dictionary, no_suggestions, caps);
			no_suggestions = false;
			continue;
		}
		/* Treat special characters differently */
		switch(next) {
	        case '\t':{              /* Just read a tab */

			string **suggests = dictionary->suggestions();
			if (suggests == NULL) {
				cerr << endl << "So sorry, couldn't find any suggestions or something went wrong..." << endl;
				dictionary->clean_prefix();
				no_suggestions = true;
				continue;
			}
			cerr << endl;
			int i;
			for (i = 0; i < N; i++) {
				if (suggests[i] != NULL)
					reverse(suggests[i]->begin(), suggests[i]->end());
				else{
					i++;
					break;
				}
			}
			bool flag = false;
			/* If there is only one word */
			if (i == 2) {
				next = '1';
			} else {
				/* Reading input after showing suggestions */
				do {
					next = getchar_silent();
					if (next == BACKSPACE){
						flag = true;
						dictionary->backspace();
						line = line.substr(0, line.size()-1);
						cout << line;
						break;
					} else if (next == VEOF) {
						stop = true;
						break;
					}
					if (isalpha(next) || ispunct(next) || next == ' ' || next == '\n') {
						treat_character(next, &line, dictionary, true, caps);
						flag = true;
						break;
					}
				} while (next < '1' && next > '9');
			}
			/* User chose a suggestion, must complete word in current line */
			if (!flag && !stop){
				while (next-49 >= N)
					next--; 
				string temp = suggests[next-49]->substr(dictionary->get_prefix().length());
				if (caps > 1) {
					for (unsigned int i = 0; i < temp.length(); i++) {
						line += toupper(temp[i]);
						dictionary->add_prefix(temp[i]);
					}
				} else {
					line += temp;
					for (unsigned int i = 0; i < temp.length(); i++)
						dictionary->add_prefix(temp[i]);
				}
				cout << line;
			}
			for (int i = 0; i < N; i++) {
				delete suggests[i];
			}
			delete[] suggests;
			break;
		}
	        case BACKSPACE:         /* Just read a backspace */

	            /* Move the cursor one step back, print space, and move
	             * cursor back once more to imitate backward character
	             * deletion.
	             */
			dictionary->backspace();
			line = line.substr(0, line.size()-1);
		        cout << "\b \b";
	        	break;

	        case VEOF:              /* Just read EOF (Ctrl-D) */

	            /* The EOF character is recognized only in canonical input
	             * mode. In noncanonical input mode, all input control
	             * characters such as Ctrl-D are passed to the application
	             * program exactly as typed. Thus, Ctrl-D now produces
	             * this character instead.
	             */
			stop = true;
			break;
	        default:
	            continue;
	        }
		if (stop)
			break;
	    }
	ofstream write(path.c_str());
	cout << "\nSaving dictionary.\n"
		"Exiting program. Thank you for using it." << endl;
	dictionary->print(write);
	write.close();
	delete dictionary;
	return EXIT_SUCCESS;
}
