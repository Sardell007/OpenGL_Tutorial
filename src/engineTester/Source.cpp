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

#define WIDTH 2880
#define HEIGHT 1800

int a = std::rand();

int main() {
	 
	DisplayManager display(WIDTH,HEIGHT);
	display.createDisplay();

	Loader loader;

	OBJLoader load;
	RawModel model = load.loadObjModel("res/tree.obj",loader);
	ModelTexture texture(loader.loadTexture("res/tree.png"));
	texture.setShineDamper(100);
	texture.setReflectivity(10);
	TexturedModel staticModel(model,texture);
	std::vector<Entity> trees;

	for (int i = 0; i < 100; i++) {
		float posX = (std::rand()) % 1600 - 800;
		float posZ = (std::rand()) % 800;
		float scale = 0.5 + ((std::rand()) % 10) / 10;
		trees.push_back(Entity(staticModel, std::vector<float>{posX, 0.0f, -posZ}, 0, 0, 0, 10*scale));
	}

	Light light(std::vector<float>{3000, 2000, 2000}, std::vector<float>{1.0, 1.0, 1.0});
	ModelTexture tex1 = ModelTexture(loader.loadTexture("res/grass.png"));
	ModelTexture tex2 = ModelTexture(loader.loadTexture("res/grass.png"));
	Terrain terrain(0, -1, loader, tex1);
	Terrain terrain2(-1, -1, loader, tex2);

	Camera camera;
	MasterRenderer renderer;

	while (display.isCloseRequested()) {
		camera.move();
		renderer.processTerrain(terrain);
		renderer.processTerrain(terrain2);
		for(Entity entity: trees)
			renderer.processEntity(entity);
		renderer.render(light, camera);
		display.updateDisplay();
	}
	renderer.cleanUp();
	loader.cleanUp();
	display.closeDisplay();
}