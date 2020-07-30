#pragma once
#include "Entity.h"
#include "renderEngine/DisplayManager.h"

class Player : public Entity {
private:
	void checkInput();
	void jump();
public:
	Player(TexturedModel& modeli, std::vector<float> positioni, float rxi, float ryi, float rzi, float scalei);
	void move();
	
};