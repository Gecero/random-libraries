#ifndef GUCGL_HPP
#define GUCGL_HPP
// GUCGL = gecero's universal console graphics library
#include <iostream> // for render()
#include <chrono> // for render time calculating
#include <string> // for std::to_string() in showFps()

class gucglInstance {
private:
	std::string * screen;
	int screenWidth;
	int screenHeight;
	bool firstRender; // to prevent the cursor at first render moving the cursor up
	std::chrono::high_resolution_clock::time_point timeSync1; // we define them now that we dont have to initalize them
	std::chrono::high_resolution_clock::time_point timeSync2; // when we use them because thats not very efficent

public:
	// MAIN FUNCTIONS //



	gucglInstance() { }
	~gucglInstance() { }

	static gucglInstance & getInstance() {
		static gucglInstance * instance = NULL;
		if (instance != nullptr && instance != NULL)
			return *instance;
		else {
			instance = new gucglInstance();
			return *instance;
		}
	}
	
	static inline void destroyInstance() {
		gucglInstance * tmp = &gucglInstance::getInstance();
		delete tmp;
	}

	// initalizes the whole engine and render functions
	void init(int screenWidth_, int screenHeight_) {
		screenWidth = screenWidth_;
		screenHeight = screenHeight_;
		screen = new std::string[screenHeight];
		firstRender = true;
	}



	// GRAPHIC FUNCTIONS //



	// render the current screen and return the elapsed time in seconds
	float render() {
		// render time "timer start"
		timeSync1 = std::chrono::high_resolution_clock::now();

		// move the cursor back
		if (!firstRender == true) {
			for (int i = 0; i < screenHeight; i++) {
				std::cout << "\b";
				std::cout << "\r";
			}
		}
		else {
			firstRender = false;
		}

		// render screen data
		for (int i = 0; i < screenHeight; i++) {
			std::cout << screen[i] << std::endl;
		}

		// render time "timer stop"
		timeSync2 = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<float>(timeSync2 - timeSync1).count();
	}

	inline int getScreenWidth() { return screenWidth; }
	inline int getScreenHeight() { return screenHeight; }

	// set a char to the screen
	void plot(int x, int y, char char_) {
		if(!(x > screenWidth-1 || x < 0 || y > screenHeight-1 || y < 0))
			screen[y][x] = char_;
	}

	// fill the entire screen with one char
	void fill(char char_) {
		std::string fillStr = "";
		for (int x = 0; x < screenWidth; x++)
			fillStr += " ";
		for (int y = 0; y < screenHeight; y++)
				screen[y] = fillStr;
	}
	
	// show the fps on the screen (no decimal places)
	void showFps(float frameTime, int x = 0, int y = 0) {
		std::string fps = std::to_string(1.0f / frameTime);
		if (fps.size() > 7) { // the string is always at least one int digit, one decimal point and 5 decimal places
			for (int i = 0; i < fps.size() - 7; i++)
				plot(x + i, y, fps[i]);
			plot(x + fps.size() - 7, y, ' ');
			plot(x + fps.size() - 7 + 1, y, 'f');
			plot(x + fps.size() - 7 + 2, y, 'p');
			plot(x + fps.size() - 7 + 3, y, 's');
		}
	}

};
#endif