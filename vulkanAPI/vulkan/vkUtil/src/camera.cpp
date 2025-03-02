#include "pch.h"

#include "vkUtil\include\camera.h"
#include "tools\include\window.h"
#include "tools\include\keys.h"


namespace tools
{
	CameraT::CameraT() = default;


	CameraT::CameraT(CameraT&& other) = default;

	CameraT& CameraT::operator=(CameraT&& other) = default;

	CameraT::CameraT(CameraBundlePerspective bundle)
	{
		_projection = glm::perspective(glm::radians(bundle.fov), bundle.aspectRatio, bundle.nearZ, bundle.farZ);

		initalize(bundle.worldUp, bundle.startPYR, bundle.position, bundle.front, bundle.speed, bundle.turnSpeed);

	}


	CameraT::CameraT(CameraBundleOrthographic bundle)
	{
		_projection = glm::ortho(bundle.left, bundle.right, bundle.bottom, bundle.top, bundle.nearZ, bundle.farZ);

		initalize(bundle.worldUp, bundle.startPYR, bundle.position, bundle.front, bundle.speed, bundle.turnSpeed);

	}

	void CameraT::initalize(glm::vec3 worldUp, glm::vec3 startPYR, glm::vec3 position, glm::vec3 front, float speed, float turnSpeed)
	{
		_worldUp = glm::normalize(worldUp);
		_position = position;
		_rotation = startPYR;
		_speed = speed;
		_front = front;
		_turnSpeed = turnSpeed;
		_target = _position + _front;

		update(position);
	}

	void CameraT::move_forward(double deltaTime, bool forwardOrBack)
	{
		if (forwardOrBack)
		{
			_position += _front * _speed * (float)deltaTime;
		}
		else
		{
			_position -= _front * _speed * (float)deltaTime;
		}
		_target = _position + _front;
	}

	void CameraT::move_up(double deltaTime, bool upOrDown)
	{
		if (upOrDown)
		{

			_position += _up * _speed * (float)deltaTime;
		}
		else
		{
			_position -= _up * _speed * (float)deltaTime;
		}
		_target = _position + _front;
	}

	void CameraT::move_right(double deltaTime, bool rightOrLeft)
	{
		if (rightOrLeft)
		{
			_position += _right * _speed * (float)deltaTime;
		}
		else
		{
			_position -= _right * _speed * (float)deltaTime;
		}
		_target = _position + _front;
	}


