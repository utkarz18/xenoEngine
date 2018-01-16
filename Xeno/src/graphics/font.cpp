#include "font.h"

namespace xeno{namespace graphics{
	
	Font::Font(const std::string& name, const std::string& filename, int size)
		:m_Name(name), m_Filename(filename), m_Size(size)
	{
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 3);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, m_Filename.c_str());
#ifndef XENO_PLATFORM_WEB
		XENO_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
#endif
	}
}}