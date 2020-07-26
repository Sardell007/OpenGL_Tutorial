#pragma once
#include <glm/glm.hpp>
#include <Entity/Camera.h>
#include<vector>
#include <glm/gtc/matrix_transform.hpp>

class Maths {
public:
	static glm::mat4 createTransformationMatrix(std::vector<float> translation, float rx, float ry, float rz, float scale);
	static glm::mat4 createViewMatrix(Camera camera);
};