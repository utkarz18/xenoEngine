#pragma once
#include <graphics/texture.h>
#include <graphics/shader.h>
#include <graphics/buffers/vertexarray.h>
#include <graphics/buffers/vertexBufferLayout.h>
#include <maths/maths.h>

namespace xeno{ namespace graphics{

class Renderable2D
{
protected:
	VertexArray* m_Mesh;
	Texture* m_Texture;
	Shader* m_Shader;

protected:
	virtual void init() = 0;
	virtual void update() { };
	virtual void render() { };

public:
	inline Shader* getShader() const { return m_Shader; }
};

}}