#include "Transform.h"
#include "GameObject.h"
#include "Window.h"

Transform::Transform(GameObject* _owner)
	:BaseComponent(_owner)
{
	SetName(this->TypeName);
}

Transform::~Transform()
{
}

void Transform::Init(){}

void Transform::Update()
{
	float window_width  = static_cast<float>(Window::GetInstance()->GetWindowWidth());
	float window_height = static_cast<float>(Window::GetInstance()->GetWindowHeight());
	
	glm::mat3 transform =
	{
		1,				0,				0,			//	1 0 position x	
		0,				1,				0,			//	0 1 position y
		m_vPosition.x,  m_vPosition.y,	1			//  0 0 1
	};
	glm::mat3 scale =
	{
		m_vScale.x,0,0,								// scale 0 0
		0,m_vScale.y,0,								// 0 scale 0
		0,0,1										// 0  0    1
	};
	glm::mat3 rotation =						
	{
		std::cos(m_fRotation),	std::sin(m_fRotation),0,				//cos() -sin() 0
		-std::sin(m_fRotation),	std::cos(m_fRotation),0,				//sin() cos()  0
		0,						0,					  1					// 0      0    1
	};
	glm::mat3 WorldtoNDC =
	{
		1.f/window_width,		0,				0,
		0,					1.f/window_height,	0,
		0,						0,				1
	};

	m_mModeltoWorld = (transform  * rotation * scale);
	m_mModeltoNDC = WorldtoNDC*m_mModeltoWorld;
}

void Transform::Exit(){}