	void CameraT::update(const glm::vec3& position)
	{
		_front.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front.y = sin(glm::radians(_rotation.x));
		_front.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front = glm::normalize(_front);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));

		_position =	position;

		_view = std::move(glm::lookAt(_position, _target, _up));

	}

	void CameraT::update(Direction dir, double deltaTime)
	{
		move_dir(dir, deltaTime);

		_view = std::move(glm::lookAt(_position, _target, _up));
	}

	void CameraT::update(double xMove, double yMove, double deltaTime)// parameters are NOT being updated!! REVIEW THIS ERROR
	{
		_rotation.x += xMove * _turnSpeed * deltaTime;
		_rotation.y += yMove * _turnSpeed * deltaTime;

		glm::clamp(_rotation.y, -180.0f, 180.0f);
		glm::clamp(_rotation.x, -89.0f, 89.0f);

		_front.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front.y = sin(glm::radians(_rotation.x));
		_front.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front = glm::normalize(_front);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));

		_target = _position + _front;

		_view = std::move(glm::lookAt(_position, _target, _up));
	}

	void CameraT::update(Direction dir, double xMove, double yMove, double deltaTime)
	{
		_rotation.x += xMove * _turnSpeed * deltaTime;
		_rotation.y += yMove * _turnSpeed * deltaTime;

		glm::clamp(_rotation.y, -180.0f, 180.0f);
		glm::clamp(_rotation.x, -89.0f, 89.0f);

		_front.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front.y = sin(glm::radians(_rotation.x));
		_front.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front = glm::normalize(_front);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));

		move_dir(dir, deltaTime);

		_view = std::move(glm::lookAt(_position, _target, _up));
	}


	bool CameraT::event_key(Direction dir, double deltaTime)
	{
		update(dir, deltaTime);
		return true;
	}

	bool CameraT::event_key(double xMove, double yMove, double deltaTime)
	{
		update(xMove, yMove, deltaTime);
		return true;
	}


	void CameraT::set_speed(float speed)
	{
		_speed = speed;
	}


	float CameraT::get_speed() const
	{
		return _speed;
	}


	void CameraT::set_position(const glm::vec3& position)
	{
		_position = position;
	}


	glm::mat4 CameraT::get_view() 
	{
		return _view;
	}


	glm::mat4 CameraT::get_projection() const
	{
		return _projection;
	}
	

	void CameraT::set_commands_to_window(tools::WindowT& window)
	{

		std::array<KeyCombInputOne, 10> input = 
		{
		KeyCombInputOne(Keys::W, Action::Press),
		KeyCombInputOne(Keys::S, Action::Press),
		KeyCombInputOne(Keys::A, Action::Press),
		KeyCombInputOne(Keys::D, Action::Press),
		KeyCombInputOne(Keys::Q, Action::Press),
		KeyCombInputOne(Keys::E, Action::Press),
		KeyCombInputOne(Keys::Up, Action::Press),
		KeyCombInputOne(Keys::Down, Action::Press),
		KeyCombInputOne(Keys::Right, Action::Press),
		KeyCombInputOne(Keys::Left, Action::Press)

		};
		std::array<Direction, 10> dirs = 
		{
		Direction::Up,
		Direction::Down,
		Direction::Left,
		Direction::Right,
		Direction::Forward,
		Direction::Backward,
		Direction::TurnUp,
		Direction::TurnDown,
		Direction::TurnRight,
		Direction::TurnLeft
		};

		glm::mat4& matrix = _view;
		double doub = 0.0;
		double& zer0 = doub;
		std::array<std::function<bool(double)>, 6> moveFuncs;
		std::array<std::function<bool(double, double, double)>, 4> turnFuncs;

		for (size_t i = 0; i < moveFuncs.size(); i++)
		{
			moveFuncs[i] = [this, dir = dirs[i] ](double deltaTime) -> bool
			{
				return this->event_key(dir, deltaTime);
			};
		}

		for (size_t i = 0; i < turnFuncs.size(); i++)
		{
			turnFuncs[i] = [this, dir = dirs[i+6] ](double xMove, double yMove, double deltaTime) -> bool
			{
				return this->event_key(xMove, yMove, deltaTime);
			};
		}
			
			
		for (size_t i = 0; i < moveFuncs.size(); i++)
		{
			window.AddKeyComb
			(
				true,
				input[i],
				moveFuncs[i],
				0.0
			);
		}
		

		for (size_t i = 0; i < turnFuncs.size(); i++)
		{
			window.AddKeyComb
			(
				true,
				input[i+6],
				turnFuncs[i],
				0.0, 0.0, 0.0
			);
		}

	}

	void CameraT::move_dir(Direction dir, double deltaTime)
	{
		switch (dir)
		{
		case Direction::Forward:
			move_forward(deltaTime, true);
			break;
		case Direction::Backward:
			move_forward(deltaTime, false);
			break;
		case Direction::Left:
			move_right(deltaTime, false);
			break;
		case Direction::Right:
			move_right(deltaTime, true);
			break;
		case Direction::Up:
			move_up(deltaTime, true);
			break;
		case Direction::Down:
			move_up(deltaTime, false);
			break;
		case Direction::Down | Direction::Forward:
			move_forward(deltaTime, true);
			move_up(deltaTime, false);
			break;
		case Direction::Down | Direction::Backward:
			move_forward(deltaTime, false);
			move_up(deltaTime, false);
			break;
		case Direction::Up | Direction::Forward:
			move_forward(deltaTime, true);
			move_up(deltaTime, true);
			break;
		case Direction::Up | Direction::Backward:
			move_forward(deltaTime, false);
			move_up(deltaTime, true);
			break;
		case Direction::Up | Direction::Left:
			move_right(deltaTime, false);
			move_up(deltaTime, true);
			break;
		case Direction::Up | Direction::Right:
			move_right(deltaTime, true);
			move_up(deltaTime, true);
			break;
		case Direction::Down | Direction::Left:
			move_right(deltaTime, false);
			move_up(deltaTime, false);
			break;
		case Direction::Down | Direction::Right:
			move_right(deltaTime, true);
			move_up(deltaTime, false);
			break;
		case Direction::Backward | Direction::Left:
			move_right(deltaTime, false);
			move_forward(deltaTime, false);
			break;
		case Direction::Backward | Direction::Right:
			move_forward(deltaTime, false);
			move_right(deltaTime, true);
			break;
		case Direction::Forward | Direction::Left:
			move_right(deltaTime, false);
			move_forward(deltaTime, true);
			break;
		case Direction::Forward | Direction::Right:
			move_right(deltaTime, true);
			move_forward(deltaTime, true);
			break;
		case Direction::None:
			break;
		}
	}

	void CameraT::move_and_turn_dir(Direction dir, double pitch, double yaw, double deltaTime)
	{
		switch (dir)
		{
		case Direction::Forward | Direction::TurnUp:
			move_forward(deltaTime, true);
			_rotation.x += pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Forward | Direction::TurnDown:
			move_forward(deltaTime, true);
			_rotation.x -= pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Forward | Direction::TurnLeft:
			move_forward(deltaTime, true);
			_rotation.y -= yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Forward | Direction::TurnRight:
			move_forward(deltaTime, true);
			_rotation.y += yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Backward | Direction::TurnUp:
			move_forward(deltaTime, false);
			_rotation.x += pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Backward | Direction::TurnDown:
			move_forward(deltaTime, false);
			_rotation.x -= pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Backward | Direction::TurnLeft:
			move_forward(deltaTime, false);
			_rotation.y -= yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Backward | Direction::TurnRight:
			move_forward(deltaTime, false);
			_rotation.y += yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Left | Direction::TurnUp:
			move_right(deltaTime, false);
			_rotation.x += pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Left | Direction::TurnDown:
			move_right(deltaTime, false);
			_rotation.x -= pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Left | Direction::TurnLeft:
			move_right(deltaTime, false);
			_rotation.y -= yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Left | Direction::TurnRight:
			move_right(deltaTime, false);
			_rotation.y += yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Right | Direction::TurnUp:
			move_right(deltaTime, true);
			_rotation.x += pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Right | Direction::TurnDown:
			move_right(deltaTime, true);
			_rotation.x -= pitch * _turnSpeed * deltaTime;
			break;
		case Direction::Right | Direction::TurnLeft:
			move_right(deltaTime, true);
			_rotation.y -= yaw * _turnSpeed * deltaTime;
			break;
		case Direction::Right | Direction::TurnRight:
			move_right(deltaTime, true);
			_rotation.y += yaw * _turnSpeed * deltaTime;
			break;
		}
	}

	void CameraT::turn_dir(Direction dir, double pitch, double yaw, double deltaTime)
	{
		switch (dir)
		{
		case Direction::TurnUp:
			_rotation.x += pitch * _turnSpeed * deltaTime;
			break;
		case Direction::TurnDown:
			_rotation.x -= pitch * _turnSpeed * deltaTime;
			break;
		case Direction::TurnLeft:
			_rotation.y -= yaw * _turnSpeed * deltaTime;
			break;
		case Direction::TurnRight:
			_rotation.y += yaw * _turnSpeed * deltaTime;
			break;
		}
	}


	CameraT::~CameraT() = default;

}//namespace vkUtil


//void CameraT::debug_position()
//{
//	std::cout << "Camera Position: (" << _position.x << ", " << _position.y << ", " << _position.z << ")\n";
//}