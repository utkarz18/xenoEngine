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
	const float SIZE = 2.0f;

public:
	Plane(vec2 postion);
	~Plane();

	void init() override;
	void update(Window* m_Window, float timeElapsed);
	void render(mat4 vw_matrix);
	 
	inline const vec2 getPosition() const { return m_Position; }
	inline const float getSize() const { return SIZE; }
	inline Shader* getShader() const { return m_Shader; }
};