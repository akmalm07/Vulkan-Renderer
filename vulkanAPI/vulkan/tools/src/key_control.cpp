#include "pch.h"
#include "tools\include\key_control.h"

namespace tools
{


	KeyControl::KeyControl() = default;


	void KeyControl::DelKeyComb(Keys name, std::optional<Mods> mod = std::nullopt)
	{
		for (auto& item : _keyCombs)
		{
			auto it = item.find(std::make_pair(name, mod.value_or(Mods::None)));
			if (it == item.end())
			{
				throw std::runtime_error("Entered invalid window name ( Window.cpp : DelWindowButton )");
				return;
			}
			item.erase(it);
		}
	}

	void KeyControl::DelKeyCombPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt)
	{

		auto it = _keyCombsPoly.find(std::make_pair(key, mod.value_or(Mods::None)));
		if (it == _keyCombsPoly.end())
		{
			throw std::runtime_error("Entered invalid window name ( Window.cpp : DelWindowButton )");
			return;
		}
		_keyCombsPoly.erase(it);
	}


	std::vector<std::shared_ptr<KeyCombB>> KeyControl::FindKeyCombPolyList(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt)
	{
		std::vector<std::shared_ptr<KeyCombB>> thekeys;
		thekeys.reserve(2);

		for (auto& keys : _keyCombsPoly)
		{
			auto& [ky, val] = keys;

			if (ky.first == key && ky.second == mod.value_or(Mods::None))
			{
				thekeys.push_back(val.key);
			}

		}
		return thekeys;
	}


	std::vector<std::shared_ptr<KeyCombB>> KeyControl::FindKeyCombList(Keys key, std::optional<Mods> mod = std::nullopt)
	{
		std::vector<std::shared_ptr<KeyCombB>> thekeys;
		thekeys.reserve(2);

		for (auto& keys : _keyCombs)
		{
			for (auto& [ky, val] : keys)
			{
				if (ky.first == key && ky.second == mod.value_or(Mods::None))
				{
					thekeys.push_back(val.key);
				}
			}
		}
		return thekeys;
	}



	size_t KeyControl::NumOfKeysInList(Keys key, std::optional<Mods> mod = std::nullopt)
	{
		size_t value = 0;

		for (auto& keys : _keyCombs)
		{
			for (auto& [ky, val] : keys)
			{
				if (ky.first == key && ky.second == mod.value_or(Mods::None))
				{
					value++;
					if (value == 2)
					{
						return value;
					}
				}
			}
		}
		return value;
	}



	size_t KeyControl::NumOfKeysInListPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt)
	{
		size_t value = 0;
		for (auto& keys : _keyCombsPoly)
		{
			auto& [ky, val] = keys;
			if (ky.first == key && ky.second == mod.value_or(Mods::None))
			{
				value++;
			}
		}
		return value;
	}


	std::shared_ptr<KeyCombB> KeyControl::FindKeyComb(Keys key, std::optional<Mods> mod = std::nullopt)
	{
		for (auto& keys : _keyCombs)
		{
			for (auto& [ky, val] : keys)
			{
				if (ky.first == key && ky.second == mod.value_or(Mods::None))
				{
					return val.key;
				}
			}
		}
		return nullptr;

	}


	std::shared_ptr<KeyCombB> KeyControl::FindKeyCombPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt)
	{
		for (auto& keys : _keyCombsPoly)
		{
			auto& [ky, val] = keys;
			if (ky.first == key && ky.second == mod.value_or(Mods::None))
			{
				return val.key;
			}
		}
	}


	void KeyControl::AddFuncParamUpdaterKeys(Keys key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func)
	{
		if (NumOfKeysInList(key, mod.value_or(Mods::None)) == 1)
		{
			for (auto& keys : _keyCombs)
			{
				auto it = keys.find(std::make_pair(key, mod.value_or(Mods::None)));
				if (it != keys.end())
				{
					it->second.updater = std::move(func);
					break;
				}
			}
		}
		else if (NumOfKeysInList(key) < 1)
		{
			for (auto& keys : _keyCombs)
			{
				auto it = keys.find(std::make_pair(key, mod.value_or(Mods::None)));
				if (it != keys.end())
				{
					it->second.updater = std::move(func);
				}
			}
		}
		else
		{
			throw std::runtime_error("There are more than one key with the same name and mode in the list");
		}

	}


	void KeyControl::AddFuncParamUpdaterKeysPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func)
	{
		for (auto& keys : _keyCombsPoly)
		{
			auto& [ky, val] = keys;
			if (ky.first == key && ky.second == mod.value_or(Mods::None))
			{
				val.updater = std::move(func);
				break;
			}
		}

		throw std::runtime_error("There are more than one key with the same name and mode in the list");
	}


	void KeyControl::ChangeFuncParamUpdaterKeys(Keys key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func)
	{
		AddFuncParamUpdaterKeys(key, mod.value_or(Mods::None), std::move(func));
	}


	void KeyControl::ChangeFuncParamUpdaterKeysPoly(const std::array<Keys, KEY_MAX>& key, std::optional<Mods> mod = std::nullopt, std::function<bool()> func)
	{
		_keyCombsPoly[std::make_pair(key, mod.value_or(Mods::None))].updater = std::move(func);
	}


}
