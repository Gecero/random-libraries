#ifndef HACKERPRINT_HPP
#define HACKERPRINT_HPP
#warning this library is deprecated. it's unstable and not being developed anymore
#ifdef _WIN32
	#include <Windows.h>
#endif

#include <cmath>
#include <chrono>
#include <thread>
#include <stdio.h>

class hackerPrint {
private:
	#ifdef _WIN32
		static inline void gotoxy(int x, int y) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
		}
	#else
		static inline void gotoxy(int x,int y) {
			printf("%c[%d;%df",0x1B,y,x);
		}
	#endif

public:
	static void print(int x, int y, std::string text, int sleepInterval = 1, int textCompleteness = 2) {
		std::string writtenText = "";
		for (int i = 5; i < text.length()*2; i++) { // i use 5 because at 0 the text is just like normal and changes only at a higher number
			writtenText = "";
			for (int j = 0; j < text.length(); j++) {
				hackerPrint::gotoxy(x + j, y);
				writtenText += text[j] + j / ((i ^ j) + textCompleteness);
				printf("%c", text[j] + j / ((i ^ j) + textCompleteness));
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepInterval));
			}
			if (writtenText == text)
				return;
		}
	}
};
#endif