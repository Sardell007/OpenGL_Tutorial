#include "TexturedModel.h"

int TexturedModel::count;

TexturedModel::TexturedModel(RawModel &modeli, ModelTexture &texturei) {
	TexturedModel::rawModel = modeli;
	TexturedModel::texture = texturei;
	incCount();
	TexturedModel::key = getCount();
}

TexturedModel::TexturedModel() {
	incCount();
}

void TexturedModel::incCount() {
	TexturedModel::count++;
}

int TexturedModel::getCount() {
	return count;
}

int TexturedModel::getKey() {
	return TexturedModel::key;
}