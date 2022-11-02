#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragPath) {
	std::string vertexCode, fragCode;
	std::ifstream vshaderFile, fshaderFile;
	vshaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fshaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vshaderFile.open(vertexPath);
		fshaderFile.open(fragPath);
		std::stringstream vStream, fStream;
		vStream << vshaderFile.rdbuf();
		fStream << fshaderFile.rdbuf();
		vshaderFile.close();
		fshaderFile.close();
		vertexCode = vStream.str();
		fragCode = fStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << infoLog << '\n';
	}

	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILE FAILED\n" << infoLog << '\n';
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKED FAILED\n" << infoLog << '\n';
	}

	glDeleteProgram(vertexShader);
	glDeleteProgram(fragShader);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4x4(const std::string& name, const glm::mat4x4& value) const {
	unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat3x3(const std::string& name, const glm::mat3x3& value) const {
	unsigned int transformLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix3fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3f(const std::string& name, const glm::vec3& value) const {
	unsigned int vec3loc = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(vec3loc, 1, glm::value_ptr(value));
}