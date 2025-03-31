#include "RenderManager.h"
#include "ModelManager.h"
#include "Model.h"
#include "Shader.h"
#include "window.h"
RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Init()
{
	const char* vsFile = "shader.vert";
	const char* fsFile = "shader.frag";

	shdr = new Shader;	

	shdr->CreateShaderProgramFromFiles(vsFile, fsFile);
}

void RenderManager::Draw()
{
	
	glClearColor(1.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	auto handle= Window::GetInstance()->GetWindowHandle();

	std::vector<Model*> models=ModelManager::GetInstance()->GetAllModels();
	auto shdr_handle = shdr->GetShaderProgramHandle();
	shdr->Use();
	for (auto model : models)
	{
		model->Draw();
	}
	glfwSwapBuffers(handle);
	glfwPollEvents();
	shdr->diUse();
}
