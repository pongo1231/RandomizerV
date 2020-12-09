#pragma once

#include <cstdlib>
#include <string>

inline bool TryParseInt(const std::string& text, int& result, int radix = 10)
{
	char* end;
	long parseResult = std::strtol(text.c_str(), &end, radix);

	bool parsed = *end == '\0';
	if (parsed)
	{
		result = parseResult;
	}

	return parsed;
}