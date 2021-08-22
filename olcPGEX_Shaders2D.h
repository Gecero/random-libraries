#pragma once
#include "olcPixelGameEngine.h"

/*
	olcPGEX_Shaders2D.h

	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension            |
	|                 Advanced 2D Screen Shaders                  |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	This is an extension to the olcPixelGameEngine, which provides
	advanced 2D screen shaders. To use it you have to follow theese
	simple steps:
	1.	include the header file
	2.	add "SetPixelMode(olc::Pixel::Mode::ALPHA);" to the OnUserCreate()
		function of your game class
	3.	add "myShader.init()" to the OnUserCreate() function of your
		game class
		-----OPTIONAL-----
	4.	include <time.h>
	5.	add "srand(time(NULL));" to the OnUserCreate() function of
		your game class. this will make some of the effects that
		require random values more pseudo-random

	License
	~~~~~~~
	None ;)
	I don't care what you use this for. Just do everything what you
	want to do with it. It can even be commercial! I just want to
	give other coders the opportunity to save code and get a lot of
	efficent and simple to use code. If you want to contribute to
	this library then just write some more shader functions to this
	extension and make a pull request on GitHub.

	Links
	~~~~~
	YouTube:		https://www.youtube.com/channel/UCWVVUuunLpgpoG_HVo2sGxQ
	GitHub:			https://github.com/Gecero
	Homepage:		https://youtube.alpmann.de

	Author
	~~~~~~
	Gecero Non-Copyright 2018
*/

namespace olc {
	// Container class for more or less Advanced 2D Shaders
	class Shaders2D : public olc::PGEX {
	private:
		float VHSShiftPos;
		int VHSShiftSize;
		bool VHSShift = false;
		int VHSRatioChangeWidth;

	public:
		// Initalize all shaders
		inline void init() noexcept;
		// This shader blurs the screen
		olc::rcode Blur();
		// This shader inverts the color of the screen
		olc::rcode Invert();
		// This shader converts the screen into monochrome
		olc::rcode Monochromize();
		// This shader does some stereotypicial 50's TV distortions and a sepia effect
		olc::rcode Vintageize(olc::Pixel distortionColour, bool noise);
		// This shader does some stereotypical 70's VHS distortions and noise
		olc::rcode VHSize(bool noise);
	};
}

inline void olc::Shaders2D::init() noexcept {
	VHSRatioChangeWidth = (4.0f / 3.0f) * (float)pge->ScreenHeight();
}

olc::rcode olc::Shaders2D::Blur() {
	try {
		int rSum, gSum, bSum;

		for (int x = 0; x < pge->ScreenWidth(); x++) {
			for (int y = 0; y < pge->ScreenHeight(); y++) {
				rSum = 0;
				gSum = 0;
				bSum = 0;
				// get the sum of all surrounding pixels
				for (int j = -1; j < 2; j++) {
					for (int k = -1; k < 2; k++) {
						rSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).r;
						gSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).g;
						bSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).b;
					}
				}
				// draw the average of all surroundig pixels
				pge->Draw(x, y, olc::Pixel(rSum / 9, gSum / 9, bSum / 9));
			}
		}
	}
	catch (std::exception e) { return olc::rcode::FAIL; }
	return olc::rcode::OK;
}

olc::rcode olc::Shaders2D::Invert() {
	try {
		int r, g, b;

		for (int x = 0; x < pge->ScreenWidth(); x++) {
			for (int y = 0; y < pge->ScreenHeight(); y++) {
				// invert the r, g and b colours
				r = 255 - pge->GetDrawTarget()->GetPixel(x, y).r;
				g = 255 - pge->GetDrawTarget()->GetPixel(x, y).g;
				b = 255 - pge->GetDrawTarget()->GetPixel(x, y).b;

				pge->Draw(x, y, olc::Pixel(r, g, b));
			}
		}
	}
	catch (std::exception e) { return olc::rcode::FAIL; }
	return olc::rcode::OK;
}

