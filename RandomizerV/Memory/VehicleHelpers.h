#pragma once

#include "NativesNoNamespaces.h"

#include <vector>

typedef unsigned long long DWORD64;

namespace Memory::Vehicle
{
	inline int VehicleToHandle(__int64 vehicle)
	{
		static Handle handle = Memory::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB E8");
		static int(*GetVehicleHandle)(__int64) = handle.Get<int(__int64)>();

		return handle.IsValid() ? GetVehicleHandle(vehicle) : 0;
	}

	inline const std::vector<Hash>& GetAllVehicleModels()
	{
		static std::vector<Hash> vehModels;

		if (vehModels.empty())
		{
			Handle handle = FindPattern("48 8B 05 ?? ?? ?? ?? 48 8B 14 D0 EB 0D 44 3B 12");
			if (!handle.IsValid())
			{
				return vehModels;
			}

			handle = handle.At(2).Into();
			DWORD64 modelList = handle.Value<DWORD64>();

			handle = FindPattern("0F B7 05 ?? ?? ?? ?? 44 8B 49 18 45 33 D2 48 8B F1");
			if (!handle.IsValid())
			{
				return vehModels;
			}

			handle = handle.At(2).Into();
			WORD maxModels = handle.Value<WORD>();

			for (WORD i = 0; i < maxModels; i++)
			{
				DWORD64 entry = *reinterpret_cast<DWORD64*>(modelList + 8 * i);
				if (!entry)
				{
					continue;
				}

				Hash model = *reinterpret_cast<Hash*>(entry);

				if (IS_MODEL_VALID(model) && IS_MODEL_A_VEHICLE(model))
				{
					vehModels.push_back(model);
				}
			}
		}

		return vehModels;
	}
}