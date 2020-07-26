#include "Camera.h"
#include <iostream>

#define keyW 87
#define keyD 68
#define keyA 65
#define keyS 83
#define keyQ 81
#define keyE 69
#define keyEsc 256
#define keyZ 90
#define keyX 88

Camera::Camera() {
	position = std::vector<float>{ 0.0f,-1.0f,0.0f };
	//yaw = 180;
}

void Camera::move() {
	int key = DisplayManager().getKey();
	//std::cout << yaw << std::endl;
	switch (key) {
	case keyD:
		position[0] -= 2.0f;
		break;
	case keyA:
		position[0] += 2.0f;
		break;
	case keyW:
		position[1] -= 0.2f;
		break;
	case keyS:
		position[1] += 0.2f;
		break;
	case keyZ:
		position[2] += 2.0f;
		break;
	case keyX:
		position[2] -= 2.0f;
		break;
	case keyQ:
		yaw -= 5.0f;
		break;
	case keyE:
		yaw += 5.0f;
		break;
	case keyEsc:
		DisplayManager().closeDisplay();
		break;
	};
}