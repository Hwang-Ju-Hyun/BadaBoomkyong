#include <GL/glew.h>
#include "RenderManager.h"
#include "ModelManager.h"
#include "Model.h"
#include "Shader.h"
#include "window.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Model.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <../GLM/gtc/type_ptr.hpp>
#include "Transform.h"
#include <cassert>

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
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	auto shdr_handle = shdr->GetShaderProgramHandle();		

	for (auto obj : objs)
	{

		shdr->Use();

		auto model = obj->GetModel();		

		if (model)
		{
			//OpenGL���� ���̴� ���α׷� �ȿ� �ִ� ������ ������ ��ġ(�ּ�)�� ��� �Լ�
			GLint uniform_var_loc = glGetUniformLocation(shdr_handle, "uModel_to_NDC");
			assert(uniform_var_loc >= 0);
									
			Transform* trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TypeName));
			assert(trs != nullptr);

			glm::mat3 model_to_ndc = trs->GetModelToNDC_Matrix();

			//���̴����� �� 3x3 ��� �� ���� ��� �Լ�
			glUniformMatrix3fv(uniform_var_loc, 1, GL_FALSE, glm::value_ptr(model_to_ndc));

			//Draw
			model->Draw();	

			shdr->Diuse();
		}
	}	

	auto handle=Window::GetInstance()->GetWindowHandle();
	glfwSwapBuffers(handle);
	glfwPollEvents();
	
}

void RenderManager::Exit()
{
	delete shdr;
}
