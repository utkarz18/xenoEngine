#include "vertexarray.h"

namespace xeno {namespace graphics {

		VertexArray::VertexArray(float* vertices, unsigned short* indices, float* textureCoordinates)
		{
			glGenVertexArrays(1, &m_Vao);
			glBindVertexArray(m_Vao);

			//vertex buffer
			//m_Vbo = new Buffer(vertices, 12, 3);
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (textureCoordinates != nullptr)
				//texture
			{
				m_Tbo = new Buffer(vertices, 8, 2);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, m_Tbo->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			}

			//index buffer
			//m_Ibo = new IndexBuffer(indices, 6);
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);
			
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_Vao);
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_Vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		}

		void VertexArray::unbind() const
		{
			m_Ibo->unbind();
			glBindVertexArray(0);
		}

		void VertexArray::draw() const
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		}


	}
}