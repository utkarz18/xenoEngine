#include "bird.h"

Bird::Bird(vec3 position)
{
	init();
	m_Position = position;
}

Bird::~Bird()
{
	delete m_Mesh;
	delete m_Texture;
	delete m_Shader;
	delete ib;
}

void Bird::init()
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

	m_Texture = new Texture("bird", "res/sprites/bird.png");
	m_Shader = new Shader("res/shaders/bird.vert", "res/shaders/bird.frag");

	m_Shader->enable();
	m_Shader->setUniformMat4("vw_matrix", mat4::translate(m_Position));
	m_Shader->disable();
}

void Bird::update(const Window* window, const bool& gameRunning)
{
	m_Position.y -= delta;
	if (gameRunning && window->isKeyPressed(GLFW_KEY_SPACE))
	{
		audio::AudioManager::get("Flap")->play();
		delta = -0.15f;
	}
	else
		delta += 0.01f;

	rot = -delta * 90.0f;
}

void Bird::fall() 
{
	delta = -0.15f;
}

void Bird::render() 
{
	m_Shader->enable();
	m_Shader->setUniformMat4("ml_matrix", mat4::translate(m_Position).multiply(mat4::rotate(rot, vec3(0, 0, 1))));
	glActiveTexture(GL_TEXTURE0);
	m_Texture->bind();
	m_Mesh->render(ib);
	m_Shader->disable();
}
