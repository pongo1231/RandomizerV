#include <stdafx.h>

static inline bool IsBlacklistedWeapon(Hash _weaponHash)
{
	return _weaponHash == 0xA2719263; // Unarmed
}

static inline Hash GetRandomWeapon()
{
	static const std::vector<Hash>& weaponHashes = Memory::Weapon::GetAllWeaponHashes();

	return weaponHashes[Random::GetRandomInt(0, weaponHashes.size() - 1)];
}

void(*GIVE_WEAPON_TO_PED_og)(int _pedHandle, Hash _weaponHash, int _ammoCount, bool _isHidden, bool _equipNow);
void GIVE_WEAPON_TO_PED_hook(int _pedHandle, Hash _weaponHash, int _ammoCount, bool _isHidden, bool _equipNow)
{
	if (!IsBlacklistedWeapon(_weaponHash))
	{
		_weaponHash = GetRandomWeapon();
	}

	GIVE_WEAPON_TO_PED_og(_pedHandle, _weaponHash, _ammoCount, _isHidden, _equipNow);
}

void(*sub_7FF79F446654_og)(__int64 _a1, Hash _weaponHash, int _a3, char _a4);
void sub_7FF79F446654_hook(__int64 _a1, Hash _weaponHash, int _a3, char _a4)
{
	if (!IsBlacklistedWeapon(_weaponHash))
	{
		_weaponHash = GetRandomWeapon();
	}

	sub_7FF79F446654_og(_a1, _weaponHash, _a3, _a4);
}

__int64(*sub_7FF79F2E4FF4_og)(__int64 _a1, Hash _weaponHash);
__int64 sub_7FF79F2E4FF4_hook(__int64 _a1, Hash _weaponHash)
{
	if (!IsBlacklistedWeapon(_weaponHash))
	{
		_weaponHash = GetRandomWeapon();
	}

	return sub_7FF79F2E4FF4_og(_a1, _weaponHash);
}

bool(*sub_7FF79F2B729C_og)(__int64 _a1, Hash _weaponHash, int _a3, char _a4, char _a5, unsigned int _a6);
bool sub_7FF79F2B729C_hook(__int64 _a1, Hash _weaponHash, int _a3, char _a4, char _a5, unsigned int _a6)
{
	if (!IsBlacklistedWeapon(_weaponHash))
	{
		_weaponHash = GetRandomWeapon();
	}

	return sub_7FF79F2B729C_og(_a1, _weaponHash, _a3, _a4, _a5, _a6);
}

static void OnHook()
{
	if (!g_optionsManager.ReadBool("weapons_EnableRandomizer", true))
	{
		return;
	}

	Handle handle;

	//

	handle = Memory::FindPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A E9 41 8B F0 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84 ? ? ? ? 8B 80 ? ? ? ? 8B C8");
	Memory::AddHook("GIVE_WEAPON_TO_PED", handle.Get<void>(), GIVE_WEAPON_TO_PED_hook, &GIVE_WEAPON_TO_PED_og);

	//

	if (g_optionsManager.ReadBool("weapons_EnableExtremeRandomizer", false))
	{
		handle = Memory::FindPattern("E8 ? ? ? ? EB 3F 48 8B 8B ? ? ? ? 48 85 C9 74 33 44 8B C6 8B D7 E8 ? ? ? ? 40 84 ED 74 24 48 8B 8B");
		Memory::AddHook("sub_7FF79F446654", handle.Into().Get<void>(), sub_7FF79F446654_hook, &sub_7FF79F446654_og);

		//

		handle = Memory::FindPattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B 41 10 48 8B F9 8B DA 48 8B 88 ? ? ? ? 48 83 C1 18 E8 ? ? ? ? 48 F7 D8 45 1B C0");
		Memory::AddHook("sub_7FF79F2E4FF4", handle.Get<void>(), sub_7FF79F2E4FF4_hook, &sub_7FF79F2E4FF4_og);

		//

		handle = Memory::FindPattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 55 41 56 48 83 EC 40 41 8A F9");
		Memory::AddHook("sub_7FF79F2B729C", handle.Get<void>(), sub_7FF79F2B729C_hook, &sub_7FF79F2B729C_og);
	}
}

static RegisterHook registerHook(OnHook);