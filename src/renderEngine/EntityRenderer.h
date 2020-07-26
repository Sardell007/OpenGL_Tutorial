#pragma once
#include <Models/RawModel.h>
#include <Models/TexturedModel.h>
#include <Entity/Entity.h>
#include <shaders/StaticShader.h>
#include <toolbox/Maths.h>
#include <GL/glew.h>
#include "DisplayManager.h"
#include <map>
//#include "MasterRenderer.h"

class EntityRenderer {
private:
	StaticShader shader;
	void prepareTexturedModel(TexturedModel &model);
	void unbindTexturedModel();
	void prepareInstance(Entity &entity);
public:
	EntityRenderer(float widthi, float heighti, StaticShader &shader, glm::mat4 projectionMatrix);
	EntityRenderer(StaticShader& shader, glm::mat4 projectionMatrix);
	EntityRenderer();
	void prepare();
	//void render(std::vector<Entity> entities);
	//void render(Entity &entity, StaticShader &shader);
	void render(std::map<int, std::vector<Entity>> &entities);
};