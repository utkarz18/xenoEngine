#pragma once

#include <vector>
#include "font.h"

namespace xeno {namespace graphics{ 

	class FontManager
	{
	private:
		static std::vector<Font*> m_Fonts;
	
	private:
		FontManager() { }

	public:
		static void add(Font* font);
		static Font* get();
		static Font* get(const std::string& name);
		static Font* get(const std::string& name, unsigned int size);
		static void clean();
	};
}}