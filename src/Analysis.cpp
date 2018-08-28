
#include "../include/Analysis.hpp"

float Analyze(Image *Img, Circumference *Pupil) {

	unsigned short Compromised = 0, Flash = 0;
	
	for (unsigned short i = Pupil->y - Pupil->r; i <= Pupil->y + Pupil->r; i++) {

		for (unsigned short j = Pupil->x - Pupil->r; j <= Pupil->x + Pupil->r; j++) {

			if (d(j, i, Pupil->x, Pupil->y) <= Pupil->r) {

				if (Img->Matrix[i][j].Red > 200) {

					Flash++;

				}

				else if (Img->Matrix[i][j].Red > 90) {

					Compromised++;

				}

			}

		}

	}

	return (float) Compromised / (PI * pow(Pupil->r, 2) - Flash);

}

float Process(Image *Img) {

	Crop(Img);

	Pixel **Color = Copy(Img);

	Grayscale(Img);

	Pixel **Grayscale = Copy(Img);

	Edge(Img);

	Circumference Pupil = Hough(Img);
		
	Paste(Grayscale, Img);

	if (Img->Name == "Normal2") {	

		Adjust(Img, &Pupil);

	}

	float Analysis = Analyze(Img, &Pupil);

	Paste(Color, Img);

	Draw_Circumference(Img, &Pupil);

	return Analysis;

}

std::string Diagnose(Image *Img) {

	std::string Diagnosis;

	float Compromised = Process(Img);

	if (Compromised > 0.5) {

		Diagnosis = "Sick. " + std::to_string(Compromised * 100).substr(0, 4) + '%' + " of your pupil has been compromised. Try to contact your doctor as soon as possible.";

	}

	else {

		Diagnosis = "Not sick. " + std::to_string(Compromised * 100).substr(0, 4) + '%' + " of your pupil has been compromised, but this means you aren't sick based on our parameters.";

	}

	Img->Comments.push_back(Diagnosis);

	write(Img, Img->Directory, Img->Name + "-processed.ppm", true);

	return Diagnosis;

}
