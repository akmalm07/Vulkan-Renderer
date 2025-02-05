#pragma once

#include "pch.h"

#include "tools\include\keys.h"


namespace vkUtil {


	template<class ... Args>
	struct MouseButton;	// forward declaration

	template<class ... Args>
	struct AABButton;

	template<class ... Args>
	struct KeyComb;


	struct MouseButtonB
	{
	public:

		MouseButtonB();

		MouseButtonB(Mouse name, Action action);

		virtual bool execute() const = 0;

		template <class ... Args>
		void changeParameters(Args&&... args)
		{
			dynamic_cast<MouseButton<Args...>*>(this)->changeParameter(std::forward<Args>(args)...); //dynamic cast to the derived class
		}

		bool getPressed() const;

		void setPressed(bool value);

		virtual ~MouseButtonB();
	protected:
		bool _pressed;
		Mouse _button;
		Action _action;
		bool _result;

	};



	struct AABButtonB
	{
	public:


		AABButtonB();

		AABButtonB(float cordX, float cordY, float width, float height, Action action, Mouse button, std::string_view name);

		AABButtonB(float cordX, float cordY, float width, float height, Action action, Mouse button);

		virtual bool execute() const = 0;

		bool isClicked(float x, float y, Action action, Mouse button) const;

		template <class ... Args>
		void changeParameters(Args&&... args)
		{
			dynamic_cast<AABButton<Args...>*>(this)->changeParameter(std::forward<Args>(args)...);
		}

		virtual ~AABButtonB();

	protected:
		float _x;
		float _y;
		float _width;
		float _height;
		Action _action;
		Mouse _button;
		std::string_view _name;
		bool _result;

	};


	struct KeyCombB
	{
	public:

		KeyCombB();

		KeyCombB(Keys number, Action action);

		KeyCombB(Keys number, Action action, Mods mod);

		bool isPressed(Keys number, Action action, Mods mod) const;

		virtual bool execute() const = 0;

		template <class ... Args>
		void changeParameters(Args&&... args)
		{
			dynamic_cast<KeyComb<Args...>*>(this)->changeParameter(std::forward<Args>(args)...); //dynamic cast to the derived class 
		}

		virtual ~KeyCombB();
	protected:
		Keys _charater;
		std::optional<Mods> _mode; //optional because it is not always needed
		Action _trigger;
		bool _result;

	};




	//----------------------------------------------


	//Templated derived classes for user input
	template<class ... Args>
	struct AABButton : AABButtonB
	{
	public:

		AABButton(float cordX, float cordY, float sizeX, float sizeY, Action action, Mouse mouse, std::function<bool(Args...)>& func, std::tuple<Args...> initial)
			: AABButtonB(cordX, cordY, sizeX, sizeY, action, mouse), _func(func), _args(std::move(initial))
		{}

		bool execute() const override
		{
			_result = std::apply(_func, _args);
			return _result;
		}

		void changeParameter(Args&&... args)
		{
			_args = std::make_tuple(std::forward<Args>(args)...);
		}

		bool operator()() const
		{
			return execute();
		}


		~AABButton()  override
		{
			_func = nullptr;
		}

	private:
		std::function<bool(Args...)> _func;

		std::tuple<Args...> _args;
	};


	template<class ... Args>
	struct KeyComb : KeyCombB
	{
	public:

		KeyComb(Keys number, Action action, std::function<bool(Args...)>& func, std::tuple<Args...> initial) :
			KeyCombB(number, action), _func(func), _args(std::move(initial))
		{}

		KeyComb(Keys number, Action action, Mods mod, std::function<bool(Args...)>& func, std::tuple<Args...> initial) :
			KeyCombB(number, action, mod), _func(func), _args(std::move(initial))
		{}

		void changeParameter(Args&&... args)
		{
			_args = std::make_tuple(std::forward<Args>(args)...);
		}

		bool execute() const override
		{
			_result = std::apply(_func, _args);
			return _result;
		}

		bool operator()() const	
		{
			return execute();
		}


		~KeyComb() override
		{
			_func = nullptr;
		}

	private:
		std::function<bool(Args...)> _func;
		std::tuple<Args...> _args;

	};




	template<class ... Args>
	struct MouseButton : MouseButtonB
	{
	public:

		MouseButton(Mouse name, Action action, std::function<bool(Args...)>& func, std::tuple<Args...> initial) :
			MouseButtonB(name, action), _func(func), _args(std::move(initial))
		{}

		void changeParameter(Args&&... args)
		{
			_args = std::make_tuple(std::forward<Args>(args)...);
		}

		bool execute() const override
		{
			_result = std::apply(_func, _args);
			return _result;
		}


		bool operator()() const
		{
			return execute();
		}


	private:
		std::function <bool(Args...)> _func;
		std::tuple<Args...> _args;

	};

}