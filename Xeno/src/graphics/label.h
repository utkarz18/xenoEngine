#pragma once

#include "renderable2D.h"
#include "font_manager.h"

namespace xeno { namespace graphics {

		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;
			unsigned int color;
		};

		#define RENDERER_VERTEX_SIZE sizeof(VertexData)

		class Label : public Renderable2D
		{
		public:
			Font* m_Font;
			std::string m_Text;
			maths::vec3 m_Position;
			maths::vec2 m_Scale;
			VertexData* m_Buffer;
			VertexBuffer* vb;
			IndexBuffer* ib;
			unsigned int m_Color;
			unsigned int m_IndexCount = 0;
			float x, y;
#ifdef XENO_PLATFORM_WEB
			VertexData* m_BufferBase;
#endif

		public:
			Label(std::string text, float x, float y, unsigned int color, float scale);
			Label(std::string text, float x, float y, Font* font, unsigned int color, float scale);
			Label(std::string text, float x, float y, const std::string& font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
			~Label();
			void init() override;
			void update() override;
			void render() override;
			void validateFont(const std::string& name, int size = -1);
		};

	}
}