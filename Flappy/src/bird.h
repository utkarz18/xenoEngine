#pragma once
#include <graphics/buffers/vertexarray.h>
#include <graphics/texture.h>
#include <graphics/shader.h>
#include <maths/maths.h>

using namespace xeno;
using namespace graphics;
using namespace maths;

class Bird
{
private:
	VertexArray* mesh;
	Texture* texture;
	Shader* shader;
	vec3 position = vec3();
	float rot;
	float delta = 0.0f;
	const float SIZE = 1.0f;

public:
	Bird();
	void update();
	void fall();
	void render();
	
	inline const unsigned int getY() const { return position.y; }
	inline const unsigned int getSize() const { return SIZE; }
};