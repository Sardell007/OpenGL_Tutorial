#pragma once
#include <shaders/StaticShader.h>
#include "EntityRenderer.h"
#include "DisplayManager.h"
#include <toolbox/Maths.h>
#include <glm/gtc/matrix_transform.hpp>
#include <renderEngine\TerrainRenderer.h>

class MasterRenderer {
private:
	glm::mat4 projectionMatrix;
	StaticShader shader;
	EntityRenderer renderer;
	TerrainRenderer terrainRenderer;
	TerrainShader terrainShader;
	std::vector <Terrain> terrains;
	std::map <int, std::vector<Entity>> entities;
public:
	MasterRenderer();
	static void enableCulling();
	static void disableCulling();
	void cleanUp();
	void render(Light &sun, Camera &camera);
	void processTerrain(Terrain &terrain);
	void processEntity(Entity entity);
	void prepare();
	void createProjectionMatrix();
};