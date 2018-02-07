#include <maths/maths.h>

namespace xeno{ namespace graphics{

	enum Camera_Movement {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Camera2D
	{
	private:
		int m_ScreenWidth, m_ScreenHeight;
		float m_MovementSpeed;
		bool m_NeedsUpdate;
		maths::vec2 m_Position;
		maths::mat4 orthoMatrix;
		maths::mat4 cameraMatrix;

	public:
		Camera2D(maths::vec3 position, float screenWidth, float screenHeight, float speed);
		void update();
		void processCameraMovements(Camera_Movement direction, float deltaTime);

		void setPosition(maths::vec2 position) { m_Position = position; m_NeedsUpdate = true; }

		inline const maths::vec2& getPosition() const { return m_Position; }
		inline const maths::mat4& getCameraMatrix() const { return cameraMatrix; }
	};
}}