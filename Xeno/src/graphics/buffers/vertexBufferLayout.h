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
		unsigned int value;
		switch (type)
		{
		case GL_FLOAT:		    value = 4;  break;
		case GL_UNSIGNED_INT:	value = 4;  break;
		case GL_UNSIGNED_BYTE:	value = 1;  break;
		}
		return value;
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