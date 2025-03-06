#pragma once

#include "config.h"

#include "vkUtil\include\camera_bundle.h"
#include "tools\include\keys.h"


namespace tools
{
	class WindowT;
}

namespace tools

{
	class CameraT
	{
	public:
		CameraT();
		
		CameraT(CameraT&& other);

		CameraT& operator=(CameraT&& other);

		CameraT(CameraBundlePerspective bundle);

		CameraT(CameraBundleOrthographic bundle);

		void update(const glm::vec3& position);
		
		void update(Direction dir, double deltaTime);
		
		void update(double xMove, double yMove, double deltaTime);
		
		void update(Direction dir, double xMove, double yMove, double deltaTime);
		
		void set_speed(float speed);
		float get_speed() const;

		void set_position(const glm::vec3& position);

		glm::mat4 get_view();

		glm::mat4 get_projection() const;

		void set_commands_to_window(tools::WindowT& window);

		void move_dir(Direction dir, double deltaTime);
		
		void move_and_turn_dir(Direction dir, double pitch, double yaw, double deltaTime);

		void turn_dir(Direction dir, double pitch, double yaw, double deltaTime);

		bool is_moving();

		~CameraT();

	private:

		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _position;
		glm::vec3 _prevPosition;
		glm::vec3 _rotation;
		glm::vec3 _prevRotation;
		glm::vec3 _scale;
		glm::vec3 _front;
		glm::vec3 _up;
		glm::vec3 _right;
		glm::vec3 _worldUp;
		glm::vec3 _direction;
		glm::vec3 _target;

		float _speed;
		float _turnSpeed;
		float _aspect;

	private:
		void initalize(glm::vec3 worldUp, glm::vec3 startPYR, glm::vec3 position, glm::vec3 front, float speed, float turnSpeed);

		void move_forward(double deltaTime, bool forwardOrBack);
		void move_up(double deltaTime, bool upOrDown);
		void move_right(double deltaTime, bool rightOrLeft);

		bool event_key(Direction dir, double deltaTime);
		bool event_key(double xMove, double yMove, double deltaTime);

		//void debug_position();
	};

}

namespace vkType
{
	using Camera = tools::CameraT;
}