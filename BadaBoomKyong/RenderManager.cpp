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
	glEnable(GL_CULL_FACE);// �ø� ��� Ȱ��ȭ
	glCullFace(GL_BACK); // �޸� ����
	glFrontFace(GL_CCW); // �ݽð� ������ �ո����� ����
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
		//todo �̰� transform�� active�̸� ����Ǵ°� �̻��� sprite�� �ϵ簡 �����ʿ���
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);
		if (obj_trs->GetActive())
		{
			auto model = obj->GetModel();

			if (model && !obj->GetIs3D())
			{
				m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Use();		
				//OpenGL���� ���̴� ���α׷� �ȿ� �ִ� ������ ������ ��ġ(�ּ�)�� ��� �Լ�
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

				//���̴����� �� 4x4 ��� �� ���� ��� �Լ�
				//GL_FALSE - Column major�� �ν��ض� 			
				glUniformMatrix4fv(MVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));
				glUniform4fv(ColorLocation, 1, glm::value_ptr(color));

				//Draw
				model->Draw();

				m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Diuse();
			}
			else if (model && obj->GetIs3D())
			{				
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				//OpenGL���� ���̴� ���α׷� �ȿ� �ִ� ������ ������ ��ġ(�ּ�)�� ��� �Լ�
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
							//glBindTexture(GL_TEXTURE_2D, 0); // <- ���ε� ���� �߰�
							//glUniform1i(has_texture_location, false); // <- �ݵ�� false ����
						}
						glm::mat4 m2w = trs->GetModelToWorld_Matrix();
						glm::mat4 proj = m_pCam->GetProjMatrix();
						glm::mat4 view = m_pCam->GetViewMatrix();
						glm::mat4 MVP = proj * view * m2w;
						glm::vec4 color;
						if (spr)
							color = spr->GetColor();


						//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
						// draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
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
						glActiveTexture(GL_TEXTURE0); //�ݵ�� ���� 0 Ȱ��ȭ
						glBindTexture(GL_TEXTURE_2D, tex_id); //�ؽ�ó ���ε�
						glUniform1i(out_texture_location, 0); //���̴����� ����� ���� ����
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


					//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
					// draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
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


				//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
				// draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
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
