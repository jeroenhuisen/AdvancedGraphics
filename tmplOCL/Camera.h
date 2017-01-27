#pragma once
#include "system.h"
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Camera {
private:

	glm::mat4x4 transformMat; //defualt id matrix
	glm::vec4 startDirection;
	glm::vec4 startPosition;


public:
	Camera(cl_float3 position = { 0.0f, 0.0f, 0.0f }, cl_float3 viewingDirection = { 0.0f, 0.0f, 1.0f });

	//changePosition takes offset vector and does not replace the position.
	void changePosition(const vec3 changePosition);
	//change direction takes offset vector and does not replace it.
	void changeDirection(const vec3 changeDirection);
	void moveCamera();

	cl_float3 position;
	cl_float3 direction;
	cl_float3 target;
};