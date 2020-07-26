#pragma once
#include "RawModel.h"
#include <textures/ModelTexture.h>

class TexturedModel {
private:
	RawModel rawModel;
	ModelTexture texture;
	static int count;
	static void incCount();
	static int getCount();
	int key;

public:
	int getKey();
	TexturedModel(RawModel &modeli, ModelTexture &texturei);
	TexturedModel();
	inline RawModel getRawModel() const { return rawModel; };
	inline ModelTexture getTexture() const { return texture; };
	//bool operator<(const TexturedModel model) const noexcept{ return count < model.count;	};
};