#include "TerrainShader.h"
#include "ShaderProgram.h"
#include <iostream>

std::string VERTEX_FILE_T = "src/shaders/terrainVertexShader.txt";
std::string FRAGMENT_FILE_T = "src/shaders/TerrainFragmentShader.txt";

int location_transformationMatrix_t;
int location_projectionMatrix_t;
int location_viewMatrix_t;
int location_lightPosition_t;
int location_lightColour_t;
int location_shineDamper_t;
int location_reflectivity_t;
int location_skyColour_t;

TerrainShader::TerrainShader() :ShaderProgram(VERTEX_FILE_T,FRAGMENT_FILE_T)
{
	bindAttributes();
	glLinkProgram(ShaderProgram::programID);
	glValidateProgram(programID);
	getAllUniformLocations();
}

void TerrainShader::bindAttributes() {
	bindAttribute(0, "positions");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() {
	location_transformationMatrix_t = getUniformLocation("transformationMatrix");
	location_projectionMatrix_t = getUniformLocation("projectionMatrix");
	location_viewMatrix_t = getUniformLocation("viewMatrix");
	location_lightPosition_t = getUniformLocation("lightPosition");
	location_lightColour_t = getUniformLocation("lightColour");
	location_shineDamper_t = getUniformLocation("shineDamper");
	location_reflectivity_t = getUniformLocation("reflectivity");
	location_skyColour_t = getUniformLocation("skyColour");
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
	loadFloat(location_shineDamper_t, damper);
	loadFloat(location_reflectivity_t, reflectivity);
}

void TerrainShader::loadSkyColour(float r, float g, float b) {
	loadVector(location_skyColour_t, std::vector<float>{r, g, b});
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) {
	loadMatrix(location_transformationMatrix_t, matrix);
}

void TerrainShader::loadViewMatrix(Camera& camera) {
	glm::mat4 viewMatrix = Maths().createViewMatrix(camera);
	loadMatrix(location_viewMatrix_t, viewMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 matrix) {
	loadMatrix(location_projectionMatrix_t, matrix);
}

void TerrainShader::loadLight(Light &light) {
	loadVector(location_lightPosition_t, light.getPosition());
	loadVector(location_lightColour_t, light.getColour());
}