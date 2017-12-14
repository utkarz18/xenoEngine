#pragma once

#include <xenogl.h>
#include "vertexBuffer.h"
#include "indexbuffer.h"

namespace xeno { namespace graphics {

		class VertexArray
		{
		private:
			unsigned int m_ArrayID;
			VertexBuffer *m_Vbo, *m_Tbo;
			IndexBuffer *m_Ibo;
		public:
			VertexArray(const void* vertices, const unsigned int* indices, float* textureCoordinates);
			~VertexArray();

			void bind() const;
			void unbind() const;
			void draw() const;
			void render() const;
		};

	}
}