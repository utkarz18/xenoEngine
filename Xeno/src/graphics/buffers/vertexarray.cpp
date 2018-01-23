#include "vertexarray.h"

namespace xeno { namespace graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_ArrayID);
			if (m_BufferLayout != nullptr)
				delete m_BufferLayout;
			for (int i = 0; i < m_buffers.size(); i++)
				if (m_buffers[i] != NULL) { delete m_buffers[i]; m_buffers[i] = NULL; }
		}

		void VertexArray::addBuffer(const VertexBuffer* vb)
		{
			m_buffers.push_back(vb);
		}

		void VertexArray::processBufers()
		{
			bind();
			unsigned int offset = 0;
			const auto& elements = m_BufferLayout->getElements();
			for (int i = 0; i < elements.size(); i++)
			{
				const auto& element = elements[i];
				const auto& buffer = m_buffers[i];
				buffer->bind();
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.count, element.type, element.normalized,
					element.stride, (const void*)offset);
				//offset += element.count * LayoutData::getSizeOfType(element.type);
			}
		}

		void VertexArray::setBufferLayout(const VertexBufferLayout* bufferLayout)
		{
			m_BufferLayout = bufferLayout;
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_ArrayID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArray::draw(unsigned int indexCount) const
		{
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		}

		void VertexArray::render(IndexBuffer* ib) const
		{
			bind();
			ib->bind();
			draw(ib->getCount());
			ib->unbind();
			unbind();
		}

	}
}