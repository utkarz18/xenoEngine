#include "label.h"

namespace xeno { namespace graphics {

		Label::Label(std::string text, float x, float y, unsigned int color, float scale)
		{
			m_Text = text;
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
			m_Font = FontManager::get("Flappy");
			m_Scale = maths::vec2(scale, scale);
			init();
		}

		Label::Label(std::string text, float x, float y, Font* font, unsigned int color, float scale)
		{
			m_Text = text;
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
			m_Font = font;
			m_Scale = maths::vec2(scale, scale);
			init();
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
			validateFont(font);
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
			validateFont(font, size);
		}

		Label::~Label()
		{
			delete vb;
			delete ib;
			delete m_Mesh;
			delete m_Shader;
		}

		void Label::init()
		{
			m_Mesh = new VertexArray();

			vb = new VertexBuffer(NULL, 520 * sizeof(float));

			unsigned int* indices = new unsigned int[150];

			int offset = 0;
			for (int i = 0; i < 150; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			ib = new IndexBuffer(indices, 150);

			delete[] indices;

			m_Shader = new Shader("res/shaders/label.vert", "res/shaders/label.frag", "Label");

#ifdef XENO_PLATFORM_WEB
			m_BufferBase = new VertexData[520 * 4];
#endif
			m_Mesh->bind();
			vb->bind();

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
			glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));
			
			m_Mesh->unbind();
			vb->unbind();
			
			update();			
		}


		void Label::update()
		{
			m_Mesh->bind();
			vb->bind();

#ifdef XENO_PLATFORM_WEB
			m_Buffer = m_BufferBase;
#else
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#endif
			using namespace ftgl;

			const maths::vec2& scale = m_Scale;

			float x = m_Position.x;
			texture_font_t* ftFont = m_Font->getFTFont();

			const char* text = m_Text.c_str();
			texture_font_load_glyphs(ftFont, text);
			for (int i = 0; i < m_Text.length(); i++)
			{
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, text + i);
				if (glyph != NULL)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text + i - 1);
						x += kerning / scale.x;
					}

					float x0 = x + glyph->offset_x / scale.x;
					float y0 = m_Position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = maths::vec3(x0, y0, 0);
					m_Buffer->uv = maths::vec2(u0, v0);
					m_Buffer->color = m_Color;
					m_Buffer++;

					m_Buffer->vertex = maths::vec3(x0, y1, 0);
					m_Buffer->uv = maths::vec2(u0, v1);
					m_Buffer->color = m_Color;
					m_Buffer++;

					m_Buffer->vertex = maths::vec3(x1, y1, 0);
					m_Buffer->uv = maths::vec2(u1, v1);
					m_Buffer->color = m_Color;
					m_Buffer++;

					m_Buffer->vertex = maths::vec3(x1, y0, 0);
					m_Buffer->uv = maths::vec2(u1, v0);
					m_Buffer->color = m_Color;
					m_Buffer++;

					x += glyph->advance_x / scale.x;

					m_IndexCount += 6;
				}

			}
#ifdef XENO_PLATFORM_WEB
			glBufferSubData(GL_ARRAY_BUFFER, 0, (m_Buffer - m_BufferBase) * RENDERER_VERTEX_SIZE, m_BufferBase);
			m_Buffer = m_BufferBase;
#else
			glUnmapBuffer(GL_ARRAY_BUFFER);
#endif
			vb->unbind();
			m_Mesh->unbind();

			glGenTextures(1, &(m_Font->getFTAtlas()->id));
			glBindTexture(GL_TEXTURE_2D, m_Font->getFTAtlas()->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Font->getFTAtlas()->width, m_Font->getFTAtlas()->height,
				0, GL_RGB, GL_UNSIGNED_BYTE, m_Font->getFTAtlas()->data);
		}

		void Label::render()
		{
			m_Shader->enable();
			glDisable(GL_DEPTH_TEST);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, m_Font->getID());
			m_Mesh->render(ib);
			glEnable(GL_DEPTH_TEST);
			m_Shader->disable();
		}

		void Label::validateFont(const std::string& name, int size)
		{
			if (m_Font != nullptr)
				return;
			std::cout << "NULL Font = " << name;
			if (size > 0)
				std::cout << " , Size = " << size;
			std::cout << std::endl;

			m_Font = FontManager::get(name, size);
		}
	}
}