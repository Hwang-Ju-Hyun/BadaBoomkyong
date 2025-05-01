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
#include "Sprite.h"
#include <cassert>

#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Collider.h"
#endif // DEBUG


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
			//OpenGL에서 셰이더 프로그램 안에 있는 유니폼 변수의 위치(주소)를 얻는 함수
			GLint Model_to_NDC_location = glGetUniformLocation(shdr_handle, "uModel_to_NDC");
			assert(Model_to_NDC_location >= 0);

			Transform* trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
			assert(trs != nullptr);

			GLint ColorLocation = glGetUniformLocation(shdr_handle, "uColor");
			assert(ColorLocation >= 0);
			
			Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
			assert(spr != nullptr);

			glm::mat3 model_to_ndc = trs->GetModelToNDC_Matrix();
			glm::vec4 color = spr->GetColor();

			//셰이더한테 이 3x3 행렬 좀 써줘 라는 함수
			//GL_FALSE - Column major로 인식해라 
			glUniformMatrix3fv(Model_to_NDC_location, 1, GL_FALSE, glm::value_ptr(model_to_ndc));
			glUniform4fv(ColorLocation, 1, glm::value_ptr(color));

			//Draw
			model->Draw();	
			
			shdr->Diuse();
		}
#ifdef _DEBUG
		//Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
		//if (col != nullptr)
		//	col->DrawCollider();
#endif
	}		

#ifdef _DEBUG
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

	auto handle=Window::GetInstance()->GetWindowHandle();
	glfwSwapBuffers(handle);	
	
	
}

void RenderManager::Exit()
{
	delete shdr;
}
