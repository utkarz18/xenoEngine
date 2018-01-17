#include "pipe.h"

Pipe::Pipe()
{
	init();
}

Pipe::Pipe(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	ml_matrix = mat4::translate(m_Position);
}

Pipe::~Pipe()
{
	delete m_Mesh;
	delete m_Texture;
	delete m_Shader;
	delete ib;
}

void Pipe::init()
{
	float vertices[] =
	{
		0.0f, 0.0f, 0.1f,
		0.0f, m_Height, 0.1f,
		m_Width, m_Height, 0.1f,
		m_Width, 0.0f, 0.1f
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

	tb = new VertexBuffer(tcs, 4 * 3 * sizeof(float));
	m_Mesh->addBuffer(tb);
	bufferLayout->push(2, GL_FLOAT, GL_FALSE);

	m_Mesh->setBufferLayout(bufferLayout);
	m_Mesh->processBufers();

	ib = new IndexBuffer(indices, 6);

	m_Texture = new Texture("pipe", "res/sprites/pipe.png");
	m_Shader = new Shader("res/shaders/pipe.vert", "res/shaders/pipe.frag", "Pipe");
}

void Pipe::render(int i, int xScroll, Pipe* pipe)
{
	m_Shader->enable();
	m_Shader->setUniformMat4("vw_matrix", mat4::translate(vec3(xScroll * 0.05f, 0.0f, 0.0f)));
	m_Shader->setUniformMat4("ml_matrix", pipe->getModelMatrix());
	m_Shader->setUniform1i("top", i % 2 == 0 ? 1 : 0);
	glActiveTexture(GL_TEXTURE2);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}