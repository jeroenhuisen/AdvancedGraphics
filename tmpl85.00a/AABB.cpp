#include "template.h"
#include "AABB.h"

AABB::AABB(const glm::vec3 leftBottom, const glm::vec3 rightTop):
	leftBottom(leftBottom), rightTop(rightTop){

}

//@warning volume instead of surface
float AABB::surfaceArea() {
	
	//0 is kind of an issue 
	/*if (result.x == 0) {
		result.x = 0.1;
	}
	if (result.y == 0) {
		result.y = 0.1;
	}
	if (result.z == 0) {
		result.z = 0.1;
	}*/
	//return abs(result.x*result.y*result.z);
	// 2 * SA(xy) + 2 * SA(xz) + 2 * SA(yz)
	// 2 * (SA(XY) + SA(XZ) + SA(YZ)
	glm::vec3 result = rightTop - leftBottom;
	return 2.f * (result.x*result.y + result.x*result.z + result.y*result.z);

}


// http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
bool AABB::intersects(Ray* r, float* distance) {
	// r->dir is unit direction vector of ray
	glm::vec3 dirfrac;
	dirfrac.x = 1.0f / r->direction.x;
	dirfrac.y = 1.0f / r->direction.y;
	dirfrac.z = 1.0f / r->direction.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r->org is origin of ray
	float t1 = (leftBottom.x - r->origin.x)*dirfrac.x;
	float t2 = (rightTop.x - r->origin.x)*dirfrac.x;
	float t3 = (leftBottom.y - r->origin.y)*dirfrac.y;
	float t4 = (rightTop.y - r->origin.y)*dirfrac.y;
	float t5 = (leftBottom.z - r->origin.z)*dirfrac.z;
	float t6 = (rightTop.z - r->origin.z)*dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		*distance = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		*distance = tmax;
		return false;
	}

	*distance = tmin;
	r->bvhHit++;
	return true;
}