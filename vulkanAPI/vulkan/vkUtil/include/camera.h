#pragma once

#include "config.h"

#include "vkUtil\include\camera_bundle.h"
#include "tools\include\window.h"


namespace vkUtil
{

	class CameraT
	{
	public:
		CameraT();
		
		CameraT(CameraT&& other);

		CameraT(vkUtil::CameraBundlePerspective bundle);

		CameraT(vkUtil::CameraBundleOrthographic bundle);

		CameraT& operator=(CameraT&& other);

		void update();

		void setSpeed(float speed);
		float getSpeed() const;

		void setPosition(const glm::vec3& position);

		glm::mat4 getView() const;

		glm::mat4 getProjection() const;

		void setCommandsToWindow(vkUtil::WindowT& window);


		~CameraT();

	private:

		glm::mat4 _projection;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
		glm::vec3 _front;
		glm::vec3 _up;
		glm::vec3 _right;
		glm::vec3 _worldUp;

		float _speed;
		float _turnSpeed;
		float _aspect;

	private:
		void initalize(glm::vec3 worldUp, glm::vec3 startPYR, glm::vec3 position, glm::vec3 front, float speed, float turnSpeed);
	};

}

namespace vkType
{
	using Camera = vkUtil::CameraT;
}