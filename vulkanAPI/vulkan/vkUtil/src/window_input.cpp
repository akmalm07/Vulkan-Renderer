#include "pch.h"

#include "window_input.h"



namespace vkUtil {

	UserInput::~UserInput() = default;


	MouseButtonB::MouseButtonB() :
		_button(Mouse::None), _action(Action::None), _pressed(false)
	{}

	MouseButtonB::MouseButtonB(Mouse name, Action action) :
		_button(name), _action(action), _pressed(false)
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

	AABButtonB::AABButtonB(float cordX, float cordY, float width, float height, Action action, Mouse button, std::string_view name)
		:_x(cordX), _y(cordY), _width(width), _height(height), _action(action), _button(button), _name(name)
	{}

	bool AABButtonB::isClicked(float x, float y, Action action, Mouse button) const
	{
		if (action != _action || button != _button)
			return false;
		return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
	}

	AABButtonB::~AABButtonB() = default;



	KeyCombB::KeyCombB() :
		_charater(Keys::None), _trigger(Action::None), _mode(std::nullopt)
	{}


	KeyCombB::KeyCombB(Keys number, Action action) :
		_charater(number), _trigger(action), _mode(std::nullopt)
	{
	}

	KeyCombB::KeyCombB(Keys number, Action action, Mods mode) :
		_charater(number), _trigger(action), _mode(mode)

	{}

	bool KeyCombB::isPressed(Keys number, Action action, Mods mod) const
	{
		if (number == _charater && action == _trigger)
		{
			if (_mode.has_value())
			{
				if (_mode.value() == mod)
					return true;
				else
					return false;
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