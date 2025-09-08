#include <GL/glew.h>
#include "ParticleSystem.h"
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
#include "CubeMapResource.h"
#include "SkyBox.h"

//temp �����
#include "InputManager.h"
#include "MathUtil.h"


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
static float x = 0.f;
void RenderManager::Init()
{
	const char* vsFile_2D = "vertex.vert";
	const char* fsFile_2D = "fragment.frag";
		
	const char* vsFile_3D = "vertex3d.vert";
	const char* fsFile_3D = "fragment3d.frag";

	const char* vsFile_SkyBox = "vertexSkyBox.vert";
	const char* fsFile_SkyBox= "fragmenetSkyBox.frag";

	const char* vsFile_Particle = "Particles.vert";
	const char* fsFile_Particle = "Particles.frag";

	for (int i = 0;i<int(SHADER_REF::SHADER_REF_LAST);i++)
	{
		Shader* shdr = new Shader;
		m_vShdr.push_back(shdr);
	}

	m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->CreateShaderProgramFromFiles(vsFile_2D, fsFile_2D);
	m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->CreateShaderProgramFromFiles(vsFile_3D, fsFile_3D);
	m_vShdr[int(SHADER_REF::SKYBOX)]->CreateShaderProgramFromFiles(vsFile_SkyBox, fsFile_SkyBox);
	m_vShdr[int(SHADER_REF::PARTICLES)]->CreateShaderProgramFromFiles(vsFile_Particle, fsFile_Particle);

	m_pParticleSystem = new ParticleSystem;
	
	

	m_pCam = new Camera;
	
	m_pCam->Init();
	m_pParticleSystem->Init();

	//todo : �̰� �� light manager�� �ű��
	GameObject* light_obj = GameObjectManager::GetInstance()->FindObject("Light");
	m_pLight = dynamic_cast<Light*>(light_obj->FindComponent(Light::LightTypeName));
	assert(m_pLight != nullptr);

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
			else if(obj->GetName()=="customModelObj1")
			{
				m_vOpaqueObject.push_back(obj);
			}
			else if (obj->GetName() == "NewObject1")
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
	auto shdr_handle_3D=  m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->GetShaderProgramHandle();
	auto shdr_handle_skybox = m_vShdr[int(SHADER_REF::SKYBOX)]->GetShaderProgramHandle();
	auto shdr_handle_particle= m_vShdr[int(SHADER_REF::PARTICLES)]->GetShaderProgramHandle();

	Transform* obj_trs = nullptr;
	glEnable(GL_DEPTH_TEST);
	m_pCam->Update();

	BeforeDraw();

	m_iLightAffect_location= glGetUniformLocation(shdr_handle_3D, "uLightAffect");
			

	//1. ������ ���� ������
	for (auto obj : m_vOpaqueObject)
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
				glUniform1i(m_iLightAffect_location, true);


				obj->GetName() == "Light" ? glUniform1i(m_iLightColorOn, true) : glUniform1i(m_iLightColorOn, false);
				
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

					//===========
					//===========
					//====FOG====
					//===========
					//===========
					m_iFogColor_location = glGetUniformLocation(shdr_handle_3D, "uFogColor");
					m_iFogStart_location = glGetUniformLocation(shdr_handle_3D, "uFogStart");
					m_iFogEnd_location = glGetUniformLocation(shdr_handle_3D, "uFogEnd");
					assert(m_iFogColor_location >= 0);
					glUniform3f(m_iFogColor_location, 0.76, 0.65, 0.50);
					glUniform1f(m_iFogStart_location, 1650.f);
					glUniform1f(m_iFogEnd_location, 2000.f);
					//===========
					//===========
					//====FOG====
					//===========
					//===========

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

	//==========
	//==========
	//==skybox==
	//==========
	//==========
	DrawSkyBox(m_pCam);
	//==========
	//==========
	//==skybox==
	//==========
	//==========

	
	for (auto obj : objs)
	{
		Player* p = dynamic_cast<Player*>(obj->FindComponent<Player>());
		//============
		//============
		//==Particle==
		//============
		//============	
		if (p && p->m_bHolySlashing)
		{
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			m_vShdr[static_cast<int>(SHADER_REF::PARTICLES)]->Use();
			p->m_pPs->m_iParticleTransform_location = glGetUniformLocation(shdr_handle_particle, "u_MVP_Particle");
			assert(p->m_pPs->m_iParticleTransform_location >= 0);
			p->m_pPs->m_iParticleShaderColor_location = glGetUniformLocation(shdr_handle_particle, "u_Color");
			assert(p->m_pPs->m_iParticleShaderColor_location >= 0);

			p->m_pPs->Update();
			p->m_pPs->Render();
			m_vShdr[static_cast<int>(SHADER_REF::PARTICLES)]->Diuse();
		}
		//============
		//============
		//==Particle==
		//============
		//============
	}
	

	
	


	// ���� ��ü ������ ��
	glDepthMask(GL_FALSE); // ���� ��� ����
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
				m_iHurtEffect_location = glGetUniformLocation(shdr_handle_3D, "uHurtEffect");

				glUniform1i(m_iLightAffect_location, false);

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
					Monster* mon = dynamic_cast<Monster*>(obj->FindComponent<Monster>());											

						 
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

					//todo : �ּ�ó���Ȱ� ����� �浹ü ���̴��� ���� �׸��°� �̰͵� ���̴����� �����ϰ� 
					//draw collider���� �ּ����� �Ƹ� assert�ּ� ó���س����� ���� �װ͵� �����
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
	glDepthMask(GL_TRUE); // �ٽ� �ѱ�
	
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
				
	m_vShdr[int(SHADER_REF::TWO_DIMENSIONS)]->Diuse();
	m_vShdr[int(SHADER_REF::THREE_DIMENSIONS)]->Diuse();
	m_vShdr[int(SHADER_REF::SKYBOX)]->Diuse();

	for (int i = 0;i < static_cast<int>(SHADER_REF::SHADER_REF_LAST);i++)
	{
		delete m_vShdr[i];
		m_vShdr[i] = nullptr;
	}
	if (m_pCam)
	{
		delete m_pCam;
		m_pCam = nullptr;
	}

	if (m_pParticleSystem)
	{
		delete m_pParticleSystem;
		m_pParticleSystem = nullptr;
	}
}

