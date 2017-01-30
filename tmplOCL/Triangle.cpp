#include "system.h"
#include "Triangle.h"

Triangle createTriangle(vec3 v1, vec3 v2, vec3 v3, Material material) {
	Triangle t;
	t.v1 = { v1.x, v1.y, v1.z };
	t.v2 = { v2.x, v2.y, v2.z };
	t.v3 = { v3.x, v3.y, v3.z };

	vec3 dir = normalize(cross((v2 - v1), (v3 - v1)));
	t.direction = { dir.x, dir.y, dir.z };

	vec3 e1 = v2 - v1;
	vec3 e2 = v3 - v1;
	t.e1 = { e1.x, e1.y, e1.z };
	t.e2 = { e2.x, e2.y, e2.z };
	//t.material = material;
	t.color = { material.color.x, material.color.y, material.color.z, material.reflectioness };
//	t.reflect = material.reflectioness;
	return t;
}

Triangle createTriangle(vec3 v1, vec3 v2, vec3 v3, vec3 n1, vec3 n2, vec3 n3, Material material) {
	Triangle t;
	t.v1 = { v1.x, v1.y, v1.z };
	t.v2 = { v2.x, v2.y, v2.z };
	t.v3 = { v3.x, v3.y, v3.z };

	//vec3 dir = normalize(n1 + n2 + n3);//doesn't work
	vec3 dir = normalize(cross((v2 - v1), (v3 - v1)));
	/*if (dir1.x < 0 && dir.x > 0) {
		dir.x = dir.x*-1;
	}
	if (dir1.y < 0 && dir.y > 0) {
		dir.y = dir.y*-1;
	}
	if (dir1.z < 0 && dir.z > 0) {
		dir.z = dir.z*-1;
	}*/
	t.direction = { dir.x, dir.y, dir.z };

	vec3 e1 = v2 - v1;
	vec3 e2 = v3 - v1;
	t.e1 = { e1.x, e1.y, e1.z };
	t.e2 = { e2.x, e2.y, e2.z };
	//t.material = material;
	t.color = { material.color.x, material.color.y, material.color.z, material.reflectioness };
//	t.reflect = material.reflectioness;
	return t;
}

AABB getBounds(Triangle t) {
	float xMin = min(t.v1.x, t.v2.x);
	xMin = min(xMin, t.v3.x);
	float yMin = min(t.v1.y, t.v2.y);
	yMin = min(yMin, t.v3.y);
	float zMin = min(t.v1.z, t.v2.z);
	zMin = min(zMin, t.v3.z);

	float xMax = max(t.v1.x, t.v2.x);
	xMax = max(xMax, t.v3.x);
	float yMax = max(t.v1.y, t.v2.y);
	yMax = max(yMin, t.v3.y);
	float zMax = max(t.v1.z, t.v2.z);
	zMax = max(zMax, t.v3.z);

	/*float xMin = v1.x, yMin = v1.y, zMin = v1.z;
	float xMax = v1.x, yMax = v1.y, zMax = v1.z;

	if (v2.x > xMin) {
	xMax = v2.x;
	}
	else { // == aswell for no real reason
	xMin = v2.x;
	}
	if (v2.y > yMin) {
	yMax = v2.y;
	}
	else { // == aswell for no real reason
	yMin = v2.y;
	}
	if (v2.z > zMin) {
	zMax = v2.z;
	}
	else { // == aswell for no real reason
	zMin = v2.z;
	}


	if (v3.x > xMin) {
	xMax = v3.x;
	}
	else { // == aswell for no real reason
	xMin = v3.x;
	}
	if (v3.y > yMin) {
	yMax = v3.y;
	}
	else { // == aswell for no real reason
	yMin = v3.y;
	}
	if (v3.z > zMin) {
	zMax = v3.z;
	}
	else { // == aswell for no real reason
	zMin = v3.z;
	}
	*/
	return AABB(glm::vec3(xMin, yMin, zMin), glm::vec3(xMax, yMax, zMax));
}