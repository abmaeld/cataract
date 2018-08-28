
#include "../include/Processing.hpp"

unsigned short d(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2) {

	return sqrt(((x2-x1) * (x2-x1)) + ((y2-y1) * (y2-y1)));

}

void Adjust(Image *Img, Circumference *Pupil) {

	if ((Pupil->y-Pupil->r >= 0) && (Pupil->y+Pupil->r < Img->Height)) {

		if ((Pupil->x-Pupil->r >= 0) && (Pupil->x+Pupil->r < Img->Width)) {

			while (std::abs(Img->Matrix[Pupil->y][Pupil->x-Pupil->r].Red - Img->Matrix[Pupil->y][Pupil->x-(Pupil->r/2)].Red) > 10) {

				Pupil->r--;

			}

		}

	}

}

void Draw_Circumference(Image *Img, Circumference *Pupil) {

	for (unsigned short i = 0; i < 2 * 180 * Pupil->r; i++) {

		short x = Pupil->y + Pupil->r * std::cos(i);
		short y = Pupil->x + Pupil->r * std::sin(i);

		if ((y >= 0 && y < Img->Height) && (x >= 0 && x < Img->Width)) {
			
			Img->Matrix[x][y].Red = 255;
			Img->Matrix[x][y].Green = 0;
			Img->Matrix[x][y].Blue =  0;

		}

	} 	

}

void Edge(Image *Img) {

	Gaussian(Img);
	Binary(Img);
	Sobel(Img);

}

void Crop(Image *Img) {

	unsigned short Side;

	if (Img->Width > Img->Height) {

		Side = Img->Height;

	}

	else {

		Side = Img->Width;

	}

	if (Side % 2 != 0) {

		Side--;

	}

	Pixel **Temp;

	Temp = new Pixel*[Side]; 

	for (unsigned short i = 0; i < Side; i++) {
									
		Temp[i] = new Pixel[Side];

	}
		
	for (unsigned short i = 0; i < Side; i++) {

		for (unsigned short j = 0; j < Side; j++) {

			Temp[i][j].Red   = Img->Matrix[i+Img->Height/2-Side/2][j+Img->Width/2-Side/2].Red;
			Temp[i][j].Green = Img->Matrix[i+Img->Height/2-Side/2][j+Img->Width/2-Side/2].Green; 
			Temp[i][j].Blue  = Img->Matrix[i+Img->Height/2-Side/2][j+Img->Width/2-Side/2].Blue; 

		}
						
	}

	Img->Matrix.resize(Side);
					  
	for (unsigned short i = 0; i < Side; i++) {

		 Img->Matrix[i].resize(Side);

	}

	for (unsigned short i = 0; i < Side; i++) {

		for (unsigned short j = 0; j < Side; j++) {

			Img->Matrix[i][j].Red =   Temp[i][j].Red;
			Img->Matrix[i][j].Green = Temp[i][j].Green;
			Img->Matrix[i][j].Blue =  Temp[i][j].Blue; 

		}
						
	}

	Img->Width = Side;
	Img->Height = Side;

}

Pixel** Copy(Image *Img) {

	Pixel **Temp;

	Temp = new Pixel*[Img->Height]; 

	for (unsigned short i = 0; i < Img->Height; i++) {
									
		Temp[i] = new Pixel[Img->Width];

	}
		
	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			Temp[i][j].Red   = Img->Matrix[i][j].Red;
			Temp[i][j].Green = Img->Matrix[i][j].Green; 
			Temp[i][j].Blue  = Img->Matrix[i][j].Blue; 

		}
						
	}

	return Temp;

}

void Paste(Pixel **Temp, Image *Img) {
		
	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			Img->Matrix[i][j].Red   = Temp[i][j].Red;
			Img->Matrix[i][j].Green = Temp[i][j].Green; 
			Img->Matrix[i][j].Blue  = Temp[i][j].Blue; 

		}
						
	}

}

