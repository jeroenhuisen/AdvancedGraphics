#include "mat90.h"
#include "template.h"
const glm::mat3x3 zAxisLocal90C =glm::mat3x3(0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f);

const glm::mat3x3 zAxisLocal90 = glm::mat3x3(0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f);


const glm::mat3x3 xAxisLocal90C = glm::mat3x3(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f);
const glm::mat3x3 xAxisLocal90 = glm::mat3x3(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);