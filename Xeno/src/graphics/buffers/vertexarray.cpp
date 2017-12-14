#include "vertexarray.h"

namespace xeno {namespace graphics {

		VertexArray::VertexArray(const void* vertices, const unsigned int* indices, float* textureCoordinates)
		{
			glGenVertexArrays(1, &m_ArrayID);
			glBindVertexArray(m_ArrayID);
			m_Vbo = new VertexBuffer(vertices, 4 * 3 * sizeof(float));

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

			m_Tbo = new VertexBuffer(textureCoordinates, 4 * 2 * sizeof(float));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

			m_Ibo = new IndexBuffer(indices, 6);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_ArrayID);
			delete m_Vbo, m_Ibo;
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_ArrayID);
			m_Ibo->bind();
		}

		void VertexArray::unbind() const
		{
			m_Ibo->unbind();
			glBindVertexArray(0);
		}

		void VertexArray::draw() const
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}

		void VertexArray::render() const
		{
			bind();
			draw();
		}


	}
}