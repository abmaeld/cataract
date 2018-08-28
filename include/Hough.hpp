
#ifndef HOUGH_HPP
#define HOUGH_HPP

#include <thread>
#include <cmath>
#include "../include/Image.hpp"
#include "../include/Processing.hpp"
#define PI 3.1415926

extern unsigned short Offset;
extern bool Threads;

void Scan(Image *Img, unsigned char ***Hough_Space, unsigned short INIT_X, unsigned short FINAL_X, unsigned short INIT_Y, unsigned short FINAL_Y, unsigned short Minimum, unsigned short Maximum);
Circumference Hough(Image *Img);

#endif