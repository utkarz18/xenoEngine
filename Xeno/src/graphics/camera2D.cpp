#include "camera2D.h"
namespace xeno{namespace graphics{

Camera2D::Camera2D(maths::vec3 position, float screenWidth, float screenHeight, float speed)
{
	m_Position = position;
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	m_MovementSpeed = speed;

	cameraMatrix = maths::mat4::identity();

	m_NeedsUpdate = true;
}

void Camera2D::update()
{
	if (m_NeedsUpdate)
	{
		cameraMatrix = maths::mat4::translate(maths::vec3(-m_Position.x, -m_Position.y, 0.0f));
		m_NeedsUpdate = false;
	}
}

}}