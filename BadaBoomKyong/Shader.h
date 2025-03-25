#pragma once
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader();
	~Shader();
private:
	unsigned int m_uiShaderProgramHandle;
public:
	inline unsigned int GetShaderProgramHandle()const { return m_uiShaderProgramHandle; }
public:
	void ReadShaderFile(const char* _filePath);
	void AddShaderFile(const char* _filePath, GLenum _shaderType);
};