#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id) {
	ModelTexture::textureID = id;
	shineDamper = 1;
	reflectivity = 0;
}

ModelTexture::ModelTexture() {
}

void ModelTexture::setShineDamper(float damper) {
	shineDamper = damper;
}

void ModelTexture::setReflectivity(float reflect) {
	reflectivity = reflect;
}