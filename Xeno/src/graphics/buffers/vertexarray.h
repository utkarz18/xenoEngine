#pragma once

#include <vector>
#include <xenogl.h>
#include "buffer.h"
#include "indexbuffer.h"

namespace xeno { namespace graphics {

		class VertexArray
		{
		private:
			unsigned int m_Vao, vbo, ibo;
			Buffer *m_Vbo, *m_Tbo;
			IndexBuffer *m_Ibo;
		public:
			VertexArray(float* vertices, unsigned short* indices, float* textureCoordinates);
			~VertexArray();

			void bind() const;
			void unbind() const;
			void draw() const;
		};

	}
}