#pragma once

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4x4(const std::string& name, const glm::mat4x4& value) const;
};