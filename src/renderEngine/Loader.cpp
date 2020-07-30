#include "Loader.h"

RawModel Loader::loadToVAO(std::vector<float> positions,std::vector<float> textureCoords, std::vector<float> normals,std::vector<int> indices) {
	unsigned int vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3,positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	return RawModel(vaoID, indices.size());
}

int Loader::loadTexture(std::string filename)
{
	unsigned int textureID;
	int img_width, img_height, img_BPP;
	unsigned char* m_LocalBuffer;
	//stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filename.c_str(), &img_width, &img_height, &img_BPP, 4);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	Loader::textures.push_back(textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
	return textureID;
}

int Loader::createVAO() {
	unsigned int vaoID;
	glGenVertexArrays(1,&vaoID);
	Loader::vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(unsigned int attributeNumber,int coordinateSize, std::vector<float> data) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	Loader::vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	float* datai = &data[0];
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), datai, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

void Loader::cleanUp() {
	for (unsigned int vao : Loader::vaos) {
		glDeleteVertexArrays(1,&vao);
	}
	for (unsigned int vbo : Loader::vbos) {
		glDeleteBuffers(1,&vbo);
	}
	for (unsigned int texture : textures) {
		glDeleteTextures(1, &texture);
	}
}

void Loader::bindIndicesBuffer(std::vector<int> indices) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	Loader::vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	int* data = &indices[0];
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), data, GL_STATIC_DRAW);
}