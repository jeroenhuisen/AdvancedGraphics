#include "camera.h"
#include "template.h"


Camera::Camera(int width, int height, float horizontalFOV, glm::vec3 position, glm::vec3 viewingDirection ) :
	Placeable(position, viewingDirection), screenWidth(width), screenHeight(height), horizontalFOV(horizontalFOV), width2(width/2), height2(height/2), startDirection(glm::vec4(viewingDirection, 1)), startPosition(glm::vec4(position, 1)) {

	screenDistance = width2 / tanf(glm::radians(horizontalFOV * 0.5f));
	/*transformMat[0][3] = position.x;
	transformMat[1][3] = position.y;
	transformMat[2][3] = position.z*/
	moveCamera();


/*	p0.x = -width2;
	p0.y = screenDistance;
	p0.z = -height2;

	p1.x = width2;
	p1.y = screenDistance;
	p1.z = -height2;

	p2.x = -width2;
	p2.y = screenDistance;
	p2.z = height2;
*/
	//quite inefficient since multiple matrix multiplications and stuff while some geometry might also work? can atleast be combined 3 matrix for 3 points should be enough...
}

glm::vec3 Camera::getPixelDirection(int x, int y) {
	// x-width2 is the pixel distance
	//x - width2;
	//y - height2;
	float u = (float) x / screenWidth;
	float v = (float) y / screenHeight;

	vec3 pXY = p0 + u*(p1 - p0) + v*(p2 - p0);
	vec3 d = (pXY - position);
	//d / d.length-
	//return glm::normalize(d);
	return d;
}

void Camera::changePosition(vec3 changePosition) {
	glm::mat4x4 t; // identiy matrix
	t[0][3] = changePosition.x;
	t[1][3] = changePosition.y;
	t[2][3] = changePosition.z;
	transformMat = t*transformMat;
	glm::vec4 temp = startDirection * transformMat + startPosition;
	position.x = temp.x;
	position.y = temp.y;
	position.z = temp.z;
}


void Camera::changeDirection(vec3 rotationDirection) {
	glm::mat4x4 r;
	if (rotationDirection.x != 0) {
		// so its z we think because Ermis doesnt like barrelrolls ;( I cri everitiem
		float cosX = cos(-rotationDirection.x);
		float sinX = sin(-rotationDirection.x);
		r *= mat4x4(cosX, sinX, 0,0, -sinX, cosX, 0,0, 0,0,1,0, 0,0,0,1);
	}
	if (rotationDirection.z != 0) {
		// so its z we think because Ermis doesnt like barrelrolls ;( I cri everitiem
		float cosZ = cos(rotationDirection.z);
		float sinZ = sin(rotationDirection.z);
		r *= mat4x4(1, 0, 0, 0, 0, cosZ, sinZ, 0, 0, -sinZ, cosZ, 0, 0, 0, 0, 1);
	}
	transformMat *= r;
	glm::vec4 temp = transformMat * startDirection;
	direction.x = temp.x;
	direction.y = temp.y;
	direction.z = temp.z;
}

void Camera::moveCamera() {
	glm::vec3 center = direction * screenDistance + position;

	p0 = center + zAxisLocal90C * direction * width2; //only with also height so
	p0 += xAxisLocal90 * direction * height2; // height done
	p1 = center + zAxisLocal90 * direction * width2; //- since + didn t work but yeah... should be another rotation thing?
	p1 += xAxisLocal90 * direction * height2;
	p2 = center + zAxisLocal90C * direction * width2;
	p2 += xAxisLocal90C * direction * height2;
}