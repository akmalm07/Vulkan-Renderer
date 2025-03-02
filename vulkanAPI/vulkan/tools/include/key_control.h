#pragma once


#include "config.h"

#include "tools\include\keys.h"

#include "tools\include\window_input.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <array>

namespace tools
{
	class KeyControl
	{
	public:

		KeyControl();

		std::vector<std::shared_ptr<KeyCombB>> FindKeyCombList(Keys key, std::optional<Mods> mod = std::nullopt);

		std::vector<std::shared_ptr<KeyCombB>> FindKeyCombPolyList(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt);


		size_t NumOfKeysInList(Keys key, std::optional<Mods> mod = std::nullopt);

		size_t NumOfKeysInListPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt);


		std::shared_ptr<KeyCombB> FindKeyComb(Keys key, std::optional<Mods> mod = std::nullopt);

		std::shared_ptr<KeyCombB> FindKeyCombPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt);


		void AddFuncParamUpdaterKeys(Keys key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func);

		void AddFuncParamUpdaterKeysPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func);


		void ChangeFuncParamUpdaterKeys(Keys key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func);

		void ChangeFuncParamUpdaterKeysPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func);


		void DelKeyComb(Keys key, std::optional<Mods> mod = std::nullopt);

		void DelKeyCombPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt);


		template<class F, class ... Args>
		void AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, F&& function, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, bool(T::* func)(Args...), std::tuple<Args...>&& args);

		template<class ... Args>
		void AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, std::function<bool(Args...)> func, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(bool repeatAsWell, const KeyCombInputOne& input, bool(T::* func)(Args...), Args&&... args);



		template<class F, class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, F&& function, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), std::tuple<Args...>&& args);

		template<class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, std::function<bool(Args...)> func, Args&&... args);

	protected:

		std::array<std::unordered_map <std::pair<Keys, Mods>, KeyComplete>, SIZET(Action::Count)> _keyCombs;

		std::unordered_map <std::pair<std::array<Keys, KEY_MAX>, Mods>, KeyComplete> _keyCombsPoly;
	};

}

#include "key_control.inl"

