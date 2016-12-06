#pragma once
#include "template.h"
#include "placeable.h"
#include "mat90.h"
#include "ray.h"

class Camera : public Placeable {
private:
	float screenDistance;
	int screenWidth;
	int screenHeight;
	float horizontalFOV;
	float width2, height2;

	glm::vec3 p0, p1, p2;

	glm::mat4x4 transformMat; //defualt id matrix
	glm::vec4 startDirection;
	glm::vec4 startPosition;
public:
	Camera(int width, int height, float horizontalFOV, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 viewingDirection = glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 getPixelDirection(int x, int y);

	//changePosition takes offset vector and does not replace the position.
	void changePosition(glm::vec3 changePosition);
	//change direction takes offset vector and does not replace it.
	void changeDirection(glm::vec3 changeDirection);
	void moveCamera();
};