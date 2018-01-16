#pragma once

#include <xenogl.h>
#include "vertexBuffer.h"
#include "indexbuffer.h"
#include "vertexBufferLayout.h"

namespace xeno { namespace graphics {

		class VertexArray
		{
		private:
			unsigned int m_ArrayID;
			const VertexBufferLayout* m_BufferLayout = nullptr;
			std::vector<const VertexBuffer*> m_buffers;
		public:
			VertexArray();
			~VertexArray();

			void addBuffer(const VertexBuffer* vb);
			void setBufferLayout(const VertexBufferLayout* bufferLayout);
			void processBufers();
			void bind() const;
			void unbind() const;
			void draw(unsigned int indexCount) const;
			void render(IndexBuffer* ib) const;
		};

	}
}