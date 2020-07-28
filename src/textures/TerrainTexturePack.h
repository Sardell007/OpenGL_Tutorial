#pragma once
#include "TerrainTexture.h"

class TerrainTexturePack {
private:
	TerrainTexture backgroundTexture;
	TerrainTexture rTexture;
	TerrainTexture gTexture;
	TerrainTexture bTexture;

public:
	TerrainTexturePack(TerrainTexture background, TerrainTexture r, TerrainTexture g, TerrainTexture b);
	TerrainTexturePack();
	inline TerrainTexture getBackground() { return backgroundTexture; };
	inline TerrainTexture getR() { return rTexture; };
	inline TerrainTexture getG() { return gTexture; };
	inline TerrainTexture getB() { return bTexture; };	
};