#include <stdlib.h>
#include <xeno.h>
#include <bird.h>
#include <background.h>
#include <pipe.h>
#include <graphics/label.h>
#include <utils/fileUtils.h>
//for optimus card
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//extern "C" {
//	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}

#ifdef XENO_PLATFORM_WEB
static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}
#endif

using namespace xeno;
using namespace graphics;
using namespace audio;

class Game : public Xeno
{
private:
	Window* m_Window;
	Background* background;
	Bird* bird;
	Pipe* pipe;
	Pipe** pipes = new Pipe* [5 * 2];
	Label *title, *startMsg, *score, *highScore, *gameOverMsg;

	int xScroll, map, index, scoreCount = 0;
	float OFFSET = 10.0f;

	bool gameRunning = false;
	bool gameStarted = false;

	int highScoreCount;
public:
	Game(Window* window)
	{
		m_Window = window;
	}

	~Game()
	{
		delete background;
		delete bird;
		delete pipe;
		for (int i = 0; i < 5 * 2; i++)
			delete pipes[i];
		delete[] pipes;
		delete title;
		delete startMsg;
		delete score;
		delete highScore;
	}

	void init() override
	{
		highScoreCount = std::stoi(read_file("res/highScore.txt"));

		bird = new Bird(vec3(0, -0.8, 0));
		background = new Background();
		pipe = new Pipe();
		createPipes();

		title = new Label("Flappy Bird", -5.8, 2, 0xffffffff, 32);
		startMsg = new Label("Press SPACE to Play", -4, -4, FontManager::get("FlappyS"), 0xffffffff, 90);
		score = new Label("0", -0.4, 4, FontManager::get("FlappyS"), 0xffffffff, 50);
		highScore = new Label("", -2.8, 0, FontManager::get("FlappyS"), 0xffffffff, 80);

		mat4 pr_matrix = mat4::orthographic(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);
		
		std::vector<Renderable2D*> sprites = { bird, background, pipe, title, startMsg, score, highScore};
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
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void createPipes()
	{
		srand((unsigned)time(0));
		for (int i = 0; i < 5 * 2; i += 2) 
		{
			pipes[i] = new Pipe(OFFSET + index * 3.0f, 5.0f  * 0.8f * (float)rand() / (RAND_MAX + 1.0f));
			pipes[i + 1] = new Pipe(pipes[i]->getX(), pipes[i]->getY() - 11.6f);
			index += 2;
		}
	}

	void updatePipes()
	{
		pipes[index % 10] = new Pipe(OFFSET + index * 3.0f, 5.0f  * 0.8f * (float)rand() / (RAND_MAX + 1.0f));
		pipes[(index + 1) % 10] = new Pipe(pipes[index % 10]->getX(), pipes[index % 10]->getY() - 11.6f);
		index += 2;
	}

	void updateHighScore()
	{
		if (scoreCount > highScoreCount)
		{
			highScoreCount = scoreCount;
			write_file("res/highScore.txt", std::to_string(highScoreCount));
		}
	}

	bool checkCollisionandBounds()
 	{
		float birdX = -xScroll * 0.05;
		float birdY = bird->getY();

		if (birdY < -8.0f || birdY > 5.0f)
			return true;

		for (int i = 0; i < 5 * 2; i++)
		{
			float pipeX = pipes[i]->getX();
			float pipeY = pipes[i]->getY();

			float pipe2X;
			float pipe2Y;
			float pipe2X1;
			float pipe2Y1;

			float birdX0 = birdX - bird->getSize() / 2.0f;
			float birdX1 = birdX + bird->getSize() / 2.0f;
			float birdY0 = birdY - bird->getSize() / 2.0f;
			float birdY1 = birdY + bird->getSize() / 2.0f;

			float pipeX1 = pipeX + pipe->getWidth();
			float pipeY1 = pipeY + pipe->getHeight();

			if (birdX1 > pipeX && birdX0 < pipeX1)
				if (birdY1 > pipeY && birdY0 < pipeY1)
					return true;


			if (i < 9)
			{
				pipe2X = pipes[i + 1]->getX();
				pipe2Y = pipes[i + 1]->getY();
				pipe2X1 = pipe2X + pipe->getWidth();
				pipe2Y1 = pipe2Y + pipe->getHeight();

				if (birdX0 == pipeX1 + 0.5 && birdX0 == pipe2X1 + 0.5)
				{
					scoreCount++;
					score->m_Text = std::to_string(scoreCount);
					score->update();
					audio::AudioManager::get("Score")->play();
				}
			}
			
		}
		return false;
	}

	void update() override
	{
		if (gameRunning)
		{
			xScroll--;
			updateHighScore();
			if (-xScroll % 335 == 0)
				map++;
			if (-xScroll > 400 && -xScroll % 120 == 0)
				updatePipes();
			if (checkCollisionandBounds())
			{
				gameRunning = false;
				audio::AudioManager::get("Hit")->play();
				bird->fall();
				startMsg->m_Text = "Press ENTER to Restart";
				startMsg->update();
				highScore->m_Text = "High Score : " + std::to_string(highScoreCount);
				highScore->update();
				//audio::AudioManager::get("Die")->play();
			}
		}
		if(gameStarted)
			bird->update(m_Window, gameRunning);
	}

	void render() override
	{
		for(int i = 0; i < map + 4; i++)
			background->render(i, xScroll, map);
		for (int i = 0; i < 5 * 2; i++)
			pipe->render(i, xScroll, pipes[i]);
		bird->render();
		if (!gameStarted)
		{
			title->render();
			startMsg->render();
		}
		else 
		{
			if (!gameRunning)
			{
				startMsg->render();
				highScore->render();
			}
			score->render();
		}

	}

	bool isRunning()
	{
		return gameRunning;
	}

	void setRunning(bool flag)
	{
		gameRunning = flag;
	}

	bool isStarted()
	{
		return gameStarted;
	}

	void setStarted(bool flag)
	{
		gameStarted = flag;
	}
};

int main()
{
	Window* window = new Window("Flappy Bird!", 960, 540);

	FontManager::add(new Font("Flappy", "res/fonts/flappy.ttf", 128));
	FontManager::add(new Font("FlappyS", "res/fonts/flappy_score.ttf", 64));

	AudioManager::add(new Audio("Flap", "res/sounds/flap.wav"));
	AudioManager::add(new Audio("Hit", "res/sounds/hit.wav"));
	AudioManager::add(new Audio("Score", "res/sounds/score.wav"));
	AudioManager::add(new Audio("Die", "res/sounds/die.wav"));

	Game* game = new Game(window);
	game->start();

#ifdef XENO_PLATFORM_WEB
	std::function<void()> mainLoop = [&]() {
#else
	while (!window->closed())
	{
#endif
		window->clear();
		game->run();
		window->update();
		if (!game->isStarted() && window->isKeyPressed(GLFW_KEY_SPACE))
		{
			game->setStarted(true);
			game->setRunning(true);
		}

		if (game->isStarted() && !game->isRunning() && window->isKeyPressed(GLFW_KEY_ENTER))
		{
			delete game;
			game = new Game(window);
			game->start();
		}
#ifdef XENO_PLATFORM_WEB
	};
	emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#else
	}
#endif
	delete game;
	delete window;
	return 0;
}