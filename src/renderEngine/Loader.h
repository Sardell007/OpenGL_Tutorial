#pragma once
#include <vector>
#include <string>
#include <Models/RawModel.h>
#include <GL/glew.h>
#include <stb_image/stb_image.h>

class Loader {
public :
	RawModel loadToVAO(std::vector<float> positions,std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices);
	int loadTexture(std::string filename);
	void cleanUp();
private:
	int createVAO();
	void storeDataInAttributeList(unsigned int attributeNumber,int coordinateSize, std::vector<float> data);
	void unbindVAO();
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> textures;
	void bindIndicesBuffer(std::vector<int> indices);
};