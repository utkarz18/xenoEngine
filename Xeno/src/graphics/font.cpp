#include "font.h"

namespace xeno{namespace graphics{
	
	Font::Font(const std::string& name, const std::string& filename, int size)
		:m_Name(name), m_Filename(filename), m_Size(size), m_Scale(maths::vec2(1, 1))
	{
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, m_Filename.c_str());
		XENO_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
	}

	void Font::setScale(float x, float y)
	{
		m_Scale = maths::vec2(x, y);
	}
}}