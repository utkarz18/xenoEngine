#include "bird.h"

Bird::Bird()
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
		0, 1,
		0, 0,
		1, 0,
		1, 1
	};

	mesh = new VertexArray(vertices, indices, tcs);
	texture = new Texture("bird", "res/bird.png");
	shader = new Shader("res/shaders/bird.vert", "res/shaders/bird.frag");
}

void Bird::update() {
	/*position.y -= delta;
	if (window.isKeyDown(GLFW_KEY_SPACE))
		delta = -0.15f;
	else
		delta += 0.01f;

	rot = -delta * 90.0f;*/
}

void Bird::fall() {
	delta = -0.15f;
}

void Bird::render() {
	shader->enable();
	shader->setUniformMat4("ml_matrix", mat4::translation(position).multiply(mat4::rotation(rot, vec3(0, 0, 1))));
	texture->bind();
	mesh->render();
	shader->disable();
}
