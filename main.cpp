#include <iostream>
#include <fstream>
#include "vec.h"
#include "color.h"

int main() {

	// Image dimensions 
	int imageWidth = 256;
	int imageHeight = 256;

	// Output file

	std::ofstream renderFile;
	renderFile.open("renderOutput.ppm");


	// Render image 

	renderFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	
	for (int i = 0; i < imageHeight; i++) {
		std::clog << "\rScanlines remaining: " << (imageHeight - i) << " " << std::flush;
		for (int j = 0; j < imageWidth; j++) {
			
			
			auto pixel_color = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
			write_color(renderFile, pixel_color); // Write color to renderImage

		}
	}

	std::clog << "\rDone.\n";

	// Close Render
	renderFile.close();

	return 0;
}