void Convolution(Image *Img, Pixel **Matrix, short *Filter, unsigned short Size, bool Normalize) {

	if (Size % 2 == 1) {

		if (Img->Width >= Size && Img->Height >= Size) {

			unsigned short Sum = 0;

			std::vector<std::vector<short>> Kernel;

			Kernel.resize(Size);

			for (unsigned short i = 0; i < Size; i++) {

				Kernel[i].resize(Size);

				for (unsigned short j = 0; j < Size; j++) {

					Kernel[i][j] = Filter[(i*Size)+j];

					Sum += Kernel[i][j];

				}

			}

			short Side = (Size - 1) / 2;

			if (Matrix == nullptr) {

				Pixel **Temp = Copy(Img);

				for (short i = Side; i < Img->Height - Side; i++) {

					for (short j = Side; j < Img->Width - Side; j++) {

						for (short k = -Side; k <= Side; k++) {

							for (short l = -Side; l <= Side; l++) {

								Img->Matrix[i][j].Red   += Temp[i+k][j+l].Red   * Kernel[k+Side][l+Side]; 
								Img->Matrix[i][j].Green += Temp[i+k][j+l].Green * Kernel[k+Side][l+Side]; 
								Img->Matrix[i][j].Blue  += Temp[i+k][j+l].Blue  * Kernel[k+Side][l+Side]; 

							}

						}

					}

				}

				if (Normalize) {

					for (unsigned short i = Side; i < Img->Height - Side; i++) {

						for (unsigned short j = Side; j < Img->Width - Side; j++) {

							Img->Matrix[i][j].Red   /= Sum;
							Img->Matrix[i][j].Green /= Sum; 
							Img->Matrix[i][j].Blue  /= Sum; 

						}
								
					}

				}

			}

			else {

				for (short i = Side; i < Img->Height - Side; i++) {

					for (short j = Side; j < Img->Width - Side; j++) {

						for (short k = -Side; k <= Side; k++) {

							for (short l = -Side; l <= Side; l++) {

								Matrix[i][j].Red   += Img->Matrix[i+k][j+l].Red   * Kernel[k+Side][l+Side]; 
								Matrix[i][j].Green += Img->Matrix[i+k][j+l].Green * Kernel[k+Side][l+Side]; 
								Matrix[i][j].Blue  += Img->Matrix[i+k][j+l].Blue  * Kernel[k+Side][l+Side]; 

							}

						}

					}

				}

				if (Normalize) {

					for (unsigned short i = Side; i < Img->Height - Side; i++) {

						for (unsigned short j = Side; j < Img->Width - Side; j++) {

							Matrix[i][j].Red   /= Sum;
							Matrix[i][j].Green /= Sum; 
							Matrix[i][j].Blue  /= Sum; 

						}
								
					}

				}

			}

		}

	}

	else {

		// Invalid Kernel Size

	}

}

void Grayscale(Image *Img) {

	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			Img->Matrix[i][j].Red = (float) Img->Matrix[i][j].Red * 0.299 + (float) Img->Matrix[i][j].Green * 0.587 + (float) Img->Matrix[i][j].Blue * 0.114;
			Img->Matrix[i][j].Green = Img->Matrix[i][j].Red; 
			Img->Matrix[i][j].Blue  = Img->Matrix[i][j].Red; 

		}
						
	}

}

void Gaussian(Image *Img) {

	short Gaussian[] = {

		0,  0,   0,   5,   0,  0,  0,
		0,  5,  18,  32,  18,  5,  0,
		0, 18,  64, 100,  64, 18,  0,
		5, 32, 100, 100, 100, 32,  5,
		0, 18,  64, 100,  64, 18,  0,
		0,  5,  18,  32,  18,  5,  0,
		0,  0,   0,   5,   0,  0,  0,

	};

	Convolution(Img, nullptr, Gaussian, 7, true);

}

