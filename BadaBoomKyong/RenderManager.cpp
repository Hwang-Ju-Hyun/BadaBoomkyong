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
	const char* vsFile = "vertex.vert";
	const char* fsFile = "fragment.frag";

	shdr = new Shader;	

	shdr->CreateShaderProgramFromFiles(vsFile, fsFile);
}

void RenderManager::Draw()
{		
	std::vector<Model*> models=ModelManager::GetInstance()->GetAllModels();
	auto shdr_handle = shdr->GetShaderProgramHandle();
	
	shdr->Use();

	for (auto model : models)
	{
		if(model->GetModelType()==MODEL_TYPE::RECTANGLE)
			model->Draw();
	}

	shdr->Diuse();

	auto handle=Window::GetInstance()->GetWindowHandle();
	glfwSwapBuffers(handle);
	glfwPollEvents();
	
}

void RenderManager::Exit()
{
	delete shdr;
}
