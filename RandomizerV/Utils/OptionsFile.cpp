#include "stdafx.h"

#include "OptionsFile.h"

OptionsFile::OptionsFile(const std::string& _fileName) : m_fileName(_fileName)
{
	struct stat temp;
	if (stat(m_fileName.c_str(), &temp) == -1)
	{
		return;
	}

	std::ifstream file(m_fileName);
	if (file.fail())
	{
		return;
	}

	char buffer[256];
	while (file.getline(buffer, 256))
	{
		std::string line(buffer);

		if (line.empty() || line[0] == ';' /* Comment */)
		{
			continue;
		}

		std::string key = line.substr(0, line.find("="));

		// Ignore line if there's no "="
		if (line == key)
		{
			continue;
		}

		std::string value = line.substr(line.find("=") + 1).substr(0, line.find('\n')); // Also do trimming of newline
		
		m_options[key] = value;
	}

	LOG("Loaded config file " << _fileName << " successfully");
}

std::string OptionsFile::ReadValue(const std::string& _key, const std::string& _defaultValue) const
{
	const auto& result = m_options.find(_key);
	if (result != m_options.end())
	{
		return result->second;
	}
	else
	{
		return !_defaultValue.empty() ? _defaultValue : "";
	}
}

int OptionsFile::ReadValueInt(const std::string& _key, int _defaultValue) const
{
	const std::string& value = ReadValue(_key);
	
	if (!value.empty())
	{
		int result;
		if (TryParseInt(value, result))
		{
			return result;
		}
	}

	return _defaultValue;
}