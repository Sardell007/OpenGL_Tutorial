#pragma once

class TerrainTexture {
private:
	int textureID;
public:
	TerrainTexture(int textureIDi);
	TerrainTexture();
	inline int getTextureID() { return textureID; };
};