#include "GeometryUtill.h"
#include "Transform.h"
#include "GameObject.h"
#include "MathUtil.h"
#include <stdio.h>

GeometryUtil::GeometryUtil(){}

GeometryUtil::~GeometryUtil() {}

bool GeometryUtil::IsPointInsideRectangle(glm::vec2 _point, Transform* _trs)
{	  
    if(_trs->GetOwner()->GetModelType() == MODEL_TYPE::RECTANGLE|| _trs->GetOwner()->GetModelType() == MODEL_TYPE::LINE)
	{        
        glm::vec3 obj_pos = _trs->GetPosition();
        glm::vec2 obj_scale = _trs->GetScale();

        float obj_right = obj_pos.x + (obj_scale.x / 2.f);
        float obj_left = obj_pos.x - (obj_scale.x / 2.f);
        float obj_top = obj_pos.y + (obj_scale.y / 2.f);
        float obj_bottom = obj_pos.y - (obj_scale.y / 2.f);

        if (_point.x < obj_right && obj_left < _point.x
            && _point.y < obj_top && obj_bottom < _point.y)
        {
            return true;
        }
	}
	return false;
}

bool GeometryUtil::IsPointInsideTraingle(glm::vec2 _point, Transform* _trs)
{
    glm::vec2 tri_pos=_trs->GetPosition();

    std::vector<glm::vec3> vertices_pos = _trs->GeteEachVertexPosition();

    float d1=MathUtil::GetInstance()->Cross2D(_point, { vertices_pos[0].x,vertices_pos[0].y }, { vertices_pos[1].x,vertices_pos[1].y });
    float d2=MathUtil::GetInstance()->Cross2D(_point, { vertices_pos[1].x,vertices_pos[1].y }, { vertices_pos[2].x,vertices_pos[2].y });
    float d3=MathUtil::GetInstance()->Cross2D(_point, { vertices_pos[2].x,vertices_pos[2].y }, { vertices_pos[0].x,vertices_pos[0].y });

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);    
}

#include "Player.h"
#include "RigidBody.h"
#include <iostream>

void GeometryUtil::HandlePosition_CollisionAABB(GameObject* ground, GameObject* playerObj)
{
    auto playerTrs = dynamic_cast<Transform*>(playerObj->FindComponent("Transform"));
    auto groundTrs = dynamic_cast<Transform*>(ground->FindComponent("Transform"));

    glm::vec2 pPos = playerTrs->GetPosition();
    glm::vec2 gPos = groundTrs->GetPosition();
    glm::vec2 pScale = playerTrs->GetScale();
    glm::vec2 gScale = groundTrs->GetScale();

    float dx = (pPos.x - gPos.x);
    float px = (pScale.x + gScale.x) * 0.5f - std::abs(dx);

    float dy = (pPos.y - gPos.y);
    float py = (pScale.y + gScale.y) * 0.5f - std::abs(dy);

    if (px < py) 
    {
        playerTrs->AddPositionX((dx > 0) ? px : -px);
    }
    else 
    {
        playerTrs->AddPositionY((dy > 0) ? py : -py);

        Player* p = static_cast<Player*>(playerObj->FindComponent(Player::PlayerTypeName));
        if (dy > 0 && p)
        {            
            RigidBody* rb = static_cast<RigidBody*>(playerObj->FindComponent(RigidBody::RigidBodyTypeName));
            if (rb)
            {               
                if (p->jumpPressed)
                {                    
                    p->jumpPressed = false;
                    return;
                }
                else
                {
                    p->SetIsGround(true);
                    glm::vec3 vel = rb->GetVelocity();
                    vel.y = 0.f;
                    rb->SetVelocity(vel);
                }                
            }
        }
            
    }
}


//void GeometryUtil::HandlePosition_CollisionAABB(GameObject* _obj1, GameObject* _obj2)
//{	
//	Transform* obj1_trs = dynamic_cast<Transform*>(_obj1->FindComponent(Transform::TransformTypeName));
//	Transform* obj2_trs =  dynamic_cast<Transform*>( _obj2->FindComponent (Transform::TransformTypeName));
//
//	glm::vec2 obj1_pos = obj1_trs->GetPosition();
//	glm::vec2 obj2_pos = obj2_trs->GetPosition();
//
//	glm::vec2 obj1_scale = obj1_trs->GetScale();
//	glm::vec2 obj2_scale = obj2_trs->GetScale();
//
//	float upper_distance = std::fabs((obj1_pos.y - (obj1_scale.y / 2.f)) - (obj2_pos.y + obj2_scale.y / 2.f));
//	float down_distance = std::fabs((obj1_pos.y + (obj1_scale.y / 2.f)) - (obj2_pos.y - obj2_scale.y / 2.f));
//	float right_distance = std::fabs((obj1_pos.x + (obj1_scale.x / 2.f)) - (obj2_pos.x - obj2_scale.x / 2.f));
//	float left_distance = std::fabs((obj1_pos.x - (obj1_scale.x / 2.f)) - (obj2_pos.x + obj2_scale.x / 2.f));
//
//	float arr_distance[4] = { upper_distance, down_distance, right_distance, left_distance };
//	float min_distance = arr_distance[0];
//	int direction = 0;
//
//	for (int i = 0; i < 4; i++)
//	{
//		if (min_distance > arr_distance[i])
//		{
//			min_distance = arr_distance[i];
//			direction = i;
//		}
//	}
//	Player* p = static_cast<Player*>(_obj2->FindComponent(Player::PlayerTypeName));
//	RigidBody* rig =static_cast<RigidBody*>(p->GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
//	switch (direction)
//	{
//	case 0:
//		obj2_trs->AddPositionY(-min_distance);				
//		break;
//	case 1:	
//		obj2_trs->AddPositionY(min_distance);		
//		p->SetJumpForce(0);
//		p->SetIsGround(true);
//		p->SetCurJumpCountZero();
//		break;	
//	case 2:
//		obj2_trs->AddPositionX(min_distance);				
//		break;
//	case 3:
//		obj2_trs->AddPositionX(-min_distance);				
//		break;
//	default:
//		break;
//	}	
//}