void RenderManager::DrawSkyBox(Camera* _cam)
{
	auto skyboxObj = GameObjectManager::GetInstance()->FindObject("background");
	if (!skyboxObj) return;

	SkyBox* skyboxComp = skyboxObj->FindComponent<SkyBox>();
	if (!skyboxComp) return;

	CubeMapResource* cubemap = skyboxComp->GetCubeMapResource();
	if (!cubemap) 
		return;

	GLuint cubemapTex = cubemap->GetTextureID();

	// ���� ����
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	glCullFace(GL_FRONT); // ���θ� ���̰�	
	glDisable(GL_CULL_FACE); // ���Ѵٸ� �׳� ����
	//glEnable(GL_CULL_FACE);

	// ���̴� ���ε�
	Shader* skyShader = m_vShdr[int(SHADER_REF::SKYBOX)];
	skyShader->Use();

	// View matrix (translation ����)
	glm::mat4 view = glm::mat4(glm::mat3(_cam->GetViewMatrix()));
	glm::mat4 proj = _cam->GetProjMatrix();
	glm::mat4 VP = proj * view;

	// ������ ����
	GLint uVP = glGetUniformLocation(skyShader->GetShaderProgramHandle(), "uVP");
	glUniformMatrix4fv(uVP, 1, GL_FALSE, glm::value_ptr(VP));

	// ť��� ���ε�
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTex);
	GLint uSkybox = glGetUniformLocation(skyShader->GetShaderProgramHandle(), "skybox");
	glUniform1i(uSkybox, 0);

	// ť�� �޽� ��ο� (�ܼ� ť�� VAO �غ��صα�)
	skyboxObj->GetModel()->Draw();	

	// ���� ����
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	skyShader->Diuse();

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