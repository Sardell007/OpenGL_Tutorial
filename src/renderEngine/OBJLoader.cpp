#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> split(std::string s, char tok) {
	std::vector<std::string> strings;
	std::string temp = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == tok) {
			strings.push_back(temp);
			temp = "";
		}
		else {
			temp += s[i];
		}
	}
	if (temp != "")strings.push_back(temp);
	return strings;
}

RawModel OBJLoader::loadObjModel(std::string filename, Loader &loader) {
	std::ifstream stream(filename);
	std::string line;

	std::vector<std::vector<float>> verticies;
	std::vector<std::vector<float>> textures;
	std::vector<std::vector<float>> normals;
	std::vector<int> indicies;

	std::vector<float> verticiesArray;
	std::vector<float> normalsArray;
	std::vector<float> textureArray;

	while (true) {
		getline(stream, line);
		std::vector<std::string> currentLine = split(line,' ');
		if (line.find("v ") == 0) {
			std::vector<float> vertex{std::stof(currentLine[1]),std::stof(currentLine[2]) ,std::stof(currentLine[3])};
			verticies.push_back(vertex);
		}
		else if (line.find("vt ") == 0) {
			std::vector<float> texture{ std::stof(currentLine[1]),std::stof(currentLine[2])};
			textures.push_back(texture);
		}
		else if (line.find("vn ") == 0) {
			std::vector<float> normal{ std::stof(currentLine[1]),std::stof(currentLine[2]) ,std::stof(currentLine[3]) };
			normals.push_back(normal);
		}
		else if (line.find("f ") == 0) {
			textureArray = std::vector<float>(verticies.size() * 2);
			normalsArray = std::vector<float>(verticies.size() * 3);
			break;
		}
	}

	while (line != "") {
		if (line.find("f ") != 0) {
			getline(stream, line);
			continue;
		}
		std::vector<std::string> currentLine = split(line,' ');
		std::vector<std::string> vertex1 = split(currentLine[1], '/');
		std::vector<std::string> vertex2 = split(currentLine[2], '/');
		std::vector<std::string> vertex3 = split(currentLine[3], '/');
		processVertex(vertex1, indicies, textures, normals, textureArray, normalsArray);
		processVertex(vertex2, indicies, textures, normals, textureArray, normalsArray);
		processVertex(vertex3, indicies, textures, normals, textureArray, normalsArray);
		getline(stream, line);
	}

	stream.close();

	verticiesArray = std::vector<float>(verticies.size() * 3);

	int vertexPointer = 0;
	for (std::vector<float> vertex : verticies) {
		verticiesArray[vertexPointer++] = vertex[0];
		verticiesArray[vertexPointer++] = vertex[1];
		verticiesArray[vertexPointer++] = vertex[2];
	}

	return loader.loadToVAO(verticiesArray, textureArray, normalsArray, indicies);

}

void OBJLoader::processVertex(std::vector<std::string> &vertexData, std::vector<int> &indices,
	std::vector<std::vector<float>> &textures, std::vector<std::vector<float>> &normals, std::vector<float> &textureArray,
	std::vector<float> &normalArray) {
	int currentVertexPointer = std::stoi(vertexData[0]) - 1;
	indices.push_back(currentVertexPointer);
	std::vector<float> currentTex = textures[std::stoi(vertexData[1]) - 1];
	textureArray[currentVertexPointer * 2] = currentTex[0];
	textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex[1];
	std::vector<float> currentNorm = normals[std::stoi(vertexData[2]) - 1];
	normalArray[currentVertexPointer * 3] = currentNorm[0];
	normalArray[currentVertexPointer * 3 + 1] = currentNorm[1];
	normalArray[currentVertexPointer * 3 + 2] = currentNorm[2];	   	 
}