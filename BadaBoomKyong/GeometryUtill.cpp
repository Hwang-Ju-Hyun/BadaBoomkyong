#include "GeometryUtill.h"
#include "Transform.h"
#include "GameObject.h"
#include "MathUtil.h"
#include "Player.h"
#include "RigidBody.h"
#include <iostream>
#include "Collider.h"

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


void GeometryUtil::HandlePosition_CollisionAABB(GameObject* _groundObj, GameObject* _otherObj)
{
    Transform* other_obj_trs = dynamic_cast<Transform*>(_otherObj->FindComponent(Transform::TransformTypeName));
    Transform* ground_obj_trs = dynamic_cast<Transform*>(_groundObj->FindComponent(Transform::TransformTypeName));        

    Collider* other_obj_col=dynamic_cast<Collider*>(_otherObj->FindComponent(Collider::ColliderTypeName));
    Collider* ground_obj_col = dynamic_cast<Collider*>(_groundObj->FindComponent(Collider::ColliderTypeName));

    glm::vec2 pPos = other_obj_col->GetFinalPosition();
    glm::vec2 gPos = ground_obj_col->GetFinalPosition();

    glm::vec2 pScale = other_obj_col->GetScale();
    glm::vec2 gScale = ground_obj_col->GetScale();

    float dx = (pPos.x - gPos.x);
    float px = (pScale.x + gScale.x) * 0.5f - std::abs(dx);

    float dy = (pPos.y - gPos.y);
    float py = (pScale.y + gScale.y) * 0.5f - std::abs(dy);

    RigidBody* rb = dynamic_cast<RigidBody*>(_otherObj->FindComponent(RigidBody::RigidBodyTypeName));
    assert(rb != nullptr);
    
    if (px < py) 
    {
        other_obj_trs->AddPositionX((dx > 0) ? px : -px);
    }
    else
    {
        other_obj_trs->AddPositionY((dy > 0) ? py : -py);

        Player* p = dynamic_cast<Player*>(_otherObj->FindComponent(Player::PlayerTypeName));
       

        //todo 
        /*if (rb!=nullptr&& dy > 0)
        {                
            if (p != nullptr && p->jumpPressed)
            {
                p->jumpPressed = false;                
                return;
            }                
            rb->GroundMessage = true;
            rb->SetIsGround(true);            
        }*/        
    }
}

