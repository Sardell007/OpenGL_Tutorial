#pragma once
#include<string>

class ModelTexture {
private:
	unsigned int textureID;
	float shineDamper;
	float reflectivity;
	//std::string m_FilePath;
	//unsigned char* m_LocalBuffer;
	//int m_Width, m_Height, m_BPP;
public:
	ModelTexture(unsigned int id);
	ModelTexture();

	//void Bind(unsigned int slot = 0) const;
	//void Unbind();

	inline int getID() const { return textureID; };
	inline float getShineDamper() const { return shineDamper; };
	inline float getReflectivity() const { return reflectivity; };
	void setShineDamper(float damper);
	void setReflectivity(float reflect);
	//inline int getWidth() const { return m_Width; }
	//inline int getHeight() const { return m_Height; }
};