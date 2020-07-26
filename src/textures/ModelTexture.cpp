#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id) {
	ModelTexture::textureID = id;
	shineDamper = 1;
	reflectivity = 0;
	hasTransparency = false;
	useFakeLighting = false;
}

ModelTexture::ModelTexture() {
	hasTransparency = false;
	useFakeLighting = false;
}

void ModelTexture::setShineDamper(float damper) {
	shineDamper = damper;
}

void ModelTexture::setReflectivity(float reflect) {
	reflectivity = reflect;
}