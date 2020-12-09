#include <stdafx.h>

static inline bool AreRandomColorsEnabled()
{
	static bool enabled = g_optionsManager.ReadBool("vehicles_EnableColorRandomizer", true);

	return enabled;
}

static inline bool AreRandomUpgradesEnabled()
{
	static bool enabled = g_optionsManager.ReadBool("vehicles_EnableUpgradeRandomizer", true);

	return enabled;
}

__int64(*CVehicleFactory___CreateVehicle_og)(__int64 _a1, int* _a2, unsigned int _a3, unsigned int _a4, int* _a5, char _a6, char _a7);
__int64 CVehicleFactory___CreateVehicle_hook(__int64 _a1, int* _a2, unsigned int _a3, unsigned int _a4, int* _a5, char _a6, char _a7)
{
	__int64 result = CVehicleFactory___CreateVehicle_og(_a1, _a2, _a3, _a4, _a5, _a6, _a7);

	int handle = Memory::Vehicle::VehicleToHandle(result);

	if (AreRandomColorsEnabled())
	{
		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(handle, Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255));
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(handle, Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255));
	}

	if (AreRandomUpgradesEnabled())
	{
		SET_VEHICLE_MOD_KIT(handle, 0);

		SET_VEHICLE_WHEEL_TYPE(handle, Random::GetRandomInt(0, 7));

		for (int i = 0; i < 50; i++)
		{
			int max = GET_NUM_VEHICLE_MODS(handle, i);
			if (max > 0)
			{
				SET_VEHICLE_MOD(handle, i, Random::GetRandomInt(0, max - 1), Random::GetRandomInt(0, 1));
			}

			TOGGLE_VEHICLE_MOD(handle, i, Random::GetRandomInt(0, 1));
		}

		SET_VEHICLE_TYRES_CAN_BURST(handle, Random::GetRandomInt(0, 1));
		SET_VEHICLE_WINDOW_TINT(handle, Random::GetRandomInt(0, 6));

		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(handle, Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255));
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(handle, Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255));

		_SET_VEHICLE_NEON_LIGHTS_COLOUR(handle, Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255), Random::GetRandomInt(0, 255));
		for (int i = 0; i < 4; i++)
		{
			_SET_VEHICLE_NEON_LIGHT_ENABLED(handle, i, true);
		}

		_SET_VEHICLE_XENON_LIGHTS_COLOR(handle, Random::GetRandomInt(0, 12));
	}

	return result;
}

static void OnHook()
{
	if (!AreRandomColorsEnabled() && !AreRandomUpgradesEnabled())
	{
		return;
	}

	Handle handle;

	//

	handle = Memory::FindPattern("48 8B C4 48 89 58 08 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D 68 B9");

	Memory::AddHook("CVehicleFactory::_CreateVehicle", handle.Get<void>(), CVehicleFactory___CreateVehicle_hook, &CVehicleFactory___CreateVehicle_og);
}

static RegisterHook registerHook(OnHook);