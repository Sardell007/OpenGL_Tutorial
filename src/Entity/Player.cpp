#include "Player.h"

#include <cmath>
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
#define keySpace 32

float const RUN_SPEED = 20.0f;
float const TURN_SPEED = 160.0f;
float const GRAVITY = -50.0f;
float const JUMP_POWER = 30.0f;

float const TERRAIN_HEIGHT = 0.0f;

float currentSpeed = 0;
float currentTurnSpeed = 0;
float upwardSpeed = 0;

bool inAir = false;

Player::Player(TexturedModel& modeli, std::vector<float> positioni, float rxi, float ryi, float rzi, float scalei):
	Entity(modeli,positioni,rxi,ryi,rzi,scalei){
}

void Player::move() {
	float toRadians = 3.14159f / 180.0f;
	checkInput();
	increaseRotation(0, currentTurnSpeed * DisplayManager().getFrameTimeSeconds(), 0);
	float distance = currentSpeed * DisplayManager().getFrameTimeSeconds();
	float dx = (float) distance * std::sinf(getRy()*toRadians);
	float dz = (float)distance * std::cosf(getRy()*toRadians);
	increasePosition(dx, 0, dz);
	upwardSpeed += GRAVITY * DisplayManager().getFrameTimeSeconds();
	increasePosition(0, upwardSpeed*DisplayManager().getFrameTimeSeconds(), 0);

	if (getPosition()[1] < TERRAIN_HEIGHT) {
		upwardSpeed = 0;
		inAir = false;	
		increasePosition(0,TERRAIN_HEIGHT-getPosition()[1],0);
	}
}

void Player::jump() {
	if (!inAir) {
		upwardSpeed = JUMP_POWER;
		inAir = true;
	}
}

void Player::checkInput() {
	int key = DisplayManager().getKey();
	//std::cout << key << std::endl;
	switch (key)
	{
	case keyW:
		currentSpeed = RUN_SPEED;
		break;
	case keyS:
		currentSpeed = -RUN_SPEED;
		break;
	default:
		currentSpeed = 0;
		break;
	}

	switch (key)
	{
	case keyA:
		currentTurnSpeed = TURN_SPEED;
		break;
	case keyD:
		currentTurnSpeed = -TURN_SPEED;
		break;
	default:
		currentTurnSpeed = 0;
		break;
	}

	if (key == keySpace) {
		jump();
	}

}