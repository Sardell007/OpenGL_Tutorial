#include "Entity.h"

Entity::Entity(TexturedModel &modeli, std::vector<float> positioni, float rxi, float ryi, float rzi, float scalei)
{
	model = modeli;
	position = positioni;
	rx = rxi;
	ry = ryi;
	rz = rzi;
	scale = scalei;
}

void Entity::increasePosition(float dx, float dy, float dz) {
	position[0] += dx;
	position[1] += dy;
	position[2] += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
	rx += dx;
	ry += dy;
	rz += dz;
}