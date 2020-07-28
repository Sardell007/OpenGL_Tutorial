#pragma once
#include<string>
#include<vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile);
    ShaderProgram();
    void start();
    void stop();
    void cleanUp();
    void bindAttribute(unsigned int attribute, std::string variableName);
    virtual void bindAttributes();
    virtual void getAllUniformLocations();
	void loadInt(int location, int value);
    unsigned int programID;
private:
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int loadShader(std::string &file, unsigned int type);
protected:
    int getUniformLocation(std::string uniforName);
	void loadShineVariables(float damper, float reflectivity);
    void loadFloat(int location, float value);
    void loadVector(int location, std::vector<float> vector);
    void loadBoolean(int location, bool value);
    void loadMatrix(int location, glm::mat4& matrix);
};
