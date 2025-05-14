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

#include "header.h"
#include "Camera.h"
RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Init()
{
	const char* vsFile_2D = "vertex.vert";
	const char* fsFile_2D = "fragment.frag";
		
	const char* vsFile_3D = "vertex3d.vert";
	const char* fsFile_3D = "fragment3d.frag";

	for (int i = 0;i<int(SHADER_REF::SHADER_REF_LAST);i++)
	{
		Shader* shdr = new Shader;
		m_vShdr.push_back(shdr);
	}

	m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->CreateShaderProgramFromFiles(vsFile_2D, fsFile_2D);
	m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->CreateShaderProgramFromFiles(vsFile_3D, fsFile_3D);

	m_pCam = new Camera;
	glEnable(GL_CULL_FACE);// 컬링 기능 활성화
	glCullFace(GL_BACK); // 뒷면 제거
	glFrontFace(GL_CCW); // 반시계 방향을 앞면으로 간주
	glEnable(GL_DEPTH_TEST);
}

#include "FrameBuffer.h"
void RenderManager::Draw()
{			
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	auto shdr_handle_2D = m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->GetShaderProgramHandle();
	auto shadr_handle_3D= m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->GetShaderProgramHandle();


	glEnable(GL_DEPTH_TEST);
	m_pCam->Update();
	for (auto obj : objs)
	{
		if (obj->GetActive())
		{
			auto model = obj->GetModel();

			if (model && !obj->GetIs3D())
			{
				m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Use();

				//OpenGL에서 셰이더 프로그램 안에 있는 유니폼 변수의 위치(주소)를 얻는 함수
				GLint MVP_Location = glGetUniformLocation(shdr_handle_2D, "uMVP_2d");
				assert(MVP_Location >= 0);

				Transform* trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
				assert(trs != nullptr);

				GLint ColorLocation = glGetUniformLocation(shdr_handle_2D, "uColor_2d");
				assert(ColorLocation >= 0);

				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				assert(spr != nullptr);

				glm::mat4 m2w = trs->GetModelToWorld_Matrix();
				glm::vec4 color = spr->GetColor();

				glm::mat4 proj = m_pCam->GetProjMatrix();
				glm::mat4 view = m_pCam->GetViewMatrix();
				glm::mat4 MVP = proj * view * m2w;

				//셰이더한테 이 4x4 행렬 좀 써줘 라는 함수
				//GL_FALSE - Column major로 인식해라 			
				glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));
				glUniform4fv(ColorLocation, 1, glm::value_ptr(color));

				//Draw
				model->Draw();

				m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Diuse();
			}
			else if (model && obj->GetIs3D())
			{
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				//OpenGL에서 셰이더 프로그램 안에 있는 유니폼 변수의 위치(주소)를 얻는 함수
				GLint MVP_Location = glGetUniformLocation(shadr_handle_3D, "uMVP");
				assert(MVP_Location >= 0);

				Transform* trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
				assert(trs != nullptr);

				//GLint ColorLocation = glGetUniformLocation(shadr_handle_3D, "uColor");
				//assert(ColorLocation >= 0);

				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				assert(spr != nullptr);

				glm::mat4 m2w = trs->GetModelToWorld_Matrix();

				glm::mat4 proj = m_pCam->GetProjMatrix();
				glm::mat4 view = m_pCam->GetViewMatrix();
				glm::mat4 MVP = proj * view * m2w;
				glm::vec4 color = spr->GetColor();

				glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));
				//glUniform4fv(ColorLocation, 1, glm::value_ptr(color));

				//Draw
				model->Draw();

				//last
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();
			}
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
	delete m_pCam;
	delete m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)];
	delete m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)];
}
