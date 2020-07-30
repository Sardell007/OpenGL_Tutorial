#include "Camera.h"
#include <iostream>
#include <math.h>
#include <cmath>

float toRadian = 3.1415 / 180;

Camera::Camera(Player &playeri):player(&playeri) {
	position = std::vector<float>{ 0.0f,0.0f,0.0f };
	distanceFromPlayer = 50;
	angleAroundPlayer = 0;
	pitch = 20;
}

void Camera::move() {
	calculateZoom();
	calculatePitch();
	calculateAngleAroundPlayer();
	std::pair<float, float> dist = calculateDistance();
	calculateCameraPosition(dist);
	yaw = 180 - (player->getRy() + angleAroundPlayer);
}

void Camera::calculateZoom() {
	float zoomLevel = DisplayManager().getScroll().second;
	//std::cout << zoomLevel << std::endl;
	distanceFromPlayer -= zoomLevel;
}

void Camera::calculatePitch() {
	if (DisplayManager().getMKey() == 1) {
		float pitchChange = DisplayManager().getCPos().second * 0.1f;
		pitch -= pitchChange;
	}
}

void Camera::calculateAngleAroundPlayer() {
	if (DisplayManager().getMKey() == -1) {
		float angleChange = DisplayManager().getCPos().first * 0.1f;
		angleAroundPlayer -= angleChange;
	}
}

std::pair<float,float> Camera::calculateDistance() {
	return { (float)distanceFromPlayer * cosf(pitch * toRadian),(float)distanceFromPlayer * sinf(pitch * toRadian) };
}

void Camera::calculateCameraPosition(std::pair<float,float> disti) {
	float theta = player->getRy() + angleAroundPlayer;
	float offsetX = (float) disti.first * sinf(theta * toRadian);
	float offsetZ = (float) disti.first * cosf(theta * toRadian);
	//std::cout << offsetX << offsetZ << std::endl;
	Camera::position[0] = player->getPosition()[0] - offsetX;
	Camera::position[2] = (player->getPosition()[2] - offsetZ);
	Camera::position[1] = player->getPosition()[1] + disti.second;
}