#include "camera.h"
#include "template.h"


Camera::Camera(int width, int height, float horizontalFOV, glm::vec3 position, glm::vec3 viewingDirection ) :
	Object(position, viewingDirection), screenWidth(width), screenHeight(height), horizontalFOV(horizontalFOV), width2(width/2), height2(height/2){
	screenDistance = width2 / tanf(horizontalFOV * PI / 360);
}

glm::vec3 Camera::getPixelDirection(int x, int y) {
	// x-width2 is the pixel distance
	//x - width2;
	//y - height2;
	float u = x / screenWidth;
	float v = y / screenHeight;

	vec3 pXY = p0 + u*(p1 - p0) + v*(p2 - p0);
	vec3 d = (pXY - position);
	//d / d.length
	return glm::normalize(d);
}