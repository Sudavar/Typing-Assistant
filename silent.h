#ifndef SILENT_H_
#define SILENT_H_

#include <sys/ioctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "Trie.h"

#define BACKSPACE 0x7f

int getchar_silent();
void treat_character(int, string*, Trie*, bool, int&);

#endif /* SILENT_H_ */
