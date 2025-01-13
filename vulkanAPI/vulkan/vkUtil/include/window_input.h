#pragma once

#include "vkUtil\include\keys.h"


namespace vkUtil {



	struct AABButtonB
	{
	public:

		float xCord;
		float yCord;
		float width;
		float height;

		AABButtonB();

		AABButtonB(float cordX, float cordY, float sizeX, float sizeY)
		{
			xCord = cordX;
			yCord = cordY;
			width = sizeX;
			height = sizeY;
		}

		virtual ~AABButtonB()
		{
			xCord = 0;
			yCord = 0;
			width = 0;
			height = 0;
		}
	};

	AABButtonB::AABButtonB() = default;


	template<class R, class ... Args>
	struct AABButton : AABBButtonB
	{
	public:

		AABButton(float cordX, float cordY, float sizeX, float sizeY, std::function<R(Args...)>& func)
			: AABButtonB(cordX, cordY, sizeX, sizeY)
		{
			function = func;
		}

		std::function<R(Args...)> function;
	};


	struct KeyCombB
	{
		Keys charater;

		std::optional<Mods> mode;

		Action trigger;

		KeyCombB();

		KeyCombB(Keys number, Action action)
		{
			charater = number;
			trigger = action;
		}

		KeyCombB(Keys number, Action action, Mods mod)
		{
			charater = number;
			trigger = action;
			mode = mod;
		}

		~KeyCombB()
		{
			charater = Keys::None; 
			mode = std::nullopt;
		}

	};

	template<class R, class ... Args>
	struct KeyComb
	{
	public:

		KeyComb(Keys number, Action action, std::function<R(Args...)>& func) : KeyCombB(number, action)
		{
			function = func;
		}

		KeyComb(Keys number, Action action, Mods mod, std::function<R(Args...)>& function) : KeyCombB(number, action, mod)
		{
			function = func;
		}

		std::function<R(Args...)> function;

	};


	struct MouseButtonB
	{
		bool pressed;
		Mouse button;

		MouseButtonB();

		MouseButtonB(Mouse name)
		{
			button = name;
			pressed = false;
		}

		~MouseButtonB()
		{
			button = Mouse::None;
			pressed = false;
		}
	};


	template<class R, class ... Args>
	struct MouseButton
	{
	public:
		
		MouseButton(Mouse name, std::function<R(Args...)>& func) : MouseButtonB(name)
		{ 
			function = func;
		}
		std::function<R(Args...) function;
	};

}