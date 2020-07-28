#include "Terrain.h"

const float SIZE = 800;
const int VERTEX_COUNT = 128;

Terrain::Terrain(int gridX, int gridZ, Loader &loader, TerrainTexturePack texturePacki, TerrainTexture blendMapi) {
	Terrain::texturePack = texturePacki;
	Terrain::blendMap = blendMapi; 
	Terrain::x = gridX * SIZE;
	Terrain::z = gridZ * SIZE;
	Terrain::model = generateTerrain(loader);
}

RawModel Terrain::generateTerrain(Loader &loader) {
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals (count * 3);
	std::vector<float> textureCoords (count * 2);
	std::vector<int>indices (6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}