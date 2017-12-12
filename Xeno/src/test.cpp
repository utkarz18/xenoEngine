#include <xeno.h>

using namespace xeno;
using namespace graphics;

class Game : public Xeno
{
private:
	Window* window;
	Shader* shader;
	VertexArray* background;
public:
	Game()
	{

	}

	~Game()
	{
		
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		float vertices[] =
		{
			-0.5f, -0.5f,
			-0.5f,  0.5f,
			0.5f,  0.5f,
			0.5f, -0.5f,
		};

		unsigned short indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		float tcs[] = {
			0, 1,
			0, 0,
			1, 0,
			1, 1
		};

		background = new VertexArray(vertices, indices, nullptr);
		
	}

	void tick() override
	{
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void update() override
	{
		float speed = 0.5f;
		/*if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;*/

		maths::vec2 mouse = window->getMousePosition();
	//	shader->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

	void render() override
	{
		background->bind();
		background->draw();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}