#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#define OS          "Windows"
#define CONTINUE    "An error has occurred. To continue:"
#define ENTER       "Press Enter to return to Windows, or"
#define CTRLALTDEL  "Press CTRL+ALT+DEL to restart your computer. If you do this,"
#define UNSAVED     "you will lose any unsaved information in all open applications."
#define ERROR       "Error: 0E : 016F : BFF9B3D4"
#define PRESSKEY    "Press any key to continue"
#define ROWS        10
#define COLS        64
#define BKGND_CLEAR "\033[H\033[J"
#define BKGND_BLUE  "\x1B[44m"
#define BKGND_GREY  "\x1B[47m"
#define BKGND_NORM  "\x1B[0m"
#define COLOR_WHITE "\x1B[37m"
#define COLOR_BLUE  "\x1B[34m"
#define CURSOR_OFF  "\e[?25l"
#define CURSOR_ON   "\e[?25h"

int width = 0, height = 0, indent = 0;

static void get_dims() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	width = w.ws_col;
	height = w.ws_row;
}

static void cursor(int on) {
	if (on == 0) {
		printf("%s", CURSOR_OFF);
	} else {
		printf("%s", CURSOR_ON);
	}
}

static void clearscreen() {
	printf("%s", BKGND_CLEAR);
}

static void newline() {
	printf("%s%*s%s", BKGND_BLUE, width, " ", BKGND_NORM);
}

static void textos(char *text) {
	int local_indent = 0, length = 0;

	local_indent = indent + ((COLS - 9) / 2);
	length = (int)strlen(text);

	printf("%s%*s%s%s%s %s %s%s%s", BKGND_BLUE, local_indent, " ", BKGND_NORM, BKGND_GREY, COLOR_BLUE, text, BKGND_NORM, BKGND_BLUE, COLOR_WHITE);
	printf("%*s%s%s", width - length - local_indent, " ", BKGND_NORM, COLOR_WHITE);
}

static void textline(char *text) {
	int length = 0;

	length = (int)strlen(text);

	printf("%s%s%*s%s%*s%s%s", BKGND_BLUE, COLOR_WHITE, indent, " ", text, width - length - indent, " ", BKGND_NORM, COLOR_WHITE);
}

int main() {
	int i = 0, l = 0;

	get_dims();
	clearscreen();

	indent = (width - COLS) / 2;

	for (i = 0, l = (height - ROWS) / 2; i < l; i++) {
		newline();
	}

	textos(OS);
	newline();
	textline(CONTINUE);
	newline();
	textline(ENTER);
	newline();
	textline(CTRLALTDEL);
	textline(UNSAVED);
	newline();
	textline(ERROR);
	newline();
	textline(PRESSKEY);

	for (i = 0, l = ((height - ROWS) / 2) - 2; i < l; i++) {
		newline();
	}

	cursor(0);

	while (getchar() != '\n') {
		
	}

	cursor(1);

	return 0;
}