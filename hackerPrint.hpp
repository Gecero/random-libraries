#ifndef HACKERPRINT_HPP
#define HACKERPRINT_HPP
#ifdef _WIN32
	#include <Windows.h>
#else
	#include<stdio.h>
#endif

#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

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
		const char * txt = text.c_str();
		std::string writtenText = "";
		for (int i = 0; i < pow(sizeof(text), 2); i++) {
			writtenText = "";
			for (int j = 0; j < text.length(); j++) {
				gotoxy(x + j, y);
				writtenText += (char)(txt[j] + j / ((i ^ j) + textCompleteness));
				std::cout << (char)(txt[j] + j / ((i ^ j) + textCompleteness));
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepInterval));
			}
			if (writtenText == text && i > 5) // > 5 because at the start the text is just like the normal text and gets over the time changed
				return;
		}
	}
};
#endif
