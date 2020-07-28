#include "ShaderProgram.h"

#include<fstream>
#include<sstream>
#include<iostream>

ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile) {
    //base = &prog;
    ShaderProgram::vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    ShaderProgram::fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    ShaderProgram::programID = glCreateProgram();
    glAttachShader(ShaderProgram::programID, ShaderProgram::vertexShaderID);
    glAttachShader(ShaderProgram::programID, ShaderProgram::fragmentShaderID);
    //bindAttributes();
    //glLinkProgram(ShaderProgram::programID);
    //glValidateProgram(programID);
    //getAllUniformLocations();
}

ShaderProgram::ShaderProgram() {
}

int ShaderProgram::getUniformLocation(std::string uniformName) {
    return glGetUniformLocation(programID, uniformName.c_str());
}

void ShaderProgram::bindAttribute(unsigned int attribute, std::string variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
}

void ShaderProgram::bindAttributes() {
    std::cout << "Bind program from ShaderProgram" << std::endl;
}

void ShaderProgram::getAllUniformLocations() {
    std::cout << "gellalluniforms program from ShaderProgram" << std::endl;
}

void ShaderProgram::loadInt(int location, int value) {
    glUniform1i(location, value);
}

void ShaderProgram::loadFloat(int location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, std::vector<float> vector) {
    glUniform3f(location, vector[0], vector[1], vector[2]);
}

void ShaderProgram::loadBoolean(int location, bool value) {
    float toLoad = 0;
    if (value) toLoad = 1;
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(int location, glm::mat4& matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::start() {
    glUseProgram(ShaderProgram::programID);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

unsigned int ShaderProgram::loadShader(std::string &file, unsigned int type) {
	std::ifstream  stream(file);

	std::string line;
	std::stringstream ss;

    while (getline(stream, line)) {
                ss<< line << '\n';
    }
    
    unsigned int ShaderID = glCreateShader(type);
    std::string sS = ss.str();
    const char* src = sS.c_str();
    glShaderSource(ShaderID, 1, &src, NULL);
    glCompileShader(ShaderID);

    int result;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(ShaderID, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(ShaderID);
        return 0;
    }

    return ShaderID;
}
