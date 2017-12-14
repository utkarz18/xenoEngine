#pragma once

#include <xenogl.h>

namespace xeno { namespace graphics {

		class VertexBuffer
		{
		private:
			unsigned int m_BufferID;
		public:
			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		};

	}
}