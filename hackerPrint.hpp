#include <Windows.h>
#include <cmath>
#include <iostream>
class hackerPrint {
private:
static inline void gotoxy(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}


public:
	static void print(int x, int y, std::string text, int sleepInterval = 1, int textCompleteness = 2) {
		const char * txt = text.c_str();
		std::string writtenText = "";
		for (int i = 0; i < pow(sizeof(text), 2); i++) {
			writtenText = "";
			for (int j = 0; j < text.length(); j++) {
				gotoxy(x + j, y);
				writtenText += (char)(txt[j] + j / ((i ^ j) + textCompleteness));
				std::cout << (char)(txt[j] + j / ((i ^ j) + textCompleteness));
				Sleep(sleepInterval);
			}
			if (writtenText == text && i > 5) // > 5 because at the start the text is just like the normal text and gets over the time changed
				return;
		}
	}
};