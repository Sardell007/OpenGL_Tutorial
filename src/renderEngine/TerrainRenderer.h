#pragma once
#include <shaders/TerrainShader.h>
#include <Terrain/Terrain.h>
#include <Models/TexturedModel.h>

class TerrainRenderer {
private:
	TerrainShader shader;
	void bindTexture(Terrain terrain);
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix);
	TerrainRenderer();
	void renderer(std::vector<Terrain> &terrains);
	void prepareTerrain(Terrain &terrain);
	void unbindTexturedModel();
	void loadModelMatrix(Terrain &terrain);
};