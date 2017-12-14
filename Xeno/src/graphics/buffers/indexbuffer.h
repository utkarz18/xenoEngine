#pragma once

#include <xenogl.h>

namespace xeno { namespace graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(const unsigned int* data, unsigned int count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }
		};

	}
}