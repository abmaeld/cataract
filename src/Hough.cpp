
#include "../include/Hough.hpp"

void Scan(Image *Img, unsigned char ***Hough_Space, unsigned short X_INIT, unsigned short X_FINAL, unsigned short Y_INIT, unsigned short Y_FINAL, unsigned short Minimum, unsigned short Maximum) {

	for (unsigned short i = Y_INIT; i < Y_FINAL; i++) {

		for (unsigned short j = X_INIT; j < X_FINAL; j++) {

			if (Img->Matrix[i][j].Red == 255) {

				for (unsigned int k = Minimum; k < Maximum; k++) {

					for (unsigned int l = 0; l < 360; l++) {
			 
						unsigned short x = j - k * std::sin(l * PI / 180);

						unsigned short y = i - k * std::cos(l * PI / 180);

						if (y >= Minimum && y < Img->Height - Minimum) {

							if (x >= Minimum && x < Img->Width - Minimum) {

								Hough_Space[y-Minimum][x-Minimum][k-Minimum]++;			

							}

						}

					}

				}

			}

		}

	}

}

Circumference Hough(Image *Img) {

	unsigned short Minimum, Maximum;

	if (Img->Width > Img->Height) {

		Maximum = Img->Height / 2;

	}

	else {

		Maximum = Img->Width / 2;

	}

	Minimum = Maximum / 5;

	unsigned char ***Hough_Space;

	unsigned short Hough_Height = Img->Height - 2 * Minimum, Hough_Width = Img->Width - 2 * Minimum;
		
	Hough_Space = new unsigned char**[Hough_Height];

	for (int i = 0; i < Hough_Height; i++) {
						
		Hough_Space[i] = new unsigned char*[Hough_Width];

		for (int j = 0; j < Hough_Width; j++) {

			Hough_Space[i][j] = new unsigned char[Maximum-Minimum];

		}

	}

	unsigned short OFFSET = 2;

	if (Offset != 0) {

		OFFSET = Offset;

	}

	unsigned short Y_INIT = OFFSET, Y_FINAL = Img->Height - OFFSET;
	unsigned short X_INIT = OFFSET, X_FINAL = Img->Width  - OFFSET;
	
	if (Threads) {

		std::thread THREAD1(Scan, Img, Hough_Space, OFFSET, Img->Width / 2, OFFSET, Img->Height / 2, Minimum, Maximum);
		std::thread THREAD2(Scan, Img, Hough_Space, Img->Width / 2, Img->Width - OFFSET, OFFSET, Img->Height / 2, Minimum, Maximum);
		std::thread THREAD3(Scan, Img, Hough_Space, OFFSET, Img->Width / 2, Img->Height / 2, Img->Height - OFFSET, Minimum, Maximum);
		std::thread THREAD4(Scan, Img, Hough_Space, Img->Width / 2, Img->Width - OFFSET, Img->Height / 2, Img->Height - OFFSET, Minimum, Maximum);

		THREAD1.join();
		THREAD2.join();
		THREAD3.join();
		THREAD4.join();
		
	}

	else {

		Scan(Img, Hough_Space, X_INIT, X_FINAL, Y_INIT, Y_FINAL, Minimum, Maximum);

	}

	unsigned short x = 0, y = 0, r = 0, Center = 0;

	for (unsigned short i = 2; i < Hough_Height - 2; i++) {

		for (unsigned short j = 2; j < Hough_Width - 2; j++) {

			for (short k = 0; k < Maximum - Minimum; k++) {

				if (Hough_Space[i][j][k] > Center) {

					Center = Hough_Space[i][j][k];

					y = i + Minimum; x = j + Minimum; r = k + Minimum;

				}

			}

		}

	}

	return Circumference(x, y, r);

}
