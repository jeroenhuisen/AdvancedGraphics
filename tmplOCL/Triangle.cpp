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