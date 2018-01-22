#include "texture.h"

namespace xeno { namespace graphics {
	
	bool isPowerOfTwo(int x);
	Texture::Texture(const std::string& name, const std::string& filename)
		:m_Filename(filename)
	{
		m_TID = load();
	}

	Texture::~Texture() 
	{
		glDeleteTextures(1, &m_TID);
	}

	unsigned int Texture::load()
	{
		unsigned int result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		unsigned char* pixels = load_image(m_Filename.c_str(), &m_Width, &m_Height, &m_Bits);
		if (m_Bits != 24 && m_Bits != 32) {
#ifndef XENO_PLATFORM_WEB
			XENO_ERROR("[Texture] Unsupported image bit-depth! (%d)", m_Bits);
#endif
			std::cout << "Unsupported Image!" << std::endl;
		}
		int internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
		unsigned int format = m_Bits == 32 ?
#ifdef XENO_PLATFORM_WEB
			GL_RGBA : GL_RGB;
#else
		GL_BGRA: GL_BGR;
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels);
		if (isPowerOfTwo(m_Width)  && isPowerOfTwo(m_Width)) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {       
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] pixels;

		return result;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool isPowerOfTwo(int x)
	{
		/*  x in the below expression is for the case when x is 0 */
		return x && (!(x&(x - 1)));
	}
}}