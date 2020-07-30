#pragma once
#include<vector>
#include <renderEngine/DisplayManager.h>
#include <Entity\Player.h>

class Camera {
private:
	std::vector<float> position;
	float pitch;
	float yaw;
	float roll;
	Player* player;
	float distanceFromPlayer;
	float angleAroundPlayer;
	void calculateZoom();
	void calculatePitch();
	void calculateAngleAroundPlayer();
	std::pair<float,float> calculateDistance();
	void calculateCameraPosition(std::pair<float, float> disti);
public:
	Camera(Player &player);
	void move();
	inline std::vector<float> getPosition() { return position; };
	inline float getPitch() { return pitch; };
	inline float getYaw() { return yaw; };
	inline float getRoll() { return roll; };
};