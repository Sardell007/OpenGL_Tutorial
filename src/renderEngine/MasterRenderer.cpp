#include "MasterRenderer.h"

const float FOV = 70.0f;
const float Near_Plane = 0.1f;
const float Far_Plane = 1000;


MasterRenderer::MasterRenderer() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	createProjectionMatrix();
	renderer = EntityRenderer(shader, projectionMatrix);
	terrainRenderer = TerrainRenderer(terrainShader, projectionMatrix);
}

void MasterRenderer::cleanUp() {
	shader.cleanUp();
	terrainShader.cleanUp();
}

void MasterRenderer::render(Light &sun, Camera &camera) {
	prepare();
	shader.start();
	shader.loadLight(sun);
	shader.loadViewMatrix(camera);
	renderer.render(entities);
	shader.stop();
	terrainShader.start();
	terrainShader.loadLight(sun);
	terrainShader.loadViewMatrix(camera);
	terrainRenderer.renderer(terrains);
	terrainShader.stop();
	terrains.clear();
	entities.clear();
}

void MasterRenderer::processTerrain(Terrain &terrain) {
	terrains.push_back(terrain);
}

void MasterRenderer::processEntity(Entity entity) {
	TexturedModel entityModel = entity.getModel();
	if (entities.find(entityModel.getKey())!=entities.end()) {
		std::vector<Entity> batch = entities[entityModel.getKey()];
		batch.push_back(entity);
		entities[entityModel.getKey()] = batch;
	}
	else {
		std::vector<Entity> batch{ entity };
		entities[entityModel.getKey()] = batch;
	}
	//entities.push_back(entity);
}

void MasterRenderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix() {
	MasterRenderer::projectionMatrix = glm::perspectiveFov(FOV,(float) DisplayManager().getWidth(), (float)DisplayManager().getHeight(), Near_Plane, Far_Plane);
}