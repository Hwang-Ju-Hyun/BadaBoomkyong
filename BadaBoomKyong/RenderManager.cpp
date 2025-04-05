#include "RenderManager.h"
#include "ModelManager.h"
#include "Model.h"
#include "Shader.h"
#include "window.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Model.h"

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
	//std::vector<Model*> models=ModelManager::GetInstance()->GetAllModels();
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	auto shdr_handle = shdr->GetShaderProgramHandle();
	
	shdr->Use();

	for (auto obj : objs)
	{
		auto model = obj->GetModel();
		if (model)
		{
			model->Draw();
		}
	}

	//shdr->Diuse();

	auto handle=Window::GetInstance()->GetWindowHandle();
	glfwSwapBuffers(handle);
	glfwPollEvents();
	
}

void RenderManager::Exit()
{
	delete shdr;
}
