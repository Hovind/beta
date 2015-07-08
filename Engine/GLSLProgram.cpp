#include "GLSLProgram.h"
#include "MyException.h"

#include <fstream>

namespace Engine{
	GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath) {
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (!_vertexShaderID)
			throw MyException("Vertex shader failed to be created!");

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
			throw MyException("Fragment shader failed to be created!");
		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilepath, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders() {
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		GLint success = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&success);
		if (success == GL_FALSE)
			throw MyException("Shaders failed to link!");

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);

		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}


	GLuint GLSLProgram::getUniformLocation(const std::string &uniformName){
		GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			throw MyException("Uniform " + uniformName + " not found in shader!");
		else
			return location;
	}


	void GLSLProgram::use() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; ++i) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; ++i) {
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
		std::ifstream shaderFile(filePath);
		if (!shaderFile)
			throw MyException("Failed to open " + filePath);

		std::string fileContents,
					line;

		while (getline(shaderFile, line)) {
			fileContents += line + '\n';
		}

		shaderFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
			throw MyException("Shader " + filePath + " failed to compile");
	}
}