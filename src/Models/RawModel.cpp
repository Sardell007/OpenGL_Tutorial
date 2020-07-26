#include "RawModel.h"

RawModel::RawModel(unsigned int vaoIDi, unsigned int vertexCounti ) {
	RawModel::vaoID = vaoIDi;
	RawModel::vertexCount = vertexCounti;
}

RawModel::RawModel() {

}

RawModel::~RawModel() {

}

unsigned int RawModel::getVaoID() {
	return RawModel::vaoID;
}

unsigned int RawModel::getVertexCount() {
	return RawModel::vertexCount;
}