olc::rcode olc::Shaders2D::Monochromize() {
	try {
		int colour;

		for (int x = 0; x < pge->ScreenWidth(); x++) {
			for (int y = 0; y < pge->ScreenHeight(); y++) {
				// get the average of the r, g and b colour and draw it
				colour = (pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3;
				pge->Draw(x, y, olc::Pixel(colour, colour, colour));
			}
		}
	}
	catch (std::exception e) { return olc::rcode::FAIL; }
	return olc::rcode::OK;

}

olc::rcode olc::Shaders2D::Vintageize(olc::Pixel distortionColour = olc::Pixel(192, 192, 192, 96), bool noise = true) {
	try {
		int r, g, b, newR, newG, newB;

		// add a sepia effect
		for (int x = 0; x < pge->ScreenWidth(); x++) {
			for (int y = 0; y < pge->ScreenHeight(); y++) {
				r = pge->GetDrawTarget()->GetPixel(x, y).r;
				g = pge->GetDrawTarget()->GetPixel(x, y).g;
				b = pge->GetDrawTarget()->GetPixel(x, y).b;
				newR = fmin((0.393*r) + (0.769*g) + (0.189*b), 255);
				newG = fmin((0.349*r) + (0.686*g) + (0.168*b), 255);
				newB = fmin((0.272*r) + (0.534*g) + (0.131*b), 255);
				pge->Draw(x, y, olc::Pixel(newR, newG, newB));
			}
		}

		// add some random distortion lines
		if (rand() > pow(RAND_MAX, 0.9921875)) {
			int linePos = rand() % pge->ScreenWidth();
			pge->DrawLine(linePos, 0, linePos, pge->ScreenHeight(), distortionColour);
		}

		// add some random noise
		if (noise == true) {
			for (int i = 0; i < pow(pge->ScreenWidth() + pge->ScreenHeight(), 0.5); i++) {
				if (rand() > pow(RAND_MAX, 0.9875))
					pge->Draw(rand() % pge->ScreenWidth(), rand() % pge->ScreenHeight(), distortionColour);
			}
		}
	}
	catch (std::exception e) { return olc::rcode::FAIL; }
	return olc::rcode::OK;
}

olc::rcode olc::Shaders2D::VHSize(bool noise = true) {
	try {
		// add a block shift distortion effect
		if (VHSShift == false && rand() % (int)pow(pge->ScreenWidth()*pge->ScreenHeight(), 0.7) == 0) {
			VHSShiftPos = 0.0;
			VHSShiftSize = rand() % (pge->ScreenHeight() / 10);
			VHSShift = true;
		} else if (VHSShift == true) {
			VHSShiftPos += (double)rand() / (double)RAND_MAX * pow(pge->ScreenWidth()*pge->ScreenHeight(), 0.0175);
			if (VHSShiftPos >= pge->ScreenHeight())
				VHSShift = false;

			for (int x = 0; x < pge->ScreenWidth(); x++) {
				pge->DrawLine(x, VHSShiftPos, x, VHSShiftPos + VHSShiftSize, pge->GetDrawTarget()->GetPixel(x, VHSShiftPos));
			}
		}

		// add some random distortion lines
		int distortionLinePos = rand() % 100 > 90 ? rand() % pge->ScreenHeight() : INT_MAX;
		for (int x = 0; x < pge->ScreenWidth(); x++)
			if (rand() % 50 < 49)
				pge->Draw(x, distortionLinePos, olc::Pixel(192, 192, 192, 64));

		if (noise == true) {
			int r, g, b, avg, newR, newG, newB;

			for (int x = 0; x < pge->ScreenWidth(); x++) {
				for (int y = 0; y < pge->ScreenHeight(); y++) {
					avg = (r + g + b) / 3;
					r = pge->GetDrawTarget()->GetPixel(x, y).r;
					g = pge->GetDrawTarget()->GetPixel(x, y).g;
					b = pge->GetDrawTarget()->GetPixel(x, y).b;
					// add some noise - if black then only a bit if not black then do more
					newR = fmin(r + (r == 0 ? rand() % 4 : rand() % 16), 255);
					newG = fmin(g + (g == 0 ? rand() % 4 : rand() % 16), 255);
					newB = fmin(b + (b == 0 ? rand() % 4 : rand() % 16), 255);
					// median"-ize" the colors - this creates a blur effect
					newR = fmin((newR + avg + r) / 3, 255);
					newG = fmin((newG + avg + g) / 3, 255);
					newB = fmin((newB + avg + b) / 3, 255);

					pge->Draw(x, y, olc::Pixel(newR, newG, newB));
				}
			}
		}

		// black out everything that isn't inside a 4:3 ratio
		pge->FillRect(0, 0, (pge->ScreenWidth() - VHSRatioChangeWidth) / 2 , pge->ScreenHeight(), olc::BLACK);
		pge->FillRect(pge->ScreenWidth()-((pge->ScreenWidth() - VHSRatioChangeWidth) / 2), 0, pge->ScreenWidth(), pge->ScreenHeight(), olc::BLACK);
	}
	catch (std::exception e) { return olc::rcode::FAIL; }
	return olc::rcode::OK;
}
