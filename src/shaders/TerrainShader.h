#pragma once
#include "ShaderProgram.h"
#include <Entity/Camera.h>
#include <toolbox/Maths.h>
#include <Entity/Light.h>

class TerrainShader: public ShaderProgram {
public:
	TerrainShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera& camera);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadLight(Light &light);
	void loadShineVariables(float damper, float reflectivity);
	void loadSkyColour(float r, float g, float b);
	void bindAttributes();
	void getAllUniformLocations();
	void connectTextureUnits();
//private:
//	std::string VERTEX_FILE;
//	std::string FRAGMENT_FILE;
//	int location_transformationMatrix;
//	int location_projectionMatrix;
//	int location_viewMatrix;
//	int location_lightPosition;
//	int location_lightColour;
//	int location_shineDamper;
//	int location_reflectivity;
};