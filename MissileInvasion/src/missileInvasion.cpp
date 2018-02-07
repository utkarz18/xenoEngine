#include <xeno.h>
#include <background.h>
#include <plane.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Game : public Xeno
{
private:
	Window* m_Window;
	Camera2D* camera;
	Background* background;
	Plane* plane;

public:
	Game(Window* window)
	{
		m_Window = window;
	}

	~Game()
	{
		delete background;
	}

	void init() override
	{
		camera = new Camera2D(vec3(0, 0, 0), 16.0f, 9, 2.5f);
		background = new Background();
		plane = new Plane(vec2(0, 0));

		// set orthographic view
		mat4 pr_matrix = mat4::orthographic(-16.0f, 16.0f, -9, 9.0f, -1.0f, 1.0f);

		std::vector<Renderable2D*> sprites = { background, plane };
		for (int i = 0; i < sprites.size(); i++)
		{
			int texIndex = i;
			Shader* shader = sprites[i]->getShader();
			shader->enable();
			shader->setUniformMat4("pr_matrix", pr_matrix);
			if (i > 2)
				texIndex = 3;
			shader->setUniform1i("tex", texIndex);
			shader->disable();
		}
	}

	void tick() override
	{
		//std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void update() override
	{
			plane->update(m_Window, this->getTimeElapsed());
			//camera->setPosition(plane->getPosition());
			//camera->update(); 
	}

	void render() override
	{
		background->render(camera->getCameraMatrix());
		plane->render(camera->getCameraMatrix());
	}
};

int main()
{
	Window* window = new Window("Missile Invasion", 960, 540);
	Game* game = new Game(window);
	game->start();

	while (!window->closed())
	{
		window->clear();
		game->run();
		window->update();
	}
}