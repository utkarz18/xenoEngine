#pragma once
#include <graphics/renderable2D.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Background : public Renderable2D
{
private:
	VertexBuffer *vb, *tb;
	IndexBuffer *ib;
	vec2 m_Position;
public:
	Background();
	~Background();

	void init() override;
	void render(mat4 vw_matrix);
};