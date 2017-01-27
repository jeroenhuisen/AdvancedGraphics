#include "camera.h"
#include "system.h"


Camera::Camera(cl_float3 position, cl_float3 viewingDirection) :
	position(position), direction(viewingDirection),
	startDirection(glm::vec4(viewingDirection.x, viewingDirection.y, viewingDirection.z, 1)), startPosition(glm::vec4(position.x, position.y, position.z, 1)) {
	/*transformMat[0][0] = 0;
	transformMat[1][1] = 0;
	transformMat[2][2] = 0;*/
	/*transformMat[0][3] = position.x;
	transformMat[1][3] = position.y;
	transformMat[2][3] = position.z*/

}


void Camera::changePosition(const vec3 changePosition) {
	glm::mat4x4 t; // identity matrix
	/*t[0][3] = changePosition.x;
	t[1][3] = changePosition.y;
	t[2][3] = changePosition.z;*/
	t[3][0] = changePosition.x;
	t[3][1] = changePosition.y;
	t[3][2] = changePosition.z;
	transformMat = t*transformMat;
	glm::vec4 temp = transformMat * startPosition;
	position.x = temp.x;
	position.y = temp.y;
	position.z = temp.z;
	target.x = temp.x + direction.x;
	target.y = temp.y + direction.y;
	target.z = temp.z + direction.z;
}


void Camera::changeDirection(const vec3 rotationDirection) {
	/*glm::mat4x4 r;
	if (rotationDirection.x != 0) {
		// so its z we think because Ermis doesnt like barrelrolls ;( I cri everitiem
		float cosX = cos(-rotationDirection.x);
		float sinX = sin(-rotationDirection.x);
		r *= glm::mat4x4(cosX, sinX, 0, 0, -sinX, cosX, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		//r *= mat4x4(cosX, -sinX, 0, 0,  sinX, cosX, 0, 0,   0, 0, 1, 0,   0, 0, 0, 1);
	}
	if (rotationDirection.z != 0) {
		// so its z we think because Ermis doesnt like barrelrolls ;( I cri everitiem
		float cosZ = cos(rotationDirection.z);
		float sinZ = sin(rotationDirection.z);
		r *= glm::mat4x4(1, 0, 0, 0, 0, cosZ, sinZ, 0, 0, -sinZ, cosZ, 1, 0, 0, 0, 1);  //shouldnt here be a one?
																				   //r *= mat4x4(1, cosZ, -sinZ, 0, 0, sinZ, cosZ, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}
	transformMat *= r;
	glm::vec4 temp = transformMat * startDirection;
	direction.x = temp.x;
	direction.y = temp.y;
	direction.z = temp.z;*/
}