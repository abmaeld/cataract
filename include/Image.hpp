
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Pixel {

	public:

		int Red, Green, Blue;

};

class File {

	public:	

		std::string Path();
		std::string Untyped_Path();
		
		std::string Directory, Name, Type;
		bool Read;

};

class Image : public File {

	public:

		 Image(std::string str);
		~Image(); 
		
		bool read();

		std::vector<std::string> Comments;
		unsigned short Width, Height, Rgb;
		std::vector<std::vector<Pixel>> Matrix;

};

void write(Pixel **Matrix, std::string Dir, std::string Name, unsigned short Width, unsigned short Height, unsigned short Rgb);
void write(Image *Img, std::string Dir, std::string Name, bool Comments);

class Circumference {

	public:

		 Circumference(unsigned short X, unsigned short Y, unsigned short R);
		~Circumference();
			
		unsigned short x, y, r;

};

#endif
