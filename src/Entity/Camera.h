#pragma once
#include<vector>
#include <renderEngine/DisplayManager.h>

class Camera {
private:
	std::vector<float> position;
	float pitch;
	float yaw;
	float roll;
public:
	Camera();
	void move();
	inline std::vector<float> getPosition() { return position; };
	inline float getPitch() { return pitch; };
	inline float getYaw() { return yaw; };
	inline float getRoll() { return roll; };
};