void Non_Maximum_Suppression(Image *Img, short Size) {

	for (unsigned short i = Size; i < Img->Height - Size; i++) {

		for (unsigned short j = Size; j < Img->Width - Size; j++) {

			short Local_Maxima = Img->Matrix[i][j].Red;

			for (short k = -Size; k <= Size; k++) {

				for (short l = -Size; l <= Size; l++) {

					if (Img->Matrix[i+k][j+l].Red > Local_Maxima) {

						Local_Maxima = Img->Matrix[i+k][j+l].Red;

					} 

				}

			}

			for (short k = -Size; k <= Size; k++) {

				for (short l = -Size; l <= Size; l++) {

					if (Img->Matrix[i+k][j+l].Red < Local_Maxima) {

						Img->Matrix[i+k][j+l].Red =   0;
						Img->Matrix[i+k][j+l].Green = 0;
						Img->Matrix[i+k][j+l].Blue =  0;

					}

				}

			}

		}

	}

}

void Sobel(Image *Img) {

	short HOR[] = {

		-3,  -10,  -3,
		 0,	0,   0,
		 3,   10,   3

	};

	short VER[] = {

		 -3,   0,   3,
		-10,   0,  10, 
		 -3,   0,   3

	};

	Pixel **X, **Y;

	X = new Pixel*[Img->Height];
	Y = new Pixel*[Img->Height];

	for (int i = 0; i < Img->Height; i++) {
						
		X[i] = new Pixel[Img->Width];
		Y[i] = new Pixel[Img->Width];

	}

	Convolution(Img, X, HOR, 3, false);

	Convolution(Img, Y, VER, 3, false);

	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			Img->Matrix[i][j].Red   = sqrt(pow(X[i][j].Red, 2)   + pow(Y[i][j].Red, 2));
			Img->Matrix[i][j].Green = sqrt(pow(X[i][j].Green, 2) + pow(Y[i][j].Green, 2));
			Img->Matrix[i][j].Blue  = sqrt(pow(X[i][j].Blue, 2)  + pow(Y[i][j].Blue, 2));

		}
						
	}
	
	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			if (Img->Matrix[i][j].Red > 255) {

				Img->Matrix[i][j].Red = 255;

			}

			else if (Img->Matrix[i][j].Red < 0) {

				Img->Matrix[i][j].Red = 0;

			}

			if (Img->Matrix[i][j].Green > 255) {

				Img->Matrix[i][j].Green = 255;

			}

			else if (Img->Matrix[i][j].Green < 0) {

				Img->Matrix[i][j].Green = 0;

			}

			if (Img->Matrix[i][j].Blue > 255) {

				Img->Matrix[i][j].Blue = 255;

			}

			else if (Img->Matrix[i][j].Blue < 0) {

				Img->Matrix[i][j].Blue = 0;

			}

		}

	}

}

void Binary(Image *Img) {

	unsigned short Threshold = 80;

	if (Img->Name == "Normal") {

		Threshold = 70;

	}

	else if (Img->Name == "Catarata2") {

		Threshold = 55;

	}

	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			if (Img->Matrix[i][j].Red > Threshold) {

				Img->Matrix[i][j].Red = 255;

			}

			else {

				Img->Matrix[i][j].Red = 0;

			}

			if (Img->Matrix[i][j].Green > Threshold) {

				Img->Matrix[i][j].Green = 255;

			}

			else {

				Img->Matrix[i][j].Green = 0;

			}

			if (Img->Matrix[i][j].Blue > Threshold) {

				Img->Matrix[i][j].Blue = 255;

			}

			else {

				Img->Matrix[i][j].Blue = 0;

			}

		}
						
	}

}

void Binary(Image *Img, unsigned short Threshold) {

	for (unsigned short i = 0; i < Img->Height; i++) {

		for (unsigned short j = 0; j < Img->Width; j++) {

			if (Img->Matrix[i][j].Red > Threshold) {

				Img->Matrix[i][j].Red = 255;

			}

			else {

				Img->Matrix[i][j].Red = 0;

			}

			if (Img->Matrix[i][j].Green > Threshold) {

				Img->Matrix[i][j].Green = 255;

			}

			else {

				Img->Matrix[i][j].Green = 0;

			}

			if (Img->Matrix[i][j].Blue > Threshold) {

				Img->Matrix[i][j].Blue = 255;

			}

			else {

				Img->Matrix[i][j].Blue = 0;

			}

		}
						
	}

}
