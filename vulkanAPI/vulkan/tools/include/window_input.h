#pragma once

#include "pch.h"

#include "tools\include\keys.h"


namespace vkUtil {


	/*-------------------------------*/
// Helper functions for passing into the ctors of the derived classes

	struct KeyCombInput
	{
		Keys number;
		Action action;
		Mods mod = Mods::None;;
	};

	struct MouseButtonInput
	{
		Mouse name;
		Action action;
	};

	struct AABButtonInput
	{
		float cordX;
		float cordY;
		float width;
		float height;
		Action action;
		Mouse button;
		std::string_view name;
	};



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

		MouseButtonB(const MouseButtonInput& in);

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

		AABButtonB(const AABButtonInput& in);

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

		KeyCombB(const KeyCombInput& in);

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

		AABButton(const MouseButtonInput& in, std::function<bool(Args...)> func, std::tuple<Args...> initial)
			: AABButtonB(in), _func(func), _args(std::move(initial))
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

		KeyComb(const KeyCombInput& in, std::function<bool(Args...)>& func, std::tuple<Args...> initial) : // well tested system
			KeyCombB(in), _func(func), _args(std::move(initial))
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

		MouseButton(const MouseButtonInput& in, std::function<bool(Args...)>& func, std::tuple<Args...> initial) :
			MouseButtonB(in), _func(func), _args(std::move(initial))
		{}

		void changeParameter(Args&&... args)
		{
			_args = std::make_tuple(std::forward<Args>(args)...);
		}

		bool execute() const override
		{
			_result = std::apply(_func, _args);// can use std::invoke if the args are not in a tuple
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