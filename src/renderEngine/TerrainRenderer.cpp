#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix) {
	TerrainRenderer::shader = shader;
	TerrainRenderer::shader.start();
	TerrainRenderer::shader.loadProjectionMatrix(projectionMatrix);
	TerrainRenderer::shader.connectTextureUnits();
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
	bindTexture(terrain);
	shader.loadShineVariables(1, 0);
	
}

void TerrainRenderer::bindTexture(Terrain terrain) {
	TerrainTexturePack texturePack = terrain.getTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackground().getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack.getR().getTextureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack.getG().getTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack.getB().getTextureID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain.getblendMap().getTextureID());

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