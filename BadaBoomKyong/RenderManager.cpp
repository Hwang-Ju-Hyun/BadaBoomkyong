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
#include "TextureResource.h"
#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Collider.h"
#endif // DEBUG

#include "header.h"
#include "Camera.h"
#include "Mesh.h"

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

#include "Monster.h"
#include <iostream>
#include "Material.h"
void RenderManager::Draw()
{			
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	auto shdr_handle_2D = m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->GetShaderProgramHandle();
	auto shdr_handle_3D= m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->GetShaderProgramHandle();
	Transform* obj_trs = nullptr;
	glEnable(GL_DEPTH_TEST);
	m_pCam->Update();
	for (auto obj : objs)
	{
		//todo 이거 transform만 active이면 실행되는거 이상함 sprite로 하든가 수정필요함
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);
		if (obj_trs->GetActive())
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
				GLint MVP_Location = glGetUniformLocation(shdr_handle_3D, "uMVP");
				assert(MVP_Location >= 0);
			 
				Transform* trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
				assert(trs != nullptr);		
				
				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				//assert(spr != nullptr);												

				GLint has_texture_location = glGetUniformLocation(shdr_handle_3D, "uHasTexture");
				GLint out_texture_location = glGetUniformLocation(shdr_handle_3D, "uOutTexture");
				static int a = 0;
				if (!spr)
				{
					for (auto m : model->GetMeshes())
					{
						if (!m)						
							continue;
						if (a % 6 == 0)
							int b = 0;
						if (m->GetMaterial() && m->GetMaterial()->HasTexture())
						{
							GLuint tex_id = m->GetMaterial()->GetTexture()->GetTextureID();
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, tex_id);
							glUniform1i(out_texture_location, 0);
							//assert(has_texture_location >= 0 && out_texture_location >= 0);							
							glUniform1i(has_texture_location, true);							
						}
						else
						{
							//glBindTexture(GL_TEXTURE_2D, 0); // <- 바인딩 해제 추가
							//glUniform1i(has_texture_location, false); // <- 반드시 false 세팅
						}
						glm::mat4 m2w = trs->GetModelToWorld_Matrix();
						glm::mat4 proj = m_pCam->GetProjMatrix();
						glm::mat4 view = m_pCam->GetViewMatrix();
						glm::mat4 MVP = proj * view * m2w;
						glm::vec4 color;
						if (spr)
							color = spr->GetColor();


						//todo : 주석처리된거 지우고 충돌체 쉐이더를 통해 그리는거 이것도 쉐이더에서 수정하고 
						// draw collider에도 주석있음 아마 assert주석 처리해놓았을 거임 그것도 지우셈
						//GLint IsColliderLocation = glGetUniformLocation(shdr_handle_3D, "uIsCollider");
						glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));
						//Draw
						//model->Draw();
						m->Draw();						
						//temp
						a++;
					}
					
				}				
				else if (spr)
				{			
					if (spr->GetTexture() != nullptr)
					{
						GLuint tex_id = spr->GetTexture()->GetTextureID();
						glActiveTexture(GL_TEXTURE0); //반드시 유닛 0 활성화
						glBindTexture(GL_TEXTURE_2D, tex_id); //텍스처 바인딩
						glUniform1i(out_texture_location, 0); //셰이더에서 사용할 유닛 지정
						glUniform1i(has_texture_location, true);
					}					
					else
					{
						glUniform1i(has_texture_location, false);
					}
					glm::mat4 m2w = trs->GetModelToWorld_Matrix();
					glm::mat4 proj = m_pCam->GetProjMatrix();
					glm::mat4 view = m_pCam->GetViewMatrix();
					glm::mat4 MVP = proj * view * m2w;
					glm::vec4 color;
					if (spr)
						color = spr->GetColor();


					//todo : 주석처리된거 지우고 충돌체 쉐이더를 통해 그리는거 이것도 쉐이더에서 수정하고 
					// draw collider에도 주석있음 아마 assert주석 처리해놓았을 거임 그것도 지우셈
					//GLint IsColliderLocation = glGetUniformLocation(shdr_handle_3D, "uIsCollider");
					glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

					model->Draw();
				} 
				
				/*glm::mat4 m2w = trs->GetModelToWorld_Matrix();
				glm::mat4 proj = m_pCam->GetProjMatrix();
				glm::mat4 view = m_pCam->GetViewMatrix();
				glm::mat4 MVP = proj * view * m2w;
				glm::vec4 color;
				if(spr)
				 color= spr->GetColor();*/


				//todo : 주석처리된거 지우고 충돌체 쉐이더를 통해 그리는거 이것도 쉐이더에서 수정하고 
				// draw collider에도 주석있음 아마 assert주석 처리해놓았을 거임 그것도 지우셈
				//GLint IsColliderLocation = glGetUniformLocation(shdr_handle_3D, "uIsCollider");
				//glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));				
				//glUniform1i(IsColliderLocation, false); // false

#ifdef _DEBUG
				/*GLint DebugColorLocation = glGetUniformLocation(shdr_handle_3D, "uDebugColor");
				assert(DebugColorLocation >= 0);*/
				 
			
#endif
				//Draw				
				

				//last
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();	
			}
		}		

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
