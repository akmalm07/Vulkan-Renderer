#include "pch.h"

#include "tools\include\window_input.h"



namespace tools {

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


	bool AABButtonB::is_clicked(float x, float y, Action action, Mouse button) const
	{
		if (action != _action || button != _button)
			return false;
		return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
	}

	AABButtonB::~AABButtonB() = default;



	KeyCombB::KeyCombB() :
		_charater(Keys::None), _trigger(Action::None), _mode(std::nullopt), _result(false)
	{}


	KeyCombB::KeyCombB(const KeyCombInputOne& in) :
		_trigger(in.action), _result(false)
	{
		_charater[0] = in.number;
		for (size_t i = 1; i < _charater.size(); i++)
		{
			_charater[i] = Keys::None;
		}

		if (in.mod != Mods::None)
		{
			_mode = in.mod;
		}
		else
		{
			_mode = std::nullopt;
		}

	}
	

	KeyCombB::KeyCombB(const KeyCombInputPoly& in) :
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


	bool KeyCombB::is_pressed(Keys number, Action action, Mods mod) const
	{
		if (_charater[0] == number && action == _trigger)
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

	bool KeyCombB::is_pressed(int number, int mod) const
	{
		if (_charater[1] == Keys::None)
		{
			if (number == INT(_charater[0]))
			{
				if (mod == 0 && !_mode.has_value())
				{
					return true;
				}
				else if (_mode.has_value() && mod == SIZET(_mode.value()))
				{
					return true;
				}
			}

			return false;
		}
		else
		{
			throw std::runtime_error("Invalid call to is_pressed(unsigned int, unsigned int) in KeyCombB");
		}
	}

	bool KeyCombB::is_pressed(GLFWwindow* win, int mod) const
	{
		if (_charater[1] == Keys::None)
		{
			throw std::runtime_error("Invalid call to is_pressed(std::array<unsigned int, KEY_MAX>, unsigned int) in KeyCombB");
		}

		bool all = true;
		for (const auto& key : _charater)
		{
			if (!(glfwGetKey(win, INT(key)) == INT(_trigger)))
			{
				all = false;
				break;
			}
		}

		if (
			(all == false) || 
			(mod == 0 && _mode.has_value()) || 
			(_mode.has_value() && mod != SIZET(_mode.value()))
			)
		{
			return false;
		}



		return true;
	}



	KeyCombB::~KeyCombB()
	{
		_mode = std::nullopt;
	}

}