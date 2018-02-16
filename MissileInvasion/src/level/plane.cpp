#include "plane.h"

Plane::Plane(vec2 position)
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

	m_Texture = new Texture("plane", "res/sprites/plane.png");
	m_Shader = new Shader("res/shaders/plane.vert", "res/shaders/plane.frag", "Plane");
}

void Plane::update(Window* window, float timeElapsed)
{
		vec2 mousePos = window->getMousePosition();
		vec2 mouseScreenPos = maths::vec2((float)(mousePos.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mousePos.y * 18.0f / window->getHeight()));
		vec2 targetPos = mouseScreenPos + vec2(20.0f, 20.0f) * mouseScreenPos.normalize();

		float deltaX = targetPos.x - m_Position.x;
		float deltaY = targetPos.y - m_Position.y;
		float radian = atan2(deltaY, deltaX);
		m_Position.x += SPEED * cos(radian) * 0.05f;
		m_Position.y += SPEED * sin(radian) * 0.05f;
		rot = maths::toDegrees(radian) - 90.0f;
}

void Plane::render(mat4 vw_matrix)
{
	m_Shader->enable();
	m_Shader->setUniformMat4("ml_matrix", mat4::rotate(rot, vec3(0.0f, 0.0f, 1.0f)) * mat4::translate(m_Position) * vw_matrix);
	glActiveTexture(GL_TEXTURE1);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}
