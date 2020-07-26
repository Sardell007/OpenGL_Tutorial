#include "StaticShader.h"
#include <iostream>

std::string VERTEX_FILE_S = "src/shaders/vertexShader.txt";
std::string FRAGMENT_FILE_S = "src/shaders/fragmentShader.txt";

int location_transformationMatrix_s;
int location_projectionMatrix_s;
int location_viewMatrix_s;
int location_lightPosition_s;
int location_lightColour_s;
int location_shineDamper_s;
int location_reflectivity_s;
int location_useFakeLighting_s;
int location_skyColour_s;

void StaticShader::bindAttributes() {
	bindAttribute(0, "positions");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations() {
	location_transformationMatrix_s = getUniformLocation("transformationMatrix");
	location_projectionMatrix_s = getUniformLocation("projectionMatrix");
	location_viewMatrix_s = getUniformLocation("viewMatrix");
	location_lightPosition_s = getUniformLocation("lightPosition");
	location_lightColour_s = getUniformLocation("lightColour");
	location_shineDamper_s = getUniformLocation("shineDamper");
	location_reflectivity_s = getUniformLocation("reflectivity");
	location_useFakeLighting_s = getUniformLocation("useFakeLighting");
	location_skyColour_s = getUniformLocation("skyColour");
}

void StaticShader::loadFakeLightingVariable(bool useFake) {
	loadBoolean(location_useFakeLighting_s, useFake);
}

void StaticShader::loadSkyColour(float r, float g, float b) {
	loadVector(location_skyColour_s, std::vector<float>{r, g, b});
}

StaticShader::StaticShader():ShaderProgram(VERTEX_FILE_S, FRAGMENT_FILE_S)
{
	StaticShader::bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	getAllUniformLocations();
}


void StaticShader::loadShineVariables(float damper, float reflectivity) {
	loadFloat(location_shineDamper_s, damper);
	loadFloat(location_reflectivity_s, reflectivity);
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
	loadMatrix(location_transformationMatrix_s, matrix);
}

void StaticShader::loadViewMatrix(Camera &camera) {
	glm::mat4 viewMatrix = Maths().createViewMatrix(camera);
	loadMatrix(location_viewMatrix_s, viewMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
	loadMatrix(location_projectionMatrix_s, matrix);
}

void StaticShader::loadLight(Light &light) {
	loadVector(location_lightPosition_s, light.getPosition());
	loadVector(location_lightColour_s, light.getColour());
}