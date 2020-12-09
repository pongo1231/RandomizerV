#pragma once

#include "Handle.h"

#include <string>

enum MH_STATUS : int;

namespace Memory
{
	void Init();
	void Uninit();

	Handle FindPattern(const std::string& pattern);
}