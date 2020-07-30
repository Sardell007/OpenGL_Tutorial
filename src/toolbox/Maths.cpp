#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(std::vector<float> translation, float rx, float ry, float rz, float scale) {
	glm::mat4 matrix(1.0f);
	glm::vec3 translate(translation[0], translation[1], translation[2]);
	matrix = glm::translate(matrix, translate);
	matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera camera) {
	glm::mat4 viewMatrix(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	std::vector<float> cameraPos = camera.getPosition();
	glm::vec3 negCameraPos(-cameraPos[0], -cameraPos[1], -cameraPos[2]);
	viewMatrix = glm::translate(viewMatrix, negCameraPos);
	return viewMatrix;
}