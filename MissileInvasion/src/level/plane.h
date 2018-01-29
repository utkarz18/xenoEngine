#pragma once
#include <graphics/renderable2D.h>
#include <graphics/window.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Plane : public Renderable2D
{
private:
	VertexBuffer *vb, *tb;
	IndexBuffer *ib;
	vec3 m_Position;
	float rot;
	const float SIZE = 1.0f;

public:
	Plane(vec3 postion);
	~Plane();

	void init() override;
	void update(const Window* window);
	void fall();
	void render() override;
	 
	inline const float getY() const { return m_Position.y; }
	inline const float getSize() const { return SIZE; }
	inline Shader* getShader() const { return m_Shader; }
};