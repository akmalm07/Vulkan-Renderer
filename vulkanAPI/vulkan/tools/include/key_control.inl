#pragma once


namespace tools
{
	template<class F, class ... Args>
	void KeyControl::AddKeyComb(const KeyCombInputPoly& input, F&& function, Args&&... args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		_keyCombsPoly.emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
		);
	}

	template<vkType::IsClass T, class ...Args>
	inline void KeyControl::AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), std::tuple<Args...>&& args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		std::function<bool(Args...)> function = [this](Args&&... args)
			{
				return (this->*func)(std::forward<Args>(args)...);
			};
		_keyCombsPoly.emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<std::tuple<Args...>>(args))
		);
	}

	template<vkType::IsClass T, class ...Args>
	inline void KeyControl::AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), Args&&... args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		std::function<bool(Args...)> function = [this](Args&&... args)
			{
				return (this->*func)(std::forward<Args>(args)...);
			};
		_keyCombsPoly.emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
		);
	}

	template<class ...Args>
	inline void KeyControl::AddKeyComb(const KeyCombInputPoly& input, std::function<bool(Args...)> func, Args && ...args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		_keyCombsPoly.emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(func), std::forward<Args>(args)...)
		);

	}


	template<class F, class ... Args>
	void KeyControl::AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, F&& function, Args&&... args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		if (repeatAsWell)
		{
			auto func = function;
			_keyCombs[SIZET(Action::Repeat)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<F>(func), std::forward<Args>(args)...)
			);
		}
		_keyCombs[SIZET(input.action)].emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
		);

	}

	template<vkType::IsClass T, class ...Args>
	inline void KeyControl::AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, bool(T::* func)(Args...), std::tuple<Args...>&& args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		std::function<bool(Args...)> function = [this](Args&&... args)
			{
				return (this->*func)(std::forward<Args>(args)...);
			};
		if (repeatAsWell)
		{
			auto funct = function;
			_keyCombs[SIZET(Action::Repeat)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(funct), std::forward<std::tuple<Args...>>(args))
			);
		}

		_keyCombs[SIZET(input.action)].emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<std::tuple<Args...>>(args))
		);
	}

	template<vkType::IsClass T, class ...Args>
	inline void KeyControl::AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, bool(T::* func)(Args...), Args&&... args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
		std::function<bool(Args...)> function = [this](Args&&... args)
			{
				return (this->*func)(std::forward<Args>(args)...);
			};
		if (repeatAsWell)
		{
			auto funct = function;
			_keyCombs[SIZET(Action::Repeat)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(funct), std::forward<Args>(args)...)
			);
		}

		_keyCombs[SIZET(input.action)].emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
		);
	}

	template<class ...Args>
	inline void KeyControl::AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, std::function<bool(Args...)> func, Args && ...args)
	{
		Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);

		if (repeatAsWell)
		{
			auto function = func;
			_keyCombs[SIZET(Action::Repeat)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
			);
		}
		_keyCombs[SIZET(input.action)].emplace(
			std::pair(input.number, val),
			std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(func), std::forward<Args>(args)...)
		);

	}

}