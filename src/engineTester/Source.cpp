#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "renderEngine/EntityRenderer.h"
#include "shaders/StaticShader.h"
#include "textures/ModelTexture.h"
#include "Entity/Camera.h"
#include "renderEngine/OBJLoader.h"
#include "Entity/Light.h"
#include "renderEngine/MasterRenderer.h"

#include <vector>
#include <iostream>
#include <Entity\Player.h>

#define WIDTH 2880
#define HEIGHT 1800

int main() {

	DisplayManager display(WIDTH, HEIGHT);
	display.createDisplay();

	Loader loader;

	OBJLoader load;

	RawModel treeModel = load.loadObjModel("res/tree.obj", loader);
	ModelTexture treeTexture(loader.loadTexture("res/tree.png"));
	treeTexture.setShineDamper(100);
	treeTexture.setReflectivity(10);
	TexturedModel treeStaticModel(treeModel, treeTexture);
	std::vector<Entity> trees;

	for (int i = 0; i < 100; i++) {
		float posX = (float)((std::rand()) % 1600 - 800);
		float posZ = (float)((std::rand()) % 800);
		float scale = (float)(0.5 + ((std::rand()) % 10) / 10);
		trees.push_back(Entity(treeStaticModel, std::vector<float>{posX, 0.0f, -posZ}, 0, 0, 0, 10 * scale));
	}

	RawModel grassModel = load.loadObjModel("res/grassMod.obj", loader);
	ModelTexture grassTexture(loader.loadTexture("res/grassTex.png"));
	grassTexture.setHasTransparency(true);
	grassTexture.setUseFakeLighting(true);
	TexturedModel grassStaticModel(grassModel, grassTexture);
	std::vector<Entity> grass;

	for (int i = 0; i < 10; i++) {
		float posX = (float)((std::rand()) % 1600 - 800);
		float posZ = (float)((std::rand()) % 800) + 1;
		float scale = (float)(0.5 + ((std::rand()) % 10) / 10);
		trees.push_back(Entity(grassStaticModel, std::vector<float>{posX, 0.0f, -posZ}, 0, 0, 0, 10 * scale));
	}

	Light light(std::vector<float>{3000, 2000, 2000}, std::vector<float>{1.0, 1.0, 1.0});
	TerrainTexture background(loader.loadTexture("res/grassy2.png"));
	TerrainTexture flower(loader.loadTexture("res/grassFlower.png"));
	TerrainTexture mud(loader.loadTexture("res/mud.png"));
	TerrainTexture path(loader.loadTexture("res/path.png"));
	TerrainTexturePack texturePack(background, flower, mud, path);
	TerrainTexture blendMap(loader.loadTexture("res/blendMap.png"));

	Terrain terrain1(0, -1, loader, texturePack, blendMap);
	Terrain terrain2(-1, -1, loader, texturePack, blendMap);

	RawModel bunnyModel = load.loadObjModel("res/bunny.obj", loader);
	ModelTexture bunnyTexture(loader.loadTexture("res/white.png"));
	bunnyTexture.setShineDamper(100);
	bunnyTexture.setReflectivity(10);
	TexturedModel bunnyStaticModel(bunnyModel, bunnyTexture);
	
	Player player(bunnyStaticModel, std::vector<float>{100.0f, 0.0f, -50.0f}, 0, 0, 0, 1);

	Camera camera;
	MasterRenderer renderer;

	while (display.isCloseRequested()) {
		camera.move();
		player.move();
		renderer.processEntity(player);
		renderer.processTerrain(terrain1);
		renderer.processTerrain(terrain2);
		for (Entity entity : trees)
			renderer.processEntity(entity);
		for (Entity entity : grass)
			renderer.processEntity(entity);
		renderer.render(light, camera);
		display.updateDisplay();
	}
	renderer.cleanUp();
	loader.cleanUp();
	display.closeDisplay();
}