#include <xeno.h>
#include "bird.h"

using namespace xeno;
using namespace graphics;

class Game : public Xeno
{
private:
	Window* window;
	VertexArray* background;
	Bird* bird;

public:
	Game()
	{

	}

	~Game()
	{

	}

	void init() override
	{
		window = createWindow("Test Game", 800, 600);

		float vertices[] =
		{
			-0.5f, -0.5f,
			-0.5f,  0.5f,
			0.5f,  0.5f,
			0.5f, -0.5f,
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

		bird = new Bird();
	}

	void tick() override
	{
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void update() override
	{
	}

	void render() override
	{
		bird->render();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}