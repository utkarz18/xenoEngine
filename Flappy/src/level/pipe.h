#pragma once
#include <graphics/renderable2D.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Pipe : public Renderable2D
{
private:
	VertexBuffer *vb, *tb;
	IndexBuffer *ib;
	float m_Width = 1.5f, m_Height = 8.0f;
	vec3 m_Position = vec3();
	mat4 ml_matrix;

public:
	Pipe();
	Pipe(float x, float y);
	~Pipe();

	void init() override;
	void render(int i, int xScroll, Pipe* pipe);

	inline const float getX() const { return m_Position.x; }
	inline const float getY() const { return m_Position.y; }
	inline const float getWidth() const{ return m_Width; }
	inline const float getHeight() const { return m_Height; }
	inline const mat4 getModelMatrix() const { return ml_matrix; }
};
