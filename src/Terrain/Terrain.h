#pragma once
#include <Models/RawModel.h>
#include <textures/ModelTexture.h>
#include <renderEngine/Loader.h>

class Terrain {
private:
	float x;
	float z;
	RawModel model;
	ModelTexture texture;
	RawModel generateTerrain(Loader &loader);
public:
	Terrain(int gridX, int gridZ, Loader &loader, ModelTexture &texture);
	inline float getX() { return x; };
	inline float getZ() { return z; };
	inline RawModel getModel() const { return model; };
	inline ModelTexture getTexture() const { return texture; };
};