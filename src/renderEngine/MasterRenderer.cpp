#include "MasterRenderer.h"

const float FOV = 70.0f;
const float Near_Plane = 0.1f;
const float Far_Plane = 1000;

const float RED = 0.5;
const float GREEN = 0.5;
const float BLUE = 0.5;


MasterRenderer::MasterRenderer() {
	enableCulling();
	createProjectionMatrix();
	renderer = EntityRenderer(shader, projectionMatrix);
	terrainRenderer = TerrainRenderer(terrainShader, projectionMatrix);
}

void MasterRenderer::cleanUp() {
	shader.cleanUp();
	terrainShader.cleanUp();
}

void MasterRenderer::enableCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::render(Light &sun, Camera &camera) {
	prepare();
	shader.start();
	shader.loadSkyColour(RED, GREEN , BLUE);
	shader.loadLight(sun);
	shader.loadViewMatrix(camera);
	renderer.render(entities);
	shader.stop();
	terrainShader.start();
	shader.loadSkyColour(RED, GREEN, BLUE);
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
	glClearColor(RED, GREEN, BLUE, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix() {
	MasterRenderer::projectionMatrix = glm::perspectiveFov(FOV,(float) DisplayManager().getWidth(), (float)DisplayManager().getHeight(), Near_Plane, Far_Plane);
}