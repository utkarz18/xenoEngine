#pragma once
#include <graphics/renderable2D.h>
#include <graphics/window.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Bird : public Renderable2D
{
private:
	VertexBuffer *vb, *tb;
	IndexBuffer *ib;
	vec3 m_Position;
	float rot;
	float delta = 0.0f;
	const float SIZE = 1.0f;

public:
	Bird(vec3 postion);
	~Bird();

	void init() override;
	void update(const Window* window, const bool& gameOver);
	void fall();
	void render() override;
	 
	inline const float getY() const { return m_Position.y; }
	inline const float getSize() const { return SIZE; }
	inline Shader* getShader() const { return m_Shader; }
};