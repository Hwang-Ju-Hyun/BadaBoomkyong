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
#include "GameStateManager.h"
#include "BaseLevel.h"
#include "Collider.h"
#include "CurseDemon.h"
#include "Light.h"

RenderManager::RenderManager()
{	
}

RenderManager::~RenderManager()
{
	delete debugLineShader;
	debugLineShader = nullptr;
}

GLuint RenderManager::GetDebugLineShader() const
{
	return m_debugLineShader ? m_debugLineShader->GetShaderProgramHandle() : 0;
}

void RenderManager::InitDebugLineShader()
{
	debugLineShader = new Shader();
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
	

	//todo : 이거 곧 light manager로 옮기셈
	GameObject* light_obj = GameObjectManager::GetInstance()->FindObject("LightTemp");
	m_pLight = dynamic_cast<Light*>(light_obj->FindComponent(Light::LightTypeName));
	assert(m_pLight != nullptr);

	glEnable(GL_CULL_FACE);// 컬링 기능 활성화
	glCullFace(GL_BACK); // 뒷면 제거
	glFrontFace(GL_CCW); // 반시계 방향을 앞면으로 간주
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
			else if(obj->GetName()=="customModelObj1")
			{
				m_vOpaqueObject.push_back(obj);
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

	//1. 불투명 먼저 렌더링
	for (auto obj : m_vOpaqueObject)
	{
		//todo 이거 transform만 active이면 실행되는거 이상함 sprite로 하든가 수정필요함
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);

		if (obj_trs->GetActive())
		{
			Model* model = obj->GetModel();
			bool is3d = obj->GetIs3D();
			if (model && is3d)
			{
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				m_iMVP_Location = glGetUniformLocation(shdr_handle_3D, "uMVP");
				assert(m_iMVP_Location >= 0);

				m_iM2W_Location = glGetUniformLocation(shdr_handle_3D, "uM2W");
				assert(m_iM2W_Location >= 0);
				glm::mat4 m2w = obj_trs->GetModelToWorld_Matrix();				
				glUniformMatrix4fv(m_iM2W_Location, 1, GL_FALSE, glm::value_ptr(m2w));
				

				//LIGHT
				GLint light_num = 1;
				m_iLightNumber = glGetUniformLocation(shdr_handle_3D, "uLightNumber");			
				glUniform1i(m_iLightNumber, light_num);
				m_iLightColorOn = glGetUniformLocation(shdr_handle_3D, "uLightColorOn");
				glUniform3f(glGetUniformLocation(shdr_handle_3D,"uCameraPosition"),m_pCam->GetCamPosition().x, m_pCam->GetCamPosition().y, m_pCam->GetCamPosition().z);
				
				obj->GetName() == "LightTemp" ? glUniform1i(m_iLightColorOn, true) : glUniform1i(m_iLightColorOn, false);
				
				for (int i = 0;i < light_num;i++)
				{
					const std::string type = "uLight[" + std::to_string(i) + "].type";
					glUniform1i(glGetUniformLocation(shdr_handle_3D, type.c_str()),static_cast<int>(m_pLight->GetType()));

					const std::string position = "uLight[" + std::to_string(i) + "].position";
					const Transform* light_trs = dynamic_cast<Transform*>(m_pLight->GetOwner()->FindComponent(Transform::TransformTypeName));
					const glm::vec3 light_pos = light_trs->GetPosition();
					glUniform3f(glGetUniformLocation(shdr_handle_3D, position.c_str()), light_pos.x, light_pos.y, light_pos.z);

					const std::string ambient = "uLight[" + std::to_string(i) + "].ambient";
					glUniform3f(glGetUniformLocation(shdr_handle_3D, ambient.c_str()), m_pLight->GetAmbient().x, m_pLight->GetAmbient().y, m_pLight->GetAmbient().z);					

					const std::string diffuse = "uLight[" + std::to_string(i) + "].diffuse";
					glUniform3f(glGetUniformLocation(shdr_handle_3D, diffuse.c_str()), m_pLight->GetDiffuse().x, m_pLight->GetDiffuse().y, m_pLight->GetDiffuse().z);

					const std::string specular = "uLight[" + std::to_string(i) + "].specular";
					glUniform3f(glGetUniformLocation(shdr_handle_3D, specular.c_str()), m_pLight->GetSpecular().x, m_pLight->GetSpecular().y, m_pLight->GetSpecular().z);

					const std::string direction = "uLight[" + std::to_string(i) + "].direction";
					glUniform3f(glGetUniformLocation(shdr_handle_3D, direction.c_str()), m_pLight->GetDirection().x, m_pLight->GetDirection().y, m_pLight->GetDirection().z);

					const std::string cufotff_angle = "uLight[" + std::to_string(i) + "].cutoffangle";
					glUniform1f(glGetUniformLocation(shdr_handle_3D, cufotff_angle.c_str()),m_pLight->GetCutoffAngle());
				}

				for (int i = 0;i < model->GetMeshes().size();i++)
				{
					Material* mat = model->GetMeshes()[i]->GetMaterial();
					if (mat)
					{												
						glUniform3f(glGetUniformLocation(shdr_handle_3D, "uMp_Ambient"), mat->GetAmbient().x, mat->GetAmbient().y, mat->GetAmbient().z);
						glUniform3f(glGetUniformLocation(shdr_handle_3D, "uMp_Diffuse"), mat->GetDiffuse().x, mat->GetDiffuse().y, mat->GetDiffuse().z);
						glUniform3f(glGetUniformLocation(shdr_handle_3D, "uMp_Specular"), mat->GetSpecular().x, mat->GetSpecular().y, mat->GetSpecular().z);
						glUniform1f(glGetUniformLocation(shdr_handle_3D, "uShininess"), mat->GetShininess());
					}
				}


				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				m_iUV_Offset_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Offset");
				m_iUV_Scale_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Scale");

				Animator* anim = dynamic_cast<Animator*>(obj->FindComponent(Animator::AnimatorTypeName));

				m_iHas_texture_location = glGetUniformLocation(shdr_handle_3D, "uHasTexture");
				m_iOut_texture_location = glGetUniformLocation(shdr_handle_3D, "uOutTexture");				
				m_iHurtEffect_location = glGetUniformLocation(shdr_handle_3D, "uHurtEffect");
				glUniform1i(m_iHurtEffect_location, false);				

				if (!spr)
				{
					for (auto m : model->GetMeshes())
					{
						if (!m)
							continue;

						bool has_texture = false;

						if (m->GetMaterial() && m->GetMaterial()->HasTexture())
						{
							has_texture = true;
							GLuint tex_id = m->GetMaterial()->GetTexture()->GetTextureID();
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, tex_id);
							glUniform1i(m_iOut_texture_location, 0);
							glUniform1i(m_iHas_texture_location, true);
						}
						else
						{
							glBindTexture(GL_TEXTURE_2D, 0);
							glUniform1i(m_iHas_texture_location, false);
						}

						
						glUniform2f(m_iUV_Offset_Location, 0, 0);
						glUniform2f(m_iUV_Scale_Location, 1, 1);
						glm::mat4 MVP = GetMVP_ByObject(*obj);
						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

						m->Draw();
#ifdef _DEBUG
						Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
						if (col)
						{
							col->DrawCollider();
						}
#endif
					}
				}
				else if (spr)
				{
					bool has_texture = false;

					if (spr->GetTexture() != nullptr)
					{
						has_texture = true;
						GLuint tex_id = spr->GetTexture()->GetTextureID();
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, tex_id);
						glUniform1i(m_iOut_texture_location, 0);
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

					glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

					model->Draw();
#ifdef _DEBUG
					Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
					if (col)
					{
						col->DrawCollider();
					}
#endif
				}
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();
			}
		}
	}

	//투명
	for (auto obj : m_vTransParnetObject)
	{
		//todo 이거 transform만 active이면 실행되는거 이상함 sprite로 하든가 수정필요함
		obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		assert(obj_trs != nullptr);

		if (obj_trs->GetActive())
		{
			Model* model = obj->GetModel();
			bool is3d = obj->GetIs3D();
			if (model && is3d)
			{
				m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Use();

				//OpenGL에서 셰이더 프로그램 안에 있는 유니폼 변수의 위치(주소)를 얻는 함수
				m_iMVP_Location = glGetUniformLocation(shdr_handle_3D, "uMVP");
				assert(m_iMVP_Location >= 0);

				Sprite* spr = dynamic_cast<Sprite*>(obj->FindComponent(Sprite::SpriteTypeName));
				//assert(spr != nullptr);

				m_iUV_Offset_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Offset");
				m_iUV_Scale_Location = glGetUniformLocation(shdr_handle_3D, "uUV_Scale");

				Animator* anim = dynamic_cast<Animator*>(obj->FindComponent(Animator::AnimatorTypeName));

				m_iHas_texture_location = glGetUniformLocation(shdr_handle_3D, "uHasTexture");
				m_iOut_texture_location = glGetUniformLocation(shdr_handle_3D, "uOutTexture");
				m_iHurtEffect_location = glGetUniformLocation(shdr_handle_3D, "uHurtEffect");

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
							glBindTexture(GL_TEXTURE_2D, 0); // <- 바인딩 해제 추가
							glUniform1i(m_iHas_texture_location, false); // <- 반드시 false 세팅
						}
						glm::mat4 MVP = GetMVP_ByObject(*obj);

						glUniformMatrix4fv(m_iMVP_Location, 1, GL_FALSE, glm::value_ptr(MVP));

						m->Draw();
#ifdef _DEBUG
						Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
						if (col)
						{
							col->DrawCollider();
						}
#endif
					}
				}
				else if (spr)
				{					
					if (spr->GetTexture() != nullptr)
					{
						GLuint tex_id = spr->GetTexture()->GetTextureID();
						glActiveTexture(GL_TEXTURE0); //반드시 유닛 0 활성화
						glBindTexture(GL_TEXTURE_2D, tex_id); //텍스처 바인딩
						glUniform1i(m_iOut_texture_location, 0); //셰이더에서 사용할 유닛 지정
						glUniform1i(m_iHas_texture_location, true);
					}
					else
					{
						glUniform1i(m_iHas_texture_location, false);
		 			}
					
					//todo : 여기좀 지저분함 손좀보셈
					glm::mat4 MVP = GetMVP_ByObject(*obj);
					glm::mat4 visualOffset;
					Player* p = dynamic_cast<Player*>(obj->FindComponent(Player::PlayerTypeName));
					Monster* mon = dynamic_cast<Monster*>(obj->FindComponent<Monster>());
					//CurseDemon* mon = dynamic_cast<CurseDemon*>(obj->FindComponent<CurseDemon>());
					bool dashing=false;
					if(p)
						dashing= p->GetIsDashing();
					if (obj->GetName() == "Player")
					{												
						if (dashing)
						{
							// 텍스처가 오른쪽으로 치우쳐 있을 경우, 살짝 왼쪽으로 당김							
							float texture_offsetX = -0.5f; // ← 여기서 0.1이 보정값 (시각적 기준 보정)
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
							scaleX = -scaleX; // 음수 스케일로 좌우 반전
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
										
					if (p&&p->GetIsHurting())					
						glUniform1i(m_iHurtEffect_location, true);					
					else					
						glUniform1i(m_iHurtEffect_location, false);					

					if (mon && mon->GetIsHurting())					
						glUniform1i(m_iHurtEffect_location, true);
					else
						glUniform1i(m_iHurtEffect_location, false);

					model->Draw();

					//todo : 주석처리된거 지우고 충돌체 쉐이더를 통해 그리는거 이것도 쉐이더에서 수정하고 
					//draw collider에도 주석있음 아마 assert주석 처리해놓았을 거임 그것도 지우셈
#ifdef _DEBUG
					Collider* col = dynamic_cast<Collider*>(obj->FindComponent(Collider::ColliderTypeName));
					if (col)
					{
						col->DrawCollider();
					}
#endif
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
#include <iostream>
#include "InputManager.h"
void RenderManager::EndDraw()
{		
	std::vector<GameObject*> TransParent_temp,Opaque_temp;
	TransParent_temp.swap(m_vTransParnetObject);
	Opaque_temp.swap(m_vOpaqueObject);
}

void RenderManager::Exit()
{
	EndDraw();
	if (m_pCam)	
		delete m_pCam;		
	m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Diuse();
	m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();
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