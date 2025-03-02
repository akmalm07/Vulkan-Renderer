#include "pch.h"
#include "tools\include\mouse_control.h"


namespace tools
{


	MouseControl::MouseControl() = default;

	double MouseControl::GetMouseCurrentX() const
	{
		return _mouseCurrentX;
	}

	double MouseControl::GetMouseCurrentY() const
	{
		return _mouseCurrentY;
	}

	double MouseControl::GetMouseChangeX() const
	{
		return _mouseChangeX;
	}

	double MouseControl::GetMouseChangeY() const
	{
		return _mouseChangeY;
	}


	bool MouseControl::IsMouseButtonPressed() const
	{
		return _isMouseButtonPressed;
	}


	bool MouseControl::IsFirstClick() const
	{
		return _isFirstClick;
	}

}