#pragma once
#include "system.h"

/*struct BVHNode
{
AABB bounds;	// 24 byes
int leftFirst;	// 4 bytes
int first;		// 4 bytes, total 32 bytes
};*/

/*BVHNode::Traverse(Ray r) {
if (!r.Intersects(bounds)) return
;
if
(isleaf())
{
IntersectPrimitives();
}
else {
pool[left].Traverse(r);
pool[left + 1].Traverse(r);
}
}*/


struct BVHNodeStruct {
	cl_float3 leftBottom;
	cl_float3 rightTop;

	cl_int leftFirst;
	cl_int count; //amount of triangles
};