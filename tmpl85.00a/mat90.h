#pragma once
#ifndef mat90
#define mat90


#include "template.h"

/*class mat90 {
public:*/
extern const glm::mat3x3 zAxisLocal90C;
extern const glm::mat3x3 zAxisLocal90;/* (0.0f, -1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f);*/

	/*mat3x3 yAxisLocal90C(0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f);
	mat3x3 yAxisLocal90(0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, 0.0f);*/
extern const glm::mat3x3 xAxisLocal90C;// (1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f);
extern const glm::mat3x3 xAxisLocal90;// (1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
//};
	#endif // !mat90