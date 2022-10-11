#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*

*/

class Camera {
private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;//reverse
	glm::vec3 right;
	glm::vec3 up;
	
public:
	Camera(const glm::vec3& camPos, const glm::vec3& camDir_rev) :
		cameraPosition(camPos), cameraDirection(camDir_rev) {
		cameraDirection = glm::normalize(cameraDirection);
		up = glm::vec3(0, 1, 0);
		right = glm::normalize(glm::cross(up, cameraDirection));
	}

};