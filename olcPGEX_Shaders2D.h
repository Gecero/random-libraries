#pragma once
#include "olcPixelGameEngine.h"

namespace olc {
	class Shaders2D {
	public:
		Shaders2D() {

		}

		void Blur(olc::PixelGameEngine * pge) {
			for (int x = 0; x < pge->ScreenWidth(); x++) {
				for (int y = 0; y < pge->ScreenHeight(); y++) {
					int rSum = 0;
					int gSum = 0;
					int bSum = 0;
					for (int j = -1; j < 2; j++) {
						for (int k = -1; k < 2; k++) {
							rSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).r;
							gSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).g;
							bSum += pge->GetDrawTarget()->GetPixel(x + j, y + k).b;
						}
					}
					pge->Draw(x, y, olc::Pixel(rSum / 9.0, gSum / 9.0, bSum / 9.0));

				}
			}
		}

		void Invert(olc::PixelGameEngine * pge) {
			for (int x = 0; x < pge->ScreenWidth(); x++) {
				for (int y = 0; y < pge->ScreenHeight(); y++) {
					int r = 255 - pge->GetDrawTarget()->GetPixel(x, y).r;
					int g = 255 - pge->GetDrawTarget()->GetPixel(x, y).g;
					int b = 255 - pge->GetDrawTarget()->GetPixel(x, y).b;

					pge->Draw(x, y, olc::Pixel(r, g, b));
				}
			}
		}

		void Blackandwhiteinator(olc::PixelGameEngine * pge) {
			for (int x = 0; x < pge->ScreenWidth(); x++) {
				for (int y = 0; y < pge->ScreenHeight(); y++) {
					int colour = (float)(pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3.0;
					pge->Draw(x, y, olc::Pixel(colour, colour, colour));
				}
			}
		}


	};
}
