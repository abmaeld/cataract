
#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <vector>
#include <cmath>
#include "../include/Image.hpp"

unsigned short d(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
void Adjust(Image *Img, Circumference *Pupil);
void Draw_Circumference(Image *Img, Circumference *Pupil);

Pixel** Copy(Image *Img);
void Paste(Pixel **Temp, Image *Img);
void Deallocate(Pixel **Temp, unsigned short Height);
void Convolution(Image *Img, Pixel **Matrix, short *Kernel, unsigned short Size, bool Normalize);
void Crop(Image *Img);

void Edge(Image *Img);

void Grayscale(Image *Img);
void Gaussian(Image *Img);
void Sobel(Image *Img);

void Non_Maximum_Suppression(Image *Img, short Size);
void Binary(Image *Img);
void Binary(Image *Img, unsigned short Threshold);

#endif
