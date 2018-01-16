#pragma once

#include "../../ext/freetype-gl/freetype-gl.h"
#include <maths/vec2.h>
#include <string>

#ifndef XENO_PLATFORM_WEB
	#include <utils/log.h>
#endif

namespace xeno { namespace graphics {

		class Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			unsigned int m_Size;
			std::string m_Name;
			std::string m_Filename;

		public:
			Font(const std::string& name, const std::string& filename, int size);

			inline ftgl::texture_atlas_t* getFTAtlas() const { return m_FTAtlas; }
			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
			inline const unsigned int getID() const { return m_FTAtlas->id; }
			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFileName() const { return m_Filename; }
			inline const unsigned int getSize() const { return m_Size; }
		};

	}
}