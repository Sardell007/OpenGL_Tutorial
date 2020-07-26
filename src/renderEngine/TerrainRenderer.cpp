#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix) {
	TerrainRenderer::shader = shader;
	TerrainRenderer::shader.start();
	TerrainRenderer::shader.loadProjectionMatrix(projectionMatrix);
	TerrainRenderer::shader.stop();
}

TerrainRenderer::TerrainRenderer() {

}

void TerrainRenderer::renderer(std::vector<Terrain> &terrains) {
	for (Terrain terrain : terrains) {
		prepareTerrain(terrain);
		//loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES,terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain &terrain) {
	RawModel rawModel = terrain.getModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	loadModelMatrix(terrain);
	ModelTexture texture = terrain.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
}

void TerrainRenderer::unbindTexturedModel() {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain& terrain) {
	glm::mat4 transformationatrix = Maths().createTransformationMatrix(std::vector<float>{terrain.getX(), 0, terrain.getZ()},
		0, 0, 0, 1);
	shader.loadTransformationMatrix(transformationatrix);
}