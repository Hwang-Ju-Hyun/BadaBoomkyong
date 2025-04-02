#include <GL/glew.h>
#include "Model.h"

Model::Model(const std::string& _name, MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute>&& _vertices, std::vector<unsigned int>&& _indices)
	:m_sName(_name),
	m_eModelType(_modelType),
	m_ePrimitiveType(_primitiveType),
	m_vVertices(_vertices),
	m_vIndices(_indices)
{	
	m_vIndices.size() <= 2 ? m_bEBO = false : m_bEBO = true;
	UploadBuffers();
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
	if (m_bEBO)
		glDrawElements(m_ePrimitiveType, m_vIndices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(m_ePrimitiveType,0, GetPositionCnt_of_VBO());
}

void Model::UploadBuffers()
{
	//Create Buffer	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (m_bEBO)
		glGenBuffers(1, &EBO);
	//���� �ֱ� VAO�� Opengl context�� ���ε�
	//�� �Լ��� ȣ���ϸ� �� ������ vbo������ �ش� vao�� �����
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER��� å ���ĵ�(���ؽ�Ʈ)�� VBO��� å ���ε�
	//GL_ARRAY_BUFFER : ����(Vertex) �����͸� �����ϴ� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (m_bEBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//  ���ۿ� ������ ������ ���
	// (�̸� �غ�� ����, ���� ����� �迭 ������(Attribute)�� vbo�� ����)
	// m_vVertices.size()*2�� �� ���� : position�� uv��ǥ(�� 2���� ����)�� �ֱ� ����
	const auto size_of_vertex = sizeof(glm::vec3) * m_vVertices.size()*2;
	glBufferData(GL_ARRAY_BUFFER, size_of_vertex, m_vVertices.data(), GL_STATIC_DRAW);
	
	if (m_bEBO)
	{
		const auto size_of_indices = sizeof(unsigned int) * m_vIndices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices, m_vIndices.data(), GL_STATIC_DRAW);
	}
	
	//ù��° ���� : VertexAttribute��ȣ
	//coord Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	//VertexAttribute��ȣ ����
	glEnableVertexAttribArray(0);

	//Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	//Binding ���� <- �� �̻� �������� ����
	//��
	//glBindVertexArray(VAO); �ϸ� ������ VBO, �Ӽ� ���� ���� �� VAO�� �����
	//glBindVertexArray(0); �ϸ� ���� VAO�� �����ǹǷ�, ������ ������ �ƹ� VAO���� ������� ����

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}