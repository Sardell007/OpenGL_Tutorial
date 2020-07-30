#include "Camera.h"
#include <iostream>



Camera::Camera() {
	position = std::vector<float>{ 100.0f,35.0f,50.0f };
}

void Camera::move() {
	//int key = DisplayManager().getKey();
	////std::cout << yaw << std::endl;
	//switch (key) {
	//case keyD:
	//	position[0] -= 2.0f;
	//	break;
	//case keyA:
	//	position[0] += 2.0f;
	//	break;
	//case keyW:
	//	position[1] -= 0.2f;
	//	break;
	//case keyS:
	//	position[1] += 0.2f;
	//	break;
	//case keyZ:
	//	position[2] += 2.0f;
	//	break;
	//case keyX:
	//	position[2] -= 2.0f;
	//	break;
	//case keyQ:
	//	yaw -= 5.0f;
	//	break;
	//case keyE:
	//	yaw += 5.0f;
	//	break;
	//case keyEsc:
	//	DisplayManager().closeDisplay();
	//	break;
	//};
}