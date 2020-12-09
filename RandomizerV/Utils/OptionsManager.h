#pragma once

#include "OptionsFile.h"

#include <unordered_map>
#include <string>

class OptionsManager
{
public:
	inline int ReadInt(const std::string& _key, int _defaultValue)
	{
		const auto& found = m_cachedOptions.find(_key);
		if (found != m_cachedOptions.end())
		{
			return found->second;
		}

		int value = m_optionsFile.ReadValueInt(_key, _defaultValue);

		LOG(_key << " = " << value);

		m_cachedOptions[_key] = value;

		return value;
	}

	inline bool ReadBool(const std::string& _key, bool _defaultValue)
	{
		return ReadInt(_key, _defaultValue);
	}

private:
	OptionsFile m_optionsFile = OptionsFile("randomizer.ini");
	std::unordered_map<std::string, int> m_cachedOptions;
};

inline OptionsManager g_optionsManager;