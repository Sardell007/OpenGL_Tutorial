#pragma once
#include <Models/RawModel.h>
#include<string>
#include "Loader.h"

class OBJLoader {
public:
	static RawModel loadObjModel(std::string filename, Loader &loader);
private:
	static void processVertex(std::vector<std::string> &vertexData, std::vector<int> &indices,
		std::vector<std::vector<float>> &textures, std::vector<std::vector<float>> &normals, std::vector<float> &textureArray,
		std::vector<float> &normalArray);
};