#include <GL/glew.h>
#include "Model.h"

Model::Model(const std::string& _name, MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute> _vertices)
	:m_sName(_name),
	 m_eModelType(_modelType),
	 m_ePrimitiveType(_primitiveType)	 
{
	//Create Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//가장 최근 VAO로 Opengl context에 바인딩
	//이 함수를 호출하면 그 이후의 vbo설정은 해당 vao에 저장됨
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER라는 책 스탠드(컨텍스트)에 VBO라는 책 바인딩
	//GL_ARRAY_BUFFER : 정점(Vertex) 데이터를 저장하는 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//  버퍼에 실질적 데이터 담기
	// (미리 준비된 정점, 색상 등등의 배열 데이터(Attribute)를 vbo에 연결)
	const auto size_of_vertex = sizeof(glm::vec3)*_vertices.size();
	glBufferData(GL_ARRAY_BUFFER, size_of_vertex, _vertices.data(), GL_STATIC_DRAW);

	//첫번째 인자 : VertexAttribute번호
	//coord Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT),(void*)0);
	//VertexAttribute번호 전달
	glEnableVertexAttribArray(0);

	//Texture
	glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	
	//Binding 끊기 <- 더 이상 변경하지 않음
	//즉
	//glBindVertexArray(VAO); 하면 이후의 VBO, 속성 설정 등이 이 VAO에 저장됨
	//glBindVertexArray(0); 하면 현재 VAO가 해제되므로, 이후의 설정이 아무 VAO에도 저장되지 않음

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
	if (VAO != 0)
	{
		glDeleteBuffers(1, &VAO);
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
	}
}

void Model::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(m_ePrimitiveType,0, GetPositionCnt_of_VBO());
}
