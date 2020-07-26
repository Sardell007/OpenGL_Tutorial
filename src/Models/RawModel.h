#pragma once

class RawModel {
private:
	unsigned int vaoID;
	unsigned int vertexCount;
public:
	RawModel(unsigned int vaoIDi, unsigned int vertexCounti);
	RawModel();
	~RawModel();
	unsigned int getVaoID();
	unsigned int getVertexCount();
};