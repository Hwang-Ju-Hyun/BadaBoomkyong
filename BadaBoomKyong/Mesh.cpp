#include <GL/glew.h>
#include "Mesh.h"
#include "Material.h"

Mesh::Mesh(MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute>&& _vertices, std::vector<unsigned int>&& _indices)
	:m_eModelType(_modelType),
	m_ePrimitiveType(_primitiveType),
	m_vVertices(_vertices),
	m_vIndices(_indices)
{
	m_vIndices.size() <= 2 ? m_bEBO = false : m_bEBO = true;
	UploadBuffers();
}

Mesh::~Mesh()
{
	if (VAO != 0)
	{
		glDeleteBuffers(1, &VAO);
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
	}
	DeleteMaterial();
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	if (m_bEBO)
	{
		glDrawElements(m_ePrimitiveType, (size_t)m_vIndices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		if (m_ePrimitiveType == GL_LINES)
			glLineWidth(50.f);
		glDrawArrays(m_ePrimitiveType, 0, (size_t)GetPositionCnt_of_VBO());
	}
}

void Mesh::DeleteMaterial()
{
	if (m_pMaterial) 
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}


void Mesh::UploadBuffers()
{
	//Create Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (m_bEBO)
		glGenBuffers(1, &EBO);
	//가장 최근 VAO로 Opengl context에 바인딩
	//이 함수를 호출하면 그 이후의 vbo설정은 해당 vao에 저장됨
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER라는 책 스탠드(컨텍스트)에 VBO라는 책 바인딩
	//GL_ARRAY_BUFFER : 정점(Vertex) 데이터를 저장하는 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (m_bEBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//  버퍼에 실질적 데이터 담기
	// (미리 준비된 정점, 색상 등등의 배열 데이터(Attribute)를 vbo에 연결)
	// m_vVertices.size()*2를 한 이유 : position과 uv좌표(총 2개의 변수)가 있기 때문 <- 이였는데 지금 노말 벡터 추가함
	const auto size_of_vertex = m_vVertices.size() * sizeof(VertexAttribute);
	glBufferData(GL_ARRAY_BUFFER, size_of_vertex, m_vVertices.data(), GL_STATIC_DRAW);

	if (m_bEBO)
	{
		const auto size_of_indices = sizeof(unsigned int) * m_vIndices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices, m_vIndices.data(), GL_STATIC_DRAW);
	}

	//첫번째 인자 : VertexAttribute번호
	//coord Vertex (Location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
	//VertexAttribute번호 전달
	glEnableVertexAttribArray(0);

	//Texture (Location = 1)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//Normal (Location = 2)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(5 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	//Binding 끊기 <- 더 이상 변경하지 않음
	//즉
	//glBindVertexArray(VAO); 하면 이후의 VBO, 속성 설정 등이 이 VAO에 저장됨
	//glBindVertexArray(0); 하면 현재 VAO가 해제되므로, 이후의 설정이 아무 VAO에도 저장되지 않음

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}