#include "EntityRenderer.h"

#include<math.h>

float width, height;

EntityRenderer::EntityRenderer(float widthi, float heighti, StaticShader &shader , glm::mat4 projectionMatrix) {
	EntityRenderer::shader = shader;
	width = widthi;
	height = heighti;
	EntityRenderer::shader.start();
	EntityRenderer::shader.loadProjectionMatrix(projectionMatrix);
	EntityRenderer::shader.stop();
}

EntityRenderer::EntityRenderer() {
}

EntityRenderer::EntityRenderer(StaticShader& shader, glm::mat4 projectionMatrix) {
	EntityRenderer::shader = shader;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	EntityRenderer::shader.start();
	EntityRenderer::shader.loadProjectionMatrix(projectionMatrix);
	EntityRenderer::shader.stop();
}

void EntityRenderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

//void EntityRenderer::render(std::vector<Entity> entities) {
//	for (Entity entity : entities) {
//		prepareInstance(entity);
//		glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
//		unbindTexturedModel();
//	}
//}

//void EntityRenderer::render(Entity &entity, StaticShader &shader ) {
//	TexturedModel model = entity.getModel();
//	RawModel rawModel = model.getRawModel();
//	glBindVertexArray(rawModel.getVaoID());
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glm::mat4 transformationatrix = Maths().createTransformationMatrix(entity.getPosition(),
//		entity.getRx(), entity.getRy(), entity.getRz(), entity.getScale());
//	shader.loadTransformationMatrix(transformationatrix);
//	ModelTexture texture = model.getTexture();
//	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
//	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glBindVertexArray(0);
//}

void EntityRenderer::render(std::map<int, std::vector<Entity>> &entities) {
	std::map<int, std::vector<Entity>>::iterator itr;
	for (itr = entities.begin(); itr != entities.end(); itr++) {
		std::vector<Entity> batch = itr->second;
		TexturedModel model = batch[0].getModel();
		prepareTexturedModel(model);
		for (Entity entity : batch) {
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}



void EntityRenderer::prepareTexturedModel(TexturedModel &model) {
	RawModel rawModel = model.getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture texture = model.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void EntityRenderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity& entity) {
	//TexturedModel model = entity.getModel();
	//RawModel rawModel = model.getRawModel();
	//glBindVertexArray(rawModel.getVaoID());
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glm::mat4 transformationatrix = Maths().createTransformationMatrix(entity.getPosition(),
		entity.getRx(), entity.getRy(), entity.getRz(), entity.getScale());
	shader.loadTransformationMatrix(transformationatrix);
	//ModelTexture texture = model.getTexture();
	//shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}
