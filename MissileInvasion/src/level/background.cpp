#include "background.h"

Background::Background()
{
	init();
}

Background::~Background()
{
	delete m_Mesh;
	delete m_Texture;
	delete m_Shader;
	delete ib;
}

void Background::init()
{
	float vertices[] =
	{
		-10.0f, -10.0f * 9.0f / 16.0f, 0.0f,
		-10.0f,  10.0f * 9.0f / 16.0f, 0.0f,
		 10.0f,  10.0f * 9.0f / 16.0f, 0.0f,
		 10.0f, -10.0f * 9.0f / 16.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float tcs[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	m_Mesh = new VertexArray();
	VertexBufferLayout* bufferLayout = new VertexBufferLayout();

	vb = new VertexBuffer(vertices, 4 * 3 * sizeof(float));
	m_Mesh->addBuffer(vb);
	bufferLayout->push(3, GL_FLOAT, GL_FALSE);

	tb = new VertexBuffer(tcs, 4 * 2 * sizeof(float));
	m_Mesh->addBuffer(tb);
	bufferLayout->push(2, GL_FLOAT, GL_FALSE);

	m_Mesh->setBufferLayout(bufferLayout);
	m_Mesh->processBufers();

	ib = new IndexBuffer(indices, 6);

	m_Texture = new Texture("pipe", "res/sprites/bg.png");
	m_Shader = new Shader("res/shaders/bg.vert", "res/shaders/bg.frag", "Background");
}

void Background::render()
{
	m_Shader->enable();
	//m_Shader->setUniformMat4("vw_matrix", mat4::translate(vec3(i * 10 + xScroll * 0.03f, 0.0f, 0.0f)));
	glActiveTexture(GL_TEXTURE0);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}