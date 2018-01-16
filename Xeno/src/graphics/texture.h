#pragma once

#include <string>
#include <iostream>

#include <xenogl.h>

#ifndef XENO_PLATFORM_WEB
	#include <utils/log.h>
#endif 

#include <utils/imageUtils.h>

namespace xeno {namespace graphics {
	
	class Texture
	{
	private:
		std::string m_Name, m_Filename;
		unsigned int m_TID;
		int m_Width, m_Height;
		unsigned int m_Bits;

	public:
		Texture(const std::string& name, const std::string& filename);
		~Texture();
		void bind() const;
		void unbind() const;

		inline const std::string& getName() const { return m_Name; }
		inline const unsigned int getID() const { return m_TID; }
		inline const unsigned int getWidth() const { return m_Width; }
		inline const unsigned int getHeight() const { return m_Height; }
	
	private:
		unsigned int load();
	};

}}