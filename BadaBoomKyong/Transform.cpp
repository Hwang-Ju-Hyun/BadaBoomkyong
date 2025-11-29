#include "Transform.h"
#include "GameObject.h"
#include "Window.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "BaseComponent.h"
#include "Model.h"
#include "Camera.h"
#include "RenderManager.h"
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include "Mesh.h"
#include "Player.h"

Transform::Transform(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(this->TransformTypeName);
}

Transform::~Transform()
{
}

//It returns worldspace coords
std::vector<glm::vec3> Transform::GeteEachVertexPosition()
{
	//todo 이거 함수 자체를 지우던가 getvertices를 손보던가
	std::vector<Mesh::VertexAttribute> attr;
	std::vector<Mesh*> meshes = GetOwner()->GetModel()->GetMeshes();
	for (int i = 0;i < meshes.size();i++)
	{
		std::vector<Mesh::VertexAttribute> vertices = meshes[i]->GetVertices();
		for (int j = 0;j < vertices.size();j++)
		{
			attr.push_back(vertices[j]);
		}		
	}
	std::vector<glm::vec3> pos;	
	for (int i = 0;i < attr.size();i++)
	{
		glm::vec3 localPos = attr[i].position;
		glm::vec3 worldPos = m_mModeltoWorld_2D * glm::vec3(localPos.x, localPos.y, 1.0f);
		pos.push_back({ worldPos });
	}	
	return pos;
}

glm::mat4 Transform::GetModelToWorld_Matrix()
{
	return m_mModeltoWorld_3D;
}

void Transform::Init(){	}

void Transform::Update()
{
	float window_width = static_cast<float>(Window::GetInstance()->GetWindowWidth());
	float window_height = static_cast<float>(Window::GetInstance()->GetWindowHeight());
	if (GetOwner()->GetIs3D())
	{		
		glm::mat4 translate = glm::mat4(1.0f);
		glm::mat4 scale = glm::mat4(1.0f);
						
		
		scale = glm::scale(scale, m_vScale);
		translate = glm::translate(translate, m_vPosition);

		if(m_vRotation.x > 360.f)
			m_vRotation.x = 0.f;
		if (m_vRotation.y > 360.f)
			m_vRotation.y = 0.f;
		if (m_vRotation.z > 360.f)
			m_vRotation.z = 0.f;

		// Convert Euler angles to quaternion		
		glm::quat quatRotation = glm::quat(glm::radians(m_vRotation));

		// Convert quaternion to rotation matrix
		glm::mat4 rotationMatrix = glm::toMat4(quatRotation);		

		m_mModeltoWorld_3D = translate * rotationMatrix * scale;

		if (GetOwner()->GetName() == "Player")
		{
			const GameObject* owner = GetOwner();
			Camera* cam = RenderManager::GetInstance()->GetCamera();
			glm::vec3 cam_pos = cam->GetCamPosition();
			glm::vec3 obj_pos = m_vPosition;

			glm::vec3 dir = glm::normalize(cam_pos - obj_pos);
			dir.y = 0.0f; // cylindrical billboard 
			glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), dir));
			glm::vec3 up = glm::cross(dir, right);

			glm::mat4 billboard = glm::mat4(1.0f);
			billboard[0] = glm::vec4(right, 0.0f);
			billboard[1] = glm::vec4(up, 0.0f);
			billboard[2] = glm::vec4(dir, 0.0f);

			m_mModeltoWorld_3D = translate * billboard * scale;
			return;
		}	
	}
	else
	{
		std::string a = GetOwner()->GetName();
		m_vPosition.z = 0.f;
		glm::mat4 translate = glm::translate(glm::mat4(1.0f),m_vPosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f),m_vScale);
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), m_fRotation, glm::vec3(0, 0, 1));
		m_mModeltoWorld_3D = translate * rotateZ * scale;
	}
}
 
void Transform::Exit()
{

}

BaseRTTI* Transform::CreateTransformComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();	
	BaseRTTI* comp = last_obj->AddComponent_and_Get(TransformTypeName, new Transform(last_obj));	
	if(comp!=nullptr)
		return comp;
	return nullptr;
}

void Transform::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto pos = iter_compData->find(PositionName);
		m_vPosition.x = pos->begin().value();
		m_vPosition.y = (pos->begin()+1).value();
		m_vPosition.z = (pos->begin() + 2).value();

		auto sca = iter_compData->find(ScaleName);
		m_vScale.x = sca->begin().value();
		m_vScale.y = (sca->begin()+1).value();		
		m_vScale.z = (sca->begin()+2).value();

		if (GetOwner()->GetIs3D())
		{
			auto rot = iter_compData->find(RotationName);
			m_vRotation.x = rot->begin().value();
			m_vRotation.y = (rot->begin()+1).value();
			m_vRotation.z = (rot->begin()+2).value();
		}
		else
		{
			auto rot = iter_compData->find(RotationName);
			m_fRotation = rot->begin().value();
		}		
	}
}

json Transform::SaveToJson(const json& _str)
{	
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = TransformTypeName;

	json compData;
	compData[PositionName] = { m_vPosition.x,m_vPosition.y,m_vPosition.z };
	compData[ScaleName] = { m_vScale.x,m_vScale.y,m_vScale.z};
	if (GetOwner()->GetIs3D())	
		compData[RotationName] = { m_vRotation.x,m_vRotation.y,m_vRotation.z};
	else
		compData[RotationName] = { m_fRotation };

	data[CompDataName] = compData;
	
	return data;	
}

#ifdef _DEBUG
void Transform::EditInfoFromButton()
{	
	bool is3d = GetOwner()->GetIs3D();	
	ImGui::InputFloat3("Pos", &(m_vPosition[0]));
	ImGui::InputFloat3("Scale", &(m_vScale[0]));
	if (is3d)
		ImGui::InputFloat3("Rot", &(m_vRotation[0]));
	else
		ImGui::InputFloat("Rot", &(m_fRotation));
}
#endif // DEBUG