#include <fstream>
#include <stdio.h>
#include <GL/glew.h>
#include "Shader.h"
#include <cassert>

Shader::Shader()
	:m_uShaderProgramHandle(0)
{
}

Shader::~Shader()
{
}

std::string Shader::ReadShaderFile(const char* _filePath)
{
	std::string content;
	std::ifstream fileStream(_filePath, std::ios::in);	
	while (!fileStream.is_open())
	{		
		std::string filePath =_filePath;
		throw std::runtime_error("Error : can't open file" + filePath);
	}
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();
	return content;
}

GLuint Shader::AddShader(const char* _shaderCode, GLenum _shaderType)
{
	//셰이더 프로그램과 연결할 셰이더를 생성하며 그 ID를 반환해주고
	GLuint new_shader = glCreateShader(_shaderType);
	const GLchar* code[1];
	code[0] = _shaderCode;
	
	//직접 작성한 셰이더 코드를 glCreateShader를 통해 만든 셰이더에 연결해야함
	glShaderSource(new_shader, 1, code, nullptr);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	//셰이더 코드를 컴파일
	glCompileShader(new_shader);

	//셰이더 코드의 상태를 마지막 인자인 포인터 변수를 통해 반환하는 함수
	glGetShaderiv(new_shader,GL_COMPILE_STATUS,&result);
	if (!result)
	{
		glGetShaderInfoLog(new_shader, sizeof(err_log), nullptr, err_log);
		printf("Error compiling the %d shader : '%s'\n",_shaderType, err_log);
		return 0;
	}
	return new_shader;
}

void Shader::CompileShader(const char* _vsCode, const char* _fsCode)
{
	GLuint vs, fs;
	// 셰이더 프로그램을 생성하고 그 ID를 반환하는 OpenGL 함수
	m_uShaderProgramHandle = glCreateProgram();

	if (!m_uShaderProgramHandle)
	{	
		throw std::runtime_error("Cannot create shader program");
		return;
	}
	vs = AddShader(_vsCode, GL_VERTEX_SHADER);
	fs = AddShader(_fsCode, GL_FRAGMENT_SHADER);
	
	glAttachShader(m_uShaderProgramHandle, vs);
	glAttachShader(m_uShaderProgramHandle, fs);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glLinkProgram(m_uShaderProgramHandle);
	glGetProgramiv(m_uShaderProgramHandle, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_uShaderProgramHandle, sizeof(err_log), nullptr, err_log);
		printf("Error linking program : '%s'\n", err_log);
		return;
	}
}

void Shader::CreateShaderProgramFromFiles(const char* _vsPath, const char* _fsPath)
{
	const std::string vsFile = ReadShaderFile(_vsPath);
	const std::string fsFile = ReadShaderFile(_fsPath);
	const char* vsCode = vsFile.c_str();
	const char* fsCode = fsFile.c_str();

	CompileShader(vsCode, fsCode);
}

void Shader::Use()
{		
	glUseProgram(m_uShaderProgramHandle);
}

void Shader::Diuse()
{
	glUseProgram(0);
}
