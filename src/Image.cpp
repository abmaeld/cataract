
#include "../include/Image.hpp"

std::string File::Path() {

	return Directory + Name + Type;

}

std::string File::Untyped_Path() {

	return Directory + Name;

}

Image::Image(std::string str) {

	Directory = str.substr(0, str.find_last_of('/') + 1);
	Name = str.substr(str.find_last_of('/') + 1, str.find_last_of('.') - str.find_last_of('/') - 1);
	Type = str.substr(str.find_last_of('.'));
	Read = read();

}

Image::~Image() {


}

bool Image::read() {

	std::cout << std::endl << "  " << Name + Type << " :" << std::endl;

	if (!Path().empty()) {

		if (Type == ".ppm") {

			std::ifstream File(Path());

			if (File.is_open()) {

				std::string str_temp;
				char char_temp;

				std::getline(File, str_temp);

				if (str_temp == "P3" || str_temp == "p3") {

					File.get(char_temp);

					while (char_temp == '#') {

						File.get(char_temp);

						std::getline(File, str_temp);

						Comments.push_back(str_temp);

						File.get(char_temp);

					}

					File.unget();

					File >> Width >> Height >> Rgb;
					
					Matrix.resize(Height);
					  
					for (unsigned short i = 0; i < Height; i++) {

						Matrix[i].resize(Width);

					}

					float Factor = (float) 255 / Rgb;

					unsigned short Temp[3];
					
					for (unsigned short i = 0; i < Height; i++) {

						for (unsigned short j = 0; j < Width; j++) {

							File >> Temp[0] >> Temp[1] >> Temp[2];

							Matrix[i][j].Red   =  (float) Temp[0] * Factor;
							Matrix[i][j].Green =  (float) Temp[1] * Factor;
							Matrix[i][j].Blue  =  (float) Temp[2] * Factor;

						}

					}

					Rgb = 255;

					File.close();

					return true;

				}

				else {

					return false;

				}

			}

			else {
				
				return false;

			}

		}

		else {

			return false;

		}

	}

	else {

		return false;

	}

}

void write(Pixel **Matrix, std::string Dir, std::string Name, unsigned short Width, unsigned short Height, unsigned short Rgb) {

	std::string Path = Dir + Name + ".ppm";

	std::ofstream File(Path);

	if (File.is_open()) {

		File << "P3" << std::endl;

		File << Width << ' ' << Height << ' ' << Rgb << std::endl;

		for (unsigned short i = 0; i < Height; i++) {

			for (unsigned short j = 0; j < Width; j++) {

				File << Matrix[i][j].Red << ' ' << Matrix[i][j].Green << ' ' << Matrix[i][j].Blue << ' ';

			}

			File << std::endl;
						
		}

		File.close();

	}

}

void write(Image *Img, std::string Dir, std::string Name, bool Comments) {

	std::string Path = Dir + Name + ".ppm";

	std::ofstream File(Path);

	if (File.is_open()) {

		File << "P3" << std::endl;

		if (Comments) {

			File << "# " << Img->Name << std::endl;

			for (unsigned short i = 0; i < Img->Comments.size(); i++) {

				File << "# " << Img->Comments[i] << std::endl;

			}

		}

		File << Img->Width << ' ' << Img->Height << ' ' << Img->Rgb << std::endl;

		for (unsigned short i = 0; i < Img->Height; i++) {

			for (unsigned short j = 0; j < Img->Width; j++) {

				File << Img->Matrix[i][j].Red << ' ' << Img->Matrix[i][j].Green << ' ' << Img->Matrix[i][j].Blue << ' ';

			}

			File << std::endl;
						
		}

		File.close();

	}

}

Circumference::Circumference(unsigned short X, unsigned short Y, unsigned short R) {

	x = X;
	y = Y;
	r = R;

}

Circumference::~Circumference() {


}
