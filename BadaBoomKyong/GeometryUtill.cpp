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

void GeometryUtil::HandlePosition_CollisionAABB(GameObject* _obj1, GameObject* _obj2)
{	
	Transform* obj1_trs = dynamic_cast<Transform*>(_obj1->FindComponent(Transform::TransformTypeName));
	Transform* obj2_trs =  dynamic_cast<Transform*>( _obj2->FindComponent (Transform::TransformTypeName));

	glm::vec2 obj1_pos = obj1_trs->GetPosition();
	glm::vec2 obj2_pos = obj2_trs->GetPosition();

	glm::vec2 obj1_scale = obj1_trs->GetScale();
	glm::vec2 obj2_scale = obj2_trs->GetScale();


	float upper_distance = std::fabs((obj1_pos.y - (obj1_scale.y / 2.f)) - (obj2_pos.y + obj2_scale.y / 2.f));
	float down_distance = std::fabs((obj1_pos.y + (obj1_scale.y / 2.f)) - (obj2_pos.y - obj2_scale.y / 2.f));
	float right_distance = std::fabs((obj1_pos.x + (obj1_scale.x / 2.f)) - (obj2_pos.x - obj2_scale.x / 2.f));
	float left_distance = std::fabs((obj1_pos.x - (obj1_scale.x / 2.f)) - (obj2_pos.x + obj2_scale.x / 2.f));

	float arr_distance[4] = { upper_distance, down_distance, right_distance, left_distance };
	float min_distance = arr_distance[0];
	int direction = 0;

	for (int i = 0; i < 4; i++)
	{
		if (min_distance > arr_distance[i])
		{
			min_distance = arr_distance[i];
			direction = i;
		}
	}

	switch (direction)
	{
	case 0:
		obj2_trs->AddPositionY(-min_distance);
		break;
	case 1:
		obj2_trs->AddPositionY(min_distance);
		break;
	case 2:
		obj2_trs->AddPositionX(min_distance);
		break;
	case 3:
		obj2_trs->AddPositionX(-min_distance);
		break;
	default:
		break;
	}
}
