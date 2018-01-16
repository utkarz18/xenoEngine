#pragma once
#include <vector>

struct LayoutData
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	unsigned int stride;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
	}
};


class VertexBufferLayout
{
private:
	std::vector<LayoutData> m_Elements;

public:
	VertexBufferLayout() {}

	void push(unsigned int count, unsigned int type, unsigned char normalized)
	{
		unsigned int stride = count * LayoutData::getSizeOfType(type);
		m_Elements.push_back( { type, count, normalized, stride } );
	}

	inline const std::vector<LayoutData>& getElements() const { return m_Elements; }
};