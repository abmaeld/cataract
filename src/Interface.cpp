
#include "../include/Interface.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

std::string shellclearconsole = "cls";

#else

std::string shellclearconsole = "clear";

#endif

void Clear() {

	if (system(shellclearconsole.c_str()) != 0) {

		std::cout << std::endl << "Could not clear console." << std::endl;

	}
	
}

void Init() {

	Clear();

	std::cout << std::endl << "Cataract Diagnosis using Image Processing." << std::endl;

}

void Terminate() {

	std::cout << std::endl;
	
}