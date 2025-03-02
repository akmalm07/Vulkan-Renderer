#pragma once

#include "config.h"
#include "tools\include\keys.h"
#include "tools\include\window_input.h"


namespace tools
{

	class MouseControl
	{
	public:

		MouseControl();


		double GetMouseCurrentX() const;

		double GetMouseCurrentY() const;


		double GetMouseChangeX() const;

		double GetMouseChangeY() const;


		bool IsMouseButtonPressed() const;


		bool IsFirstClick() const;


	private:

		bool _isFirstClick = false;

		double _mouseChangeX = 0.0;
		double _mouseChangeY = 0.0;

		double _mouseCurrentX = 0.0;
		double _mouseCurrentY = 0.0;

		bool _mouseFirstMoved = true;

		bool _isMouseButtonPressed = false;
	};

}