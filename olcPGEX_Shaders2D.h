#pragma once
#ifndef OLC_PGE_APPLICATION
	#define OLC_PGE_APPLICATION
	#include "olcPixelGameEngine.h"
#endif

namespace olc {
	class Shaders2D {
	private:
		long long queue = 0;

	public:
		Shaders2D() {

		}

		enum shader {
			BLUR = 1,
			INVERT = 2,
			MONOCHROMIZE = 4,
		};

		void addToQueue(int shader) {
			queue |= shader;
		}

		void clearQueue(int shader) {
			queue = 0;
		}

		olc::rcode render(olc::PixelGameEngine * pge) {
			try {
				for (int x = 0; x < pge->ScreenWidth(); x++) {
					for (int y = 0; y < pge->ScreenHeight(); y++) {
						// // // // // BLUR // // // // //
						if (queue & BLUR) {
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
						// // // // // INVERT // // // // //
						if (queue & INVERT) {
							pge->Draw(x, y, olc::Pixel(255 - pge->GetDrawTarget()->GetPixel(x, y).r, 255 - pge->GetDrawTarget()->GetPixel(x, y).g, 255 - pge->GetDrawTarget()->GetPixel(x, y).b));
						}
						// // // // // MONOCHROMIZE // // // // //
						if (queue & MONOCHROMIZE) {
							pge->Draw(x, y, olc::Pixel(((float)(pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3.0), ((float)(pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3.0), ((float)(pge->GetDrawTarget()->GetPixel(x, y).r + pge->GetDrawTarget()->GetPixel(x, y).g + pge->GetDrawTarget()->GetPixel(x, y).b) / 3.0)));
						}

					}
				}
			} catch (std::exception e) { queue = 0; return olc::rcode::FAIL; }
			queue = 0;
			return olc::rcode::OK;
		}

	};
}
