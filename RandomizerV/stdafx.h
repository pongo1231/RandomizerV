#pragma once

#include "Macros.h"

#include "Memory/Handle.h"
#include "Memory/Memory.h"
#include "Memory/Hook.h"
#include "Memory/VehicleHelpers.h"
#include "Memory/WeaponHelpers.h"
#include "Memory/Model.h"

#include "Main.h"

#include "Utils/Random.h"
#include "Utils/TryParse.h"
#include "Utils/OptionsManager.h"
#include "Utils/Hash.h"

#include "../vendor/scripthookv/inc/main.h"
#include "../vendor/scripthookv/inc/natives.h"
#include "NativesNoNamespaces.h"

#include "../vendor/minhook/include/MinHook.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <WinUser.h>
#include <Psapi.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>