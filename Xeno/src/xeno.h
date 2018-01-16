#pragma once

#ifdef XENO_PLATFORM_WEB
	#include <emscripten/emscripten.h>
#endif

#include "graphics/window.h"
#include "graphics/texture_manager.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/indexBuffer.h"

#include "maths/maths.h"
#include "utils/timer.h"

#include <functional>

namespace xeno {

	class Xeno
	{
	private:
		Timer* m_Timer;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;

	protected:
		Xeno()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Xeno()
		{
			delete m_Timer;
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
			m_Timer = new Timer();
		}

		void run()
		{
			if (m_Timer->elapsed() - updateTimer > updateTick)
			{
				update();
				updates++;
				updateTimer += updateTick;
			}
			render();
			frames++;
			if (m_Timer->elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_FramesPerSecond = frames;
				m_UpdatesPerSecond = updates;
				frames = 0;
				updates = 0;
				tick();
			}
		}

	};
}