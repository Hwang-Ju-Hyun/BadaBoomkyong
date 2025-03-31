#pragma once
#include <GLFW/glfw3.h>
#include <string>
class Shader
{
public:
	Shader();
	~Shader();
private:
	GLuint m_uShaderProgramHandle;
public:
	inline GLuint GetShaderProgramHandle()const { return m_uShaderProgramHandle; }
public:
	std::string ReadShaderFile(const char* _filePath);
	GLuint AddShader(const char* _shaderCode, GLenum _shaderType);
	void CompileShader(const char* _vsCode, const char* _fsCode);
	void CreateShaderProgramFromFiles(const char* _vsPath, const char* _fsPath);
public:
	void Use();
	void diUse();
};