#include "camera.h"
#include "template.h"


Camera::Camera(int width, int height, float horizontalFOV, glm::vec3 position, glm::vec3 viewingDirection ) :
	Placeable(position, viewingDirection), screenWidth(width), screenHeight(height), horizontalFOV(horizontalFOV), width2(width/2), height2(height/2){

	screenDistance = width2 / tanf(horizontalFOV * PI / 360);
	glm::vec3 center = direction * screenDistance + position;
	mat3x3 zAxisLocal90C(0.0f, 1.0f, 0.0f,
						-1.0f, 0.0f,0.0f,
						0.0f, 0.0f, 1.0f);
	mat3x3 zAxisLocal90(0.0f, -1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f);

	mat3x3 yAxisLocal90C(0.0f, 0.0f, -1.0f,
						0.0f, 1.0f, 0.0f,
						1.0f, 0.0f, 0.0f);
	mat3x3 yAxisLocal90(0.0f, 0.0f, 1.0f,
						0.0f, 1.0f, 0.0f,
						-1.0f, 0.0f, 0.0f);
	p0 = center + zAxisLocal90C * direction * width2; //only with also height so
	p0 += yAxisLocal90C * direction * height2; // height done
	p1 = center + zAxisLocal90 * direction * width2; //- since + didn t work but yeah... should be another rotation thing?
	p1 += yAxisLocal90C * direction * height2; 
	p2 = center + zAxisLocal90 * direction * width2;
	p2 -= yAxisLocal90 * direction * height2;

	p0.x = -width2;
	p0.y = screenDistance;
	p0.z = -height;

	p1.x = width2;
	p1.y = screenDistance;
	p1.z = -height;

	p2.x = -width2;
	p2.y = screenDistance;
	p2.z = height;

	//quite inefficient since multiple matrix multiplications and stuff while some geometry might also work? can atleast be combined 3 matrix for 3 points should be enough...
}

glm::vec3 Camera::getPixelDirection(int x, int y) {
	// x-width2 is the pixel distance
	//x - width2;
	//y - height2;
	float u = (float) x / screenWidth;
	float v = (float) y / screenHeight;

	vec3 pXY = p0 + u*(p1 - p0) + v*(p2 - p0);
	vec3 d = (pXY - position);
	//d / d.length
	//return glm::normalize(d);
	return d;
}