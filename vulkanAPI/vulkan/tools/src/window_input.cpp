#include "pch.h"

#include "tools\include\window_input.h"



namespace vkUtil {

	MouseButtonB::MouseButtonB() = default;

	MouseButtonB::MouseButtonB(const MouseButtonInput& in) :
		_button(in.name), _action(in.action), _pressed(false), _result(false)
	{}

	bool MouseButtonB::getPressed() const	
	{
		return _pressed;
	}

	void MouseButtonB::setPressed(bool value)
	{
		_pressed = value;
	}


	MouseButtonB::~MouseButtonB() = default;



	AABButtonB::AABButtonB() = default;

	AABButtonB::AABButtonB(const AABButtonInput& in)
		:_x(in.cordX), _y(in.cordY), _width(in.width), _height(in.height), _action(in.action), _button(in.button), _name(in.name), _result(false)
	{}


	bool AABButtonB::isClicked(float x, float y, Action action, Mouse button) const
	{
		if (action != _action || button != _button)
			return false;
		return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
	}

	AABButtonB::~AABButtonB() = default;



	KeyCombB::KeyCombB() :
		_charater(Keys::None), _trigger(Action::None), _mode(std::nullopt), _result(false)
	{}


	KeyCombB::KeyCombB(const KeyCombInput& in) :
		_charater(in.number), _trigger(in.action), _result(false)
	{
		if (in.mod != Mods::None)
		{
			_mode = in.mod;
		}
		else
		{
			_mode = std::nullopt;
		}

	}


	bool KeyCombB::isPressed(Keys number, Action action, Mods mod) const
	{
		if (number == _charater && action == _trigger)
		{
			if (_mode.has_value())
			{
				if (_mode.value() == mod)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}


	KeyCombB::~KeyCombB()
	{
		_mode = std::nullopt;
	}





}