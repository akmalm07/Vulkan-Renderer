#include "pch.h"

#include "vkUtil\include\camera.h"
#include "tools\include\keys.h"


namespace vkUtil
{
	CameraT::CameraT() = default;


	CameraT::CameraT(CameraT&& other) = default;


	CameraT::CameraT(vkUtil::CameraBundlePerspective bundle)
	{
		_projection = glm::perspective(glm::radians(bundle.fov), bundle.aspectRatio, bundle.nearZ, bundle.farZ);

		initalize(bundle.worldUp, bundle.startPYR, bundle.position, bundle.front, bundle.speed, bundle.turnSpeed);

	}


	CameraT::CameraT(vkUtil::CameraBundleOrthographic bundle)
	{
		_projection = glm::ortho(bundle.left, bundle.right, bundle.bottom, bundle.top, bundle.nearZ, bundle.farZ);

		initalize(bundle.worldUp, bundle.startPYR, bundle.position, bundle.front, bundle.speed, bundle.turnSpeed);

	}

	CameraT& CameraT::operator=(CameraT&& other) = default;


	void CameraT::initalize(glm::vec3 worldUp, glm::vec3 startPYR, glm::vec3 position, glm::vec3 front, float speed, float turnSpeed)
	{
		_worldUp = glm::normalize(worldUp);
		_position = position;
		_rotation = startPYR;
		_speed = speed;
		_front = front;
		_turnSpeed = turnSpeed;

		update();
	}


	void CameraT::update()
	{
		_front.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front.y = sin(glm::radians(_rotation.x));
		_front.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_front = glm::normalize(_front);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));
	}


	void CameraT::setSpeed(float speed)
	{
		_speed = speed;
	}


	float CameraT::getSpeed() const
	{
		return _speed;
	}


	void CameraT::setPosition(const glm::vec3& position)
	{
		_position = position;
	}


	glm::mat4 CameraT::getView() const
	{
		return glm::lookAt(_position, _position + _front, _up);
	}


	glm::mat4 CameraT::getProjection() const
	{
		return _projection;
	}

	void CameraT::setCommandsToWindow(vkUtil::WindowT& window)
	{
		using namespace vkUtil;

		KeyCombInput input;
		input.number = Keys::W;
		input.action = Action::Press;

		window.AddKeyComb(
			input,
			[this](float deltaTime) -> bool
			{
				_position += _front * _speed * deltaTime;
				return true;
			},
			0.0f);


		input.number = Keys::S;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_position -= _front * _speed * deltaTime;
				return true;
			},
			0.0f);


		input.number = Keys::A;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_position -= _right * _speed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::D;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_position += _right * _speed * deltaTime;
				return true;
			},
			0.0f);


		input.number = Keys::Q;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_position -= _up * _speed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::S;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_position += _up * _speed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::Up;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_rotation.x += _turnSpeed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::Down;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_rotation.x -= _turnSpeed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::Left;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_rotation.y -= _turnSpeed * deltaTime;
				return true;
			},
			0.0f);

		input.number = Keys::Right;
		window.AddKeyComb(
			input,
			[this](float deltaTime)
			{
				_rotation.y += _turnSpeed * deltaTime;
				return true;
			},
			0.0f);
	}

	CameraT::~CameraT() = default;

}//namespace vkUtil