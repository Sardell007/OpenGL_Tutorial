#pragma once
#include "ShaderProgram.h"
#include <Entity/Camera.h>
#include <toolbox/Maths.h>
#include <Entity/Light.h>

class StaticShader: public ShaderProgram {
public :
	StaticShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera &camera);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadLight(Light &light);
	void loadShineVariables(float damper, float reflectivity);
	void bindAttributes();
	void getAllUniformLocations();
};