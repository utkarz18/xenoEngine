#include "plane.h"

Plane::Plane(vec3 position)
{
	init();
	m_Position = position;
}

Plane::~Plane()
{
	delete m_Mesh;
	delete m_Texture;
	delete m_Shader;
	delete ib;
}

void Plane::init()
{
	float vertices[] =
	{
		-SIZE / 2.0f, -SIZE / 2.0f, 0.2f,
		-SIZE / 2.0f,  SIZE / 2.0f, 0.2f,
		 SIZE / 2.0f,  SIZE / 2.0f, 0.2f,
		 SIZE / 2.0f, -SIZE / 2.0f, 0.2f
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

	m_Texture = new Texture("bird", "res/sprites/plane.png");
	m_Shader = new Shader("res/shaders/plane.vert", "res/shaders/plane.frag", "Plane");

	m_Shader->enable();
	m_Shader->setUniformMat4("vw_matrix", mat4::translate(m_Position));
	m_Shader->disable();
}

void Plane::update(const Window* window)
{
	m_Position.y += 0.05f;
	vec2 mousePos = window->getMousePosition();
	float deltaY = m_Position.y - mousePos.y;
	float deltaX = m_Position.x - mousePos.x;
	//rot = (atan2(deltaY, deltaX)*180.0000) / 3.1416;
}

void Plane::render()
{
	m_Shader->enable();
	m_Shader->setUniformMat4("ml_matrix", mat4::translate(m_Position)*mat4::rotate(rot, vec3(0, 0, 1)));
	glActiveTexture(GL_TEXTURE1);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}
