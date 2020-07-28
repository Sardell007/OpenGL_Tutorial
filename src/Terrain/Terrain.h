#pragma once
#include <Models/RawModel.h>
#include <textures/ModelTexture.h>
#include <renderEngine/Loader.h>
#include <textures\TerrainTexturePack.h>

class Terrain {
private:
	float x;
	float z;
	RawModel model;
	TerrainTexturePack texturePack;
	TerrainTexture blendMap;
	RawModel generateTerrain(Loader &loader);
public:
	//Terrain(int gridX, int gridZ, Loader &loader, ModelTexture &texture);
	Terrain(int gridX, int gridZ, Loader& loader, TerrainTexturePack texturePacki, TerrainTexture blendMapi);
	inline TerrainTexture getblendMap() { return blendMap; };
	inline TerrainTexturePack getTexturePack() { return texturePack; };
	inline float getX() { return x; };
	inline float getZ() { return z; };
	inline RawModel getModel() const { return model; };
	//inline ModelTexture getTexture() const { return texture; };
};