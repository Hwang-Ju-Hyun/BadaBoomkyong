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
