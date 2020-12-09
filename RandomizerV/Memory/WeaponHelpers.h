#pragma once

#include "Memory.h"
#include "../nativesNoNamespaces.h"

typedef unsigned long long DWORD64;
typedef unsigned long DWORD;
typedef unsigned short WORD;

#include <vector>

namespace Memory::Weapon
{
	inline std::vector<Hash>& GetAllWeaponHashes()
	{
		static std::vector<Hash> weapons;

		if (weapons.empty())
		{
			Handle handle;

			handle = Memory::FindPattern("0F B7 15 ?? ?? ?? ?? 45 33 D2 FF CA 78 29 4C 8B 1D ?? ?? ?? ?? 46 8D 04 12 41 D1 F8 4B 8B 0C C3 44 3B 49 10 74 13 73 06 41 8D 50 FF EB 04 45 8D 50 01 44 3B D2 7E DE 33 C9 48 85 C9 74 04 8B 41 1C");
			if (!handle.IsValid())
			{
				return weapons;
			}

			WORD* dword_7FF6D9EF9748 = handle.At(2).Into().Get<WORD>();

			handle = Memory::FindPattern("4C 8B 1D ?? ?? ?? ?? 46 8D 04 12 41 D1 F8 4B 8B 0C C3 44 3B 49 10 74 13 73 06 41 8D 50 FF EB 04 45 8D 50 01 44 3B D2 7E DE 33 C9 48 85 C9 74 04 8B 41 1C");
			if (!handle.IsValid())
			{
				return weapons;
			}

			DWORD64* qword_7FF6D9EF9740 = handle.At(2).Into().Get<DWORD64>();

			int v3;
			DWORD64 v4;
			DWORD64 v5;

			for (v3 = *dword_7FF6D9EF9748 - 1; v3 >= 0; v3 = v4 - 1)
			{
				v4 = static_cast<DWORD>(v3);

				v5 = *(reinterpret_cast<DWORD64*>(*qword_7FF6D9EF9740) + v4);

				Hash weapon = *reinterpret_cast<Hash*>(v5 + 16);

				// Filter out the weird invalid weapons
				if (GET_WEAPONTYPE_MODEL(weapon))
				{
					weapons.push_back(weapon);
				}
			}
		}

		return weapons;
	}
}