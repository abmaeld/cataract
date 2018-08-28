
#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <chrono>
#include "../include/Image.hpp"
#include "../include/Analysis.hpp"
#include "../include/Interface.hpp"

std::vector<std::string> Paths;
std::vector<Image*> Images;

unsigned short Offset = 0;
bool Threads =  true;

#endif
