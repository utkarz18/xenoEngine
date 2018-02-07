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
	if (!window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		m_Position.y += 0.05f;
	else
	{
		std::cout << "Fuck Santhosh" << std::endl;
		vec2 mousePos = window->getMousePosition();
		vec2 mouseScreenPos = maths::vec2((float)(mousePos.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mousePos.y * 18.0f / window->getHeight()));
		float deltaX = mousePos.x - mouseScreenPos.x;
		float deltaY = mousePos.y - mouseScreenPos.y;
		rot = (atan2(deltaY, deltaX)*180.0000) / 3.1416;
		//distance calculation
		float radius = mouseScreenPos.distance(m_Position);
		m_Position.x = 0.0f + radius * cos(rot);
		m_Position.y = 0.0f + radius * sin(rot);
		/*m_Position.x = mouseScreenPos.x;
		m_Position.y = mouseScreenPos.y;*/
		rot = (atan2(m_Position.y, m_Position.x)*180.0000) / 3.1416;
	}
}

void Plane::render(mat4 vw_matrix)
{
	m_Shader->enable();
	m_Shader->setUniformMat4("ml_matrix", mat4::rotate(rot + 0 % 90, vec3(0.0f, 0.0f, 1.0f)) * mat4::translate(m_Position));
	glActiveTexture(GL_TEXTURE1);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}
