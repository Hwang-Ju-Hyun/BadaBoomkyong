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
#include "Animator.h"
#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Collider.h"
#endif // DEBUG
#include "header.h"
#include "Camera.h"
#include "Mesh.h"
#include "Monster.h"
#include <iostream>
#include "Material.h"

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{

}

GLuint RenderManager::GetDebugLineShader() const
{
	return m_debugLineShader ? m_debugLineShader->GetShaderProgramHandle() : 0;
}

void RenderManager::InitDebugLineShader()
{
	Shader* debugLineShader = new Shader();
	debugLineShader->CreateShaderProgramFromFiles("line.vert", "line.frag");
	m_debugLineShader = debugLineShader;
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

void RenderManager::BeforeDraw()
{
	m_vTransParnetObject.clear();
	m_vOpaqueObject.clear();

	auto objs = GameObjectManager::GetInstance()->GetAllObjects();
	for (const auto& obj : objs)
	{
		Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
		for (int i = 0;i < obj->GetModel()->GetMeshes().size();i++)
		{
			Material* mat = obj->GetModel()->GetMeshes()[i]->GetMaterial();
			if (mat)
			{				
				if (mat->GetHasAlphaChannel())
				{
					m_vTransParnetObject.push_back(obj);
				}
				else
				{
					m_vOpaqueObject.push_back(obj);
				}
			}			
			else if (mat == nullptr && spr)
			{
				if (obj->GetModel()->GetModelType() == MODEL_TYPE::PLANE)
				{
					if(spr->GetTexture())
						m_vTransParnetObject.push_back(obj);
					else
						m_vOpaqueObject.push_back(obj);
				}
				else 
				{
					m_vOpaqueObject.push_back(obj);
				}
			}
		}
	}
}
#include "Player.h"
void RenderManager::Draw()
{			
	auto objs=GameObjectManager::GetInstance()->GetAllObjects();
	auto shdr_handle_2D = m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->GetShaderProgramHandle();
	auto shdr_handle_3D= m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->GetShaderProgramHandle();
		
	Transform* obj_trs = nullptr;
	glEnable(GL_DEPTH_TEST);
	m_pCam->Update();

	BeforeDraw();	

	//1. ������ ���� ������
	for (auto obj : m_vOpaqueObject)
	{
		//todo �̰� transform�� active�̸� ����Ǵ°� �̻��� sprite�� �ϵ簡 �����ʿ���
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);

		if (obj_trs->GetActive())
		{
			Model* model = obj->GetModel();
			bool is3d=obj->GetIs3D();
			if (model && is3d)
			{
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				//OpenGL���� ���̴� ���α׷� �ȿ� �ִ� ������ ������ ��ġ(�ּ�)�� ��� �Լ�
				m_iMVP_Location = glGetUniformLocation(shdr_handle_3D, "uMVP");
				assert(m_iMVP_Location >= 0);

				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				//assert(spr != nullptr);

				m_iUV_Offset_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Offset");
				m_iUV_Scale_Location  = glGetUniformLocation(shdr_handle_3D, "uUV_Scale");

				Animator* anim = dynamic_cast<Animator*>(obj->FindComponent(Animator::AnimatorTypeName));

				m_iHas_texture_location = glGetUniformLocation(shdr_handle_3D, "uHasTexture");
				m_iOut_texture_location = glGetUniformLocation(shdr_handle_3D, "uOutTexture");

				if (!spr)
				{
					for (auto m : model->GetMeshes())
					{
						if (!m)
							continue;
						if (m->GetMaterial() && m->GetMaterial()->HasTexture())
						{
							GLuint tex_id = m->GetMaterial()->GetTexture()->GetTextureID();
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, tex_id);
							glUniform1i(m_iOut_texture_location, 0);
							//assert(has_texture_location >= 0 && out_texture_location >= 0);							
							glUniform1i(m_iHas_texture_location, true);
						}
						else
						{
							glBindTexture(GL_TEXTURE_2D, 0); // <- ���ε� ���� �߰�
							glUniform1i(m_iHas_texture_location, false); // <- �ݵ�� false ����
						}
						glm::mat4 MVP = GetMVP_ByObject(*obj);					

						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));
						
						m->Draw();
					}
				}
				else if (spr)
				{
					if (spr->GetTexture() != nullptr)
					{
						GLuint tex_id = spr->GetTexture()->GetTextureID();
						glActiveTexture(GL_TEXTURE0); //�ݵ�� ���� 0 Ȱ��ȭ
						glBindTexture(GL_TEXTURE_2D, tex_id); //�ؽ�ó ���ε�
						glUniform1i(m_iOut_texture_location, 0); //���̴����� ����� ���� ����
						glUniform1i(m_iHas_texture_location, true);
					}
					else
					{
						glUniform1i(m_iHas_texture_location, false);
					}
					glm::mat4 MVP = GetMVP_ByObject(*obj);			

					if (anim)
					{
						glUniform2f(m_iUV_Offset_Location, anim->GetAnimation()->m_fSheet_UV_offset_X, anim->GetAnimation()->m_fSheet_UV_offset_Y);
						glUniform2f(m_iUV_Scale_Location, anim->GetAnimation()->m_fSheet_UV_Width, anim->GetAnimation()->m_fSheet_UV_Height);
					}
					else
					{
						glUniform2f(m_iUV_Offset_Location, 0, 0);
						glUniform2f(m_iUV_Scale_Location, 1, 1);
					}

					//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
					// draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
					//GLint IsColliderLocation = glGetUniformLocation(shdr_handle_3D, "uIsCollider");
					glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

					model->Draw();

					//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
					//draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
					Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
					if (col)
					{
						col->DrawCollider();
					}
				}		
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();			
			}
		}
	}

	//����
	for (auto obj : m_vTransParnetObject)
	{
		//todo �̰� transform�� active�̸� ����Ǵ°� �̻��� sprite�� �ϵ簡 �����ʿ���
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);

		if (obj_trs->GetActive())
		{
			Model* model = obj->GetModel();
			bool is3d = obj->GetIs3D();
			if (model && is3d)
			{
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				//OpenGL���� ���̴� ���α׷� �ȿ� �ִ� ������ ������ ��ġ(�ּ�)�� ��� �Լ�
				m_iMVP_Location = glGetUniformLocation(shdr_handle_3D, "uMVP");
				assert(m_iMVP_Location >= 0);

				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				//assert(spr != nullptr);

				m_iUV_Offset_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Offset");
				m_iUV_Scale_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Scale");

				Animator* anim = dynamic_cast<Animator*>(obj->FindComponent(Animator::AnimatorTypeName));

				m_iHas_texture_location = glGetUniformLocation(shdr_handle_3D, "uHasTexture");
				m_iOut_texture_location = glGetUniformLocation(shdr_handle_3D, "uOutTexture");

				if (!spr)
				{
					for (auto m : model->GetMeshes())
					{
						if (!m)
							continue;
						if (m->GetMaterial() && m->GetMaterial()->HasTexture())
						{
							GLuint tex_id = m->GetMaterial()->GetTexture()->GetTextureID();
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, tex_id);
							glUniform1i(m_iOut_texture_location, 0);
							//assert(has_texture_location >= 0 && out_texture_location >= 0);							
							glUniform1i(m_iHas_texture_location, true);
						}
						else
						{
							glBindTexture(GL_TEXTURE_2D, 0); // <- ���ε� ���� �߰�
							glUniform1i(m_iHas_texture_location, false); // <- �ݵ�� false ����
						}
						glm::mat4 MVP = GetMVP_ByObject(*obj);

						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

						m->Draw();
					}
				}
				else if (spr)
				{
					if (spr->GetTexture() != nullptr)
					{
						GLuint tex_id = spr->GetTexture()->GetTextureID();
						glActiveTexture(GL_TEXTURE0); //�ݵ�� ���� 0 Ȱ��ȭ
						glBindTexture(GL_TEXTURE_2D, tex_id); //�ؽ�ó ���ε�
						glUniform1i(m_iOut_texture_location, 0); //���̴����� ����� ���� ����
						glUniform1i(m_iHas_texture_location, true);
					}
					else
					{
						glUniform1i(m_iHas_texture_location, false);
		 			}
					
					//todo : ������ �������� ��������
					glm::mat4 MVP = GetMVP_ByObject(*obj);
					glm::mat4 visualOffset;
					Player* p = dynamic_cast<Player*>(obj->FindComponent(Player::PlayerTypeName));
					bool dashing = p->GetIsDashing();
					if (obj->GetName() == "Player")
					{												
						if (dashing)
						{
							// �ؽ�ó�� ���������� ġ���� ���� ���, ��¦ �������� ���							
							float texture_offsetX = -0.5f; // �� ���⼭ 0.1�� ������ (�ð��� ���� ����)
							visualOffset = glm::translate(glm::mat4(1.f), glm::vec3(texture_offsetX*p->GetDir(), 0.f, 0.f));
						}						
					}					
					glm::mat4 finalMVP = MVP * visualOffset;					
					if (anim)
					{
						float uvLeft = anim->GetAnimation()->m_fSheet_UV_offset_X;
						float uvRight = uvLeft + anim->GetAnimation()->m_fSheet_UV_Width;

						float offsetX = uvLeft;
						float scaleX = anim->GetAnimation()->m_fSheet_UV_Width;

						if (spr && spr->GetIsFlipX())
						{
							offsetX = uvLeft + scaleX;
							scaleX = -scaleX; // ���� �����Ϸ� �¿� ����
						}

						glUniform2f(m_iUV_Offset_Location, offsetX, anim->GetAnimation()->m_fSheet_UV_offset_Y);
						glUniform2f(m_iUV_Scale_Location, scaleX, anim->GetAnimation()->m_fSheet_UV_Height);
					}
					else
					{
						glUniform2f(m_iUV_Offset_Location, 0, 0);
						glUniform2f(m_iUV_Scale_Location, 1, 1);
					}

					if(dashing)
						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(finalMVP));
					else
						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

					model->Draw();

					//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
					//draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
					Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
					if (col)
					{
						col->DrawCollider();
					}
				}
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

	EndDraw();
}

void RenderManager::EndDraw()
{	
	std::vector<GameObject*> TransParent_temp,Opaque_temp;
	TransParent_temp.swap(m_vTransParnetObject);
	Opaque_temp.swap(m_vOpaqueObject);
}

void RenderManager::Exit()
{
	delete m_pCam;
	delete m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)];
	delete m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)];
}

const glm::mat4 RenderManager::GetMVP_ByObject(const GameObject& _obj)
{
	Transform* trs = dynamic_cast<Transform*>(_obj.FindComponent(Transform::TransformTypeName));
	assert(trs != nullptr);

	glm::mat4 m2w = trs->GetModelToWorld_Matrix();
	glm::mat4 proj = m_pCam->GetProjMatrix();
	glm::mat4 view = m_pCam->GetViewMatrix();
	glm::mat4 MVP = proj * view * m2w;
	return MVP;
}


void RenderManager::RenderOpaqueObject()
{
}

void RenderManager::RenderTransParentObject()
{
}