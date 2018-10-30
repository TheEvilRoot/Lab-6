#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

// Codes for second char for arrows keys
#define KEY_UP 72
#define KEY_DOWN 80

// Visual Studio is sucks
#define scanf scanf_s


// Get constant number of menu items
int getMenuItemsCount(void);

// Get constant string per each option
const char * getOptionTitle(int);

// Reprint menu with selected option (param 1)
void updateScreen(int);

// Moves pointer up
void moveUp(int*);

// Moves pointer down
void moveDown(int*);

// Clear screen and print title of option (option position - param 1)
void prepareScreen(int);

// Converts number (param 1) into k-based (param 2) numeral system.
long convert(int, int);

// Request user for current number
bool inputNumber(void);

// Check is current number was specified. If not, request from user
bool checkNumber(void);

// Print current number in 8, 10, 16 -based sysyems
bool getNumber(void);

// Get reciprocal of current. 
bool getReciprocal(void);

// Convert current number into k-based numeral system (k will requested from user)
bool getNumberInNS(void);

// Get some info (useless) about this program.
void about(void);

// Show goodby and exit ;)
void exitProgram(void);

// Await for user action to show menu back
void awaitToGetBack(void);

// Handle selected item click
void handleEnter(int);

long number = 0;
bool isNumberSpecified = false;

int main() {

	// Holds input char
	char key;

	// Is up/down key triggered
	bool keyTrigger = false;

	//Is enter key triggered
	bool enterTrigger = false;

	// Current menu position
	int pos = 0;
	
	// First print menu
	updateScreen(pos);


	while ((key = _getch()) != '#') { // Backdoor. Just press # to exit the program. Idk why.
		switch (key) {
			// -32 - first code accepted on up/down key triggered.
			case -32: {
				keyTrigger = true;
				break;
			}
			// 13 - first code accepted on enter key triggered
			case 13: {
				enterTrigger = true;
				break;
			}
			default: {
				// If first code was -32 keyTrigger - true. If it is, check second code for up/down key
				if (keyTrigger) {
					switch (key) {
						case KEY_UP: {
							moveUp(&pos);
							updateScreen(pos);
							break;
						}
						case KEY_DOWN: {
							moveDown(&pos);
							updateScreen(pos);
							break;
						}
					}

					// Turn the trigger off
					keyTrigger = false;
				}
				else if (enterTrigger) {
					// If first code was 13 enterTrigger - true. If it is, check second code for enter code (0)
					if (key == 0) {
						handleEnter(pos);
						updateScreen(pos);
					}

					// Turn the trigger off
					enterTrigger = false;
				}
				break;
			}
		}
	}
	return 0;
}

int getMenuItemsCount() {
	return 6;
}

const char * getOptionTitle(int pos) {
	switch (pos) {
		case 0: {
			return "Input number";
		}
		case 1: {
			return "Get number";
		}
		case 2: {
			return "Get reciprocal number";
		}
		case 3: {
			return "Convert to k-based NS";
		}
		case 4: {
			return "About";
		}
		case 5: {
			return "Exit";
		}
		default: {
			return "[INVALID]";
		}
	}
}

void updateScreen(int pos) {
	system("cls");
	for (int i = 0; i < getMenuItemsCount(); i++) {
		if (pos == i) {
			printf("[*] %s\n", getOptionTitle(i));
		}
		else {
			printf("[ ] %s\n", getOptionTitle(i));
		}
	}
}

void moveUp(int *posPtr) {
	if (*posPtr <= 0) {
		*posPtr = getMenuItemsCount() - 1;
	}
	else {
		*posPtr -= 1;
	}
}

void moveDown(int *posPtr) {
	if (*posPtr >= getMenuItemsCount() - 1) {
		*posPtr = 0;
	}
	else {
		*posPtr += 1;
	}
}

void prepareScreen(int pos) {
	system("cls");
	printf("\t%s\n\n", getOptionTitle(pos));
}

long convert(int number, int base) {
	if (number == 0 || base == 10)
		return number;
	return (number % base) + 10 * convert(number / base, base);
}


bool inputNumber() {
	do {
		printf("Enter new number: ");
		fflush(stdin);
		fseek(stdin, 0, SEEK_END);
	} while (!scanf("%ld", &number));
	isNumberSpecified = true;
	return false;
}


bool checkNumber() {
	if (!isNumberSpecified) {
		printf("You not specified number yet. Do you want to do this now?\nPress 'y' to enter new number, 'n' to get back to menu\n");
		if (_getch() == 'y') {
			inputNumber();
			fflush(stdin);
			fseek(stdin, 0, SEEK_END);
			return true;
		}
		else {
			return false;
		}
	}
	else return true;
}

bool getNumber() {
	if (checkNumber()) {
		printf("Your number:\n");
		printf("\tIn decimal: %ld\n", number);
		printf("\tIn octal: %o\n", number);
		printf("\tIn hexadecimal: 0x%x\n", number);
		return true;
	}
	else return false;
}

bool getReciprocal() {
	if (checkNumber()) {
		printf("Reciprocal number of %ld is 1/%ld. It approximately eqials %lf\n", number, number, (double) 1 / number);
	}
	else return false;
}

bool getNumberInNS() {
	if (checkNumber()) {
		int base = 0;
		do {
			printf("Enter numeral system base[2..]: ");
			fflush(stdin);
			fseek(stdin, 0, SEEK_END);
		} while (!scanf("%ld", &base) || base <= 1);
		if (base == 10) { // Some special cases like octal, decimal or hexadecimal NS
			printf("\n%ld in %d-based numeral system is %ld", number, base, number);
		}
		else if (base == 16) {
			printf("\n%ld in %d-based numeral system is 0x%xu", number, base, number);
		}
		else if (base == 8) {
			printf("\n%ld in %d-based numeral system is %o", number, base, number);
		}
		else {
			printf("\n%ld in %d-based numeral system is %ld", number, base, convert(number, base));
		}

		fflush(stdin);
		fseek(stdin, 0, SEEK_END);
		return true;
	}
	else return false;
}

void about() {
	printf("IDontKnowHowIShouldCallThisProgram\nVersion: 1.2\nBuild: 30102018-3\nAuthor: TheEvilRoot\nURL: https://github.com/TheEvilRoot/Lab-6 (Private)\n");
}

void exitProgram() {
	printf("Goodby!\n");
}

void awaitToGetBack() {
	printf("\nEnter any key to get back to menu...");
	getchar();
}

void handleEnter(int pos) {
	prepareScreen(pos);
	switch (pos) {
		case 0: {
			if (inputNumber()) {
				awaitToGetBack();
			}
			break;
		}
		case 1: {
			if (getNumber()) {
				awaitToGetBack();
			}
			break;
		}
		case 2: {
			if (getReciprocal()) {
				awaitToGetBack();
			}
			break;
		}
		case 3: {
			if (getNumberInNS()) {
				awaitToGetBack();
			}
			break;
		}
		case 4: {
			about();
			awaitToGetBack();
			break;
		}
		case 5: {
			exitProgram();
			printf("\nEnter any key exit...");
			getchar();
			exit(0);
			break;
		}
	}
	fflush(stdin);
	fseek(stdin, 0, SEEK_END);
}