#pragma once
#include "template.h"
#include "object.h"

class Camera : public Object {
private:
	float screenDistance;
	int screenWidth;
	int screenHeight;
	float horizontalFOV;
	float width2, height2;

	//vec3 centerPointScreen; // could be deriaved from screenDistance postion and direction or a non normalized direction point but this is the easiest way. wront but non normalized direction point would be so much nicer.

	vec3 p0, p1, p2;
public:
	Camera(int width, int height, float horizontalFOV, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 viewingDirection = glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec3 getPixelDirection(int x, int y);
};