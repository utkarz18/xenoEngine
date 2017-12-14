#pragma once

#ifdef XENO_PLATFORM_WEB
	#include <emscripten/emscripten.h>
#endif

#include "graphics/label.h"
#include "graphics/sprite.h"
#include "graphics/renderer2d.h"
#include "graphics/window.h"
#include "graphics/layers/layer.h"
#include "graphics/layers/group.h"
#include "graphics/texture_manager.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/indexBuffer.h"

#include "audio/audio.h"
#include "audio/audio_manager.h"

#include "maths/maths.h"
#include "utils/timer.h"

#include <functional>

#ifdef XENO_PLATFORM_WEB
static void dispatch_main(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}
#endif

namespace xeno {

	class Xeno
	{
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;

	protected:
		Xeno()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Xeno()
		{
			delete m_Timer;
			delete m_Window;
		}

		graphics::Window* createWindow(const char*title, int width, int height)
		{
			m_Window = new graphics::Window(title, width, height);
			return m_Window;
		}

		// Runs once upon initialization
		virtual void init() = 0;

		// Runs once per second
		virtual void tick() = 0;

		// Runs 60 times per second
		virtual void update() = 0;

		// Runs as faster as possible
		virtual void render() = 0;

		const unsigned int getFPS() const { return m_FramesPerSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }

	public:
		void start()
		{
			init();
			run();
		}

	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

#ifdef XENO_PLATFORM_WEB
			std::function<void()> mainLoop = [&]() {
#else
			while (!m_Window->closed())
			{
#endif
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
#ifdef XENO_PLATFORM_WEB
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#else
			}
#endif
		}
	};
}