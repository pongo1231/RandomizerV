#pragma once

#include <unordered_map>
#include <string>

class OptionsFile
{
public:
	OptionsFile(const std::string& _fileName);

	std::string ReadValue(const std::string& _key, const std::string& _defaultValue = "") const;
	int ReadValueInt(const std::string& _key, int _defaultValue) const;

private:
	const std::string m_fileName;
	std::unordered_map<std::string, std::string> m_options;
};