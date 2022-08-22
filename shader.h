#pragma once

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};