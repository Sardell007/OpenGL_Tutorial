#pragma once
#include <Models/TexturedModel.h>
#include <vector>

class Entity {

public:
	Entity(TexturedModel &modeli, std::vector<float> positioni, float rxi,float ryi, float rzi, float scalei);
	TexturedModel getModel() { return model; };
	std::vector<float> getPosition() { return position; };
	float getRx() { return rx; };
	float getRy() { return ry; };
	float getRz() { return rz; };
	float getScale() { return scale; };
	void increasePosition(float dx,float dy,float dz);
	void increaseRotation(float dx, float dy, float dz);
private:
	TexturedModel model;
	std::vector<float> position;
	float rx, ry, rz;
	float scale;
};