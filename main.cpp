#include <iostream>
#include <fstream>
#include "vec.h"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}




color ray_color(ray& r) {

	vec3 unit_direction = unit_vector(r.direction());

	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(abs(unit_direction.y()), abs(unit_direction.x()), 1.0);
	

	/*vec3 unitDirection = unit_vector(r.direction());
	auto a = abs(unitDirection.y() + 1) * 0.5;
	return (1 - a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);*/

	
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

	/*return color(1.0, abs(unitDirection.y()), 1.0);*/
}


int main() {

	

	

	// Image dimensions 
	auto aspect_ratio = 16.0 / 9.0;
	int imageWidth = 800;
	int imageHeight = int(imageWidth / aspect_ratio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
	auto cameraCenter = point3(0, 0, 0);

	auto viewport_u = vec3(viewportWidth, 0, 0); // Vectors going across horizontal and vertical viewport edges
	auto viewport_v = vec3(0, -viewportHeight, 0);

	auto pixelDelta_u = viewport_u / imageWidth;
	auto pixelDelta_v = viewport_v / imageHeight;

	auto viewportUpperLeft = cameraCenter + vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;

	auto pixel_00_loc = viewportUpperLeft + 0.5 * (pixelDelta_u) +  0.5 * (pixelDelta_v);


	// Output file

	std::ofstream renderFile;
	renderFile.open("renderOutput.ppm");

		
	// Render image 

	renderFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	
	for (int i = 0; i < imageHeight; i++) {
		std::clog << "\rScanlines remaining: " << (imageHeight - i) << " " << std::flush;
		for (int j = 0; j < imageWidth; j++) {
			auto pixelCenter = pixel_00_loc + (j * pixelDelta_u) + (i * pixelDelta_v);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r(cameraCenter, rayDirection);
			
			color pixelColor = ray_color(r);
			//auto pixelColor = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
			write_color(renderFile, pixelColor); // Write color to renderImage

		}
	}

	std::clog << "\rDone.\n";

	// Close Render
	renderFile.close();

	return 0;
}