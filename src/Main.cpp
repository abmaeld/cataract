
#include "../include/Main.hpp"

int main(int argc, char *argv[]) {

	Init();

	auto start = std::chrono::high_resolution_clock::now();

	for (unsigned short i = 1; i < argc; i++) {

		if (i < argc) {

			if (std::strcmp(argv[i], "-i") == 0) {

				unsigned short j = 0;

				while ((argv[(i+1)+j] != nullptr && argv[(i+1)+j][0] != '\0') && argv[(i+1)+j][0] != '-')  {

					Paths.push_back(argv[(i+1)+j]); j++;

				}

			}

			else if (std::strcmp(argv[i], "-offset") == 0) { 

				if ((argv[i+1] != nullptr && argv[i+1][0] != '\0') && argv[i+1][0] != '-') {

					Offset = std::stoi(argv[i+1]);
				
				}

			}

		}

	}

	for (unsigned short i = 0; i < Paths.size(); i++) {

		Image Temp(Paths[i]);

		Images.push_back(&Temp);

		if (Images[i]->Read) {

			std::cout << std::endl << "  " << Diagnose(Images[i]) << std::endl;

		}

		else {

		 	std::cout << std::endl << "  " << Images[i]->Name + Images[i]->Type << " could not be read." << std::endl;

		 }

	}

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;

	std::cout << std::endl << "  Exec. Time: " << elapsed.count() << " secs." << std::endl;

	Terminate();

	return 0;

}
