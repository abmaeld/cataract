
#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <iostream>
#include <cmath>
#include <string>
#include "../include/Image.hpp"
#include "../include/Processing.hpp"
#include "../include/Hough.hpp"

float Analyze(Image *Img, Circumference Pupil);
float Process(Image *Img);
std::string Diagnose(Image *Img);

#endif

