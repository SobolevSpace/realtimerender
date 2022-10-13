#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float PI = acos(-1);
const float YAW = -PI/2;
const float MOUSE_SENSITY = 0.1*PI/180;
const float MOVE_SPEED = 2.5f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

class Camera {
private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;//front
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float zoom;

	void updateCameraVectors() {
		cameraDirection = glm::vec3(
			cos(yaw)*cos(pitch),
			sin(pitch),
			sin(yaw)*cos(pitch)
		);
		right = glm::normalize(glm::cross(cameraDirection, worldUp));
		up = glm::cross(right, cameraDirection);
	}
	
public:
	glm::mat4 view;

	Camera(const glm::vec3& camPos = glm::vec3(0, 0, 0), const glm::vec3& _wup = glm::vec3(0, 1, 0), float _yaw = YAW, float _pitch = PITCH) :
		cameraPosition(camPos), worldUp(_wup), yaw(_yaw), pitch(_pitch), zoom(ZOOM) {
		cameraDirection = glm::normalize(cameraDirection);
		updateCameraVectors();
	}

	glm::mat4x4 get_view() {
		return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, up);
	}

	float get_zoom() {
		return zoom;
	}

	void process_keyboard(Camera_Movement m, float delta) {
		float distance = delta * MOVE_SPEED;
		switch (m) {
		case FORWARD: cameraPosition += distance * cameraDirection; break;
		case BACKWARD: cameraPosition -= distance * cameraDirection; break;
		case RIGHT: cameraPosition += distance * right; break;
		case LEFT: cameraPosition -= distance * right; break;
		}
	}

	void process_mouse_movement(float xoffset, float yoffset, GLboolean constrain = true) {
		xoffset *= MOUSE_SENSITY;
		yoffset *= MOUSE_SENSITY;

		yaw += xoffset;
		pitch += yoffset;

		const float bound = 89.0f / 180.f*PI;
		if (constrain) {
			if (pitch > bound) pitch = bound;
			else if (pitch < -bound) pitch = -bound;
		}

		updateCameraVectors();
	}

	void process_mouse_scroll(float offset) {
		zoom -= offset;
		if (zoom < 1.0f) zoom = 1.0f;
		else if (zoom > 90.f) zoom = 90.f;
	}

};