#pragma once
#include "olcPixelGameEngine.h"

/*
	olcPGEX_Shaders2D.h

	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension            |
	|                 Advanced 2D Screen Shaders                  |
	+-------------------------------------------------------------+

	What the heck this?
	~~~~~~~~~~~~~~~~~~~
	This is an extension to the olcPixelGameEngine, which provides
	advanced 2D screen shaders. To use it you have to follow theese
	simple steps:
	1.	include the header file
	2.	add "SetPixelMode(olc::Pixel::Mode::ALPHA);" to the OnUserCreate()
		function of your game class
		-----OPTIONAL-----
	3.	include <time.h>
	4.	add "srand(time(NULL));" to the OnUserCreate() function of
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
	Discord:		https://discord.gg/9PmAkQR
	GitHub:			https://github.com/Gecero
	Homepage:		http://youtube.alpmann.de

	Author
	~~~~~~
	Gecero Non-Copyright 2018
*/

namespace olc {
	namespace Shaders2D {
		// This is a simple shader that blurs the whole screen
		olc::rcode Blur(olc::PixelGameEngine * pge) {
			try {
				int rSum;
				int gSum;
				int bSum;
				for (int x = 0; x < pge->ScreenWidth(); x++) {
					for (int y = 0; y < pge->ScreenHeight(); y++) {
						rSum = 0;
						gSum = 0;
						bSum = 0;
						for (int j = -1; j < 2; j++) {
							for (int k = -1; k < 2; k++) {
								rSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).r;
								gSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).g;
								bSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).b;
							}
						}
						pge->Draw(x, y, olc::Pixel(rSum / 9, gSum / 9, bSum / 9));
					}
				}

			}
			catch (std::exception e) { return olc::rcode::FAIL; }
			return olc::rcode::OK;

		}

		// This is a simple shader that inverts the color of the screen
		olc::rcode Invert(olc::PixelGameEngine * pge) {
			try {
				for (int x = 0; x < pge->ScreenWidth(); x++) {
					for (int y = 0; y < pge->ScreenHeight(); y++) {
						int r = 255 - pge->GetDrawTarget()->GetPixel(x, y).r;
						int g = 255 - pge->GetDrawTarget()->GetPixel(x, y).g;
						int b = 255 - pge->GetDrawTarget()->GetPixel(x, y).b;

						pge->Draw(x, y, olc::Pixel(r, g, b));
					}
				}

			}
			catch (std::exception e) { return olc::rcode::FAIL; }
			return olc::rcode::OK;

		}
		
		// This is a simple shader that converts the screen into monochrome
		olc::rcode Monochromize(olc::PixelGameEngine * pge) {
			try {
				for (int x = 0; x < pge->ScreenWidth(); x++) {
					for (int y = 0; y < pge->ScreenHeight(); y++) {
						int colour = (float)(pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3;
						pge->Draw(x, y, olc::Pixel(colour, colour, colour));
					}
				}

			}
			catch (std::exception e) { return olc::rcode::FAIL; }
			return olc::rcode::OK;

		}
		
		// This is a shader that does some stereotypicial 50's TV distortions and a sepia effect
		olc::rcode Vintageize(olc::PixelGameEngine * pge) {
			try {
				int r;
				int g;
				int b;
				int newR;
				int newG;
				int newB;
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

				if (rand() > pow(RAND_MAX, 0.9921875)) {
					int linePos = rand() % pge->ScreenWidth();
					pge->DrawLine(linePos, 0, linePos, pge->ScreenHeight(), olc::Pixel(192, 192, 192, 96));
				}

				for (int i = 0; i < pow(pge->ScreenWidth()+pge->ScreenHeight(), 0.5); i++) {
					if (rand() > pow(RAND_MAX, 0.9875))
						pge->Draw(rand() % pge->ScreenWidth(), rand() % pge->ScreenHeight(), olc::Pixel(192, 192, 192, 64));
				}

			}
			catch (std::exception e) { return olc::rcode::FAIL; }
			return olc::rcode::OK;

		}
		
	}
}
