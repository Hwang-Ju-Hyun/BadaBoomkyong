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
	
	//���� �ֱ� VAO�� Opengl context�� ���ε�
	//�� �Լ��� ȣ���ϸ� �� ������ vbo������ �ش� vao�� �����
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER��� å ���ĵ�(���ؽ�Ʈ)�� VBO��� å ���ε�
	//GL_ARRAY_BUFFER : ����(Vertex) �����͸� �����ϴ� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//  ���ۿ� ������ ������ ���
	// (�̸� �غ�� ����, ���� ����� �迭 ������(Attribute)�� vbo�� ����)
	const auto size_of_vertex = sizeof(glm::vec3)*_vertices.size();
	glBufferData(GL_ARRAY_BUFFER, size_of_vertex, _vertices.data(), GL_STATIC_DRAW);

	//ù��° ���� : VertexAttribute��ȣ
	//coord Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT),(void*)0);
	//VertexAttribute��ȣ ����
	glEnableVertexAttribArray(0);

	//Texture
	glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	
	//Binding ���� <- �� �̻� �������� ����
	//��
	//glBindVertexArray(VAO); �ϸ� ������ VBO, �Ӽ� ���� ���� �� VAO�� �����
	//glBindVertexArray(0); �ϸ� ���� VAO�� �����ǹǷ�, ������ ������ �ƹ� VAO���� ������� ����

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
