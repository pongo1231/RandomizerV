#include <stdafx.h>

static bool m_ignoreNextModelHook = false;

__int64(*sub_7FF69D359E24_og)(unsigned int _a1, DWORD* _a2);

/*inline void _REQUEST_MODEL(Hash _hash)
{
	static __int64(*sub_7FF69D358D50)(__int64 a1) = nullptr;
	static __int64(*sub_7FF69C74B3F8)(__int64 a1, unsigned int a2, int a3);
	static DWORD* dword_7FF69E3595B4;
	static __int64(*sub_7FF69C756D8C)();
	static __int64(*sub_7FF69D2C9F6C)(__int64 a1, __int16 a2, int a3, __int64 a4);
	static DWORD* qword_7FF69E2F1CA0;
	if (!sub_7FF69D358D50)
	{
		Handle handle = Memory::FindPattern("40 53 48 83 EC 20 8B 41 50 C1 E8 1F A8 01 0F 84 ? ? ? ? 8B 5C 24 30 81 CB ? ? ? ? 81 E3 ? ? ? ? E8");
		sub_7FF69D358D50 = handle.Get<__int64(__int64)>();

		handle = Memory::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8B EC 48 83 EC 30 83 61 0C 00 83 61 10 00 44 8B F2 B8");
		sub_7FF69C74B3F8 = handle.Get<__int64(__int64, unsigned int, int)>();

		handle = Memory::FindPattern("44 8B 05 ? ? ? ? 48 8D 4D D0 8B D3 E8 ? ? ? ? C6 45 18 00 E8 ? ? ? ? 4C 8B 08 4C 8D 45 18 48 8D 55 D0 48 8B C8 41 FF 51 60 80 7D 18 00 74 29");
		dword_7FF69E3595B4 = handle.At(2).Into().Get<DWORD>();

		handle = Memory::FindPattern("48 83 EC 28 E8 ? ? ? ? 33 C9 48 85 C0 74 0C E8 ? ? ? ? 48 8B 88");
		sub_7FF69C756D8C = handle.Get<__int64()>();

		handle = Memory::FindPattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 0F B7 79 58 33 C0 45 33 D2 41 8B E8 44 0F B7 F2 48 8B D9 4C 63 DF 85 FF 7E 18 48 8B 51 50");
		sub_7FF69D2C9F6C = handle.Get<__int64(__int64, __int16, int, __int64)>();

		handle = Memory::FindPattern("48 8D 0D ? ? ? ? BA ? ? ? ? 4C 8B C8 44 8B C3 E8 ? ? ? ? 48 85 C0 75 08 48 8B CF E8");
		qword_7FF69E2F1CA0 = handle.At(2).Into().Get<DWORD>();
	}

	struct
	{
		__int64 m_vptr;
		__int64 pad2[4];
	}
	v9;
	int v11 = 0xFFFF;
	int v10 = (v10 | 0xFFFFFFF) & 0xFFFFFFF;

	__int64 v3 = sub_7FF69D359E24_og(_hash, reinterpret_cast<DWORD*>(&v11));
	v10 = v11;
	if (v3)
	{
		m_ignoreNextModelHook = true;
		sub_7FF69C74B3F8(reinterpret_cast<__int64>(&v9), _hash, *dword_7FF69E3595B4);
		v10 = 0;
		__int64 v4 = sub_7FF69C756D8C();
		if (v4)
		{
			(*(void(__fastcall**)(__int64, char*, int*))(*(__int64*)v4 + 96))(v4, reinterpret_cast<char*>(&v9), &v10);
			if (v10)
			{
				__int64 v5 = sub_7FF69C756D8C();
				if (!sub_7FF69D2C9F6C((__int64)qword_7FF69E2F1CA0, 14, _hash, v5))
				{
					sub_7FF69D358D50(v3);
				}
			}
		}
		//dword_7FF69E3595B4 = 0;
	}
}*/

__int64(*REQUEST_MODEL_og)(Hash _model);

inline void _REQUEST_MODEL(Hash _hash)
{
	REQUEST_MODEL_og(_hash);
}

static inline bool IsModelAVehicle(Hash _model)
{
	static const std::vector<Hash>& vehicles = Memory::Vehicle::GetAllVehicleModels();

	return std::find(vehicles.begin(), vehicles.end(), _model) != vehicles.end();
}

static std::unordered_map<Hash, Hash> m_vehTable;

inline Hash GetReplacementVehicle(Hash _model)
{
	if (m_vehTable.empty())
	{
		static const std::vector<Hash>& vehicles = Memory::Vehicle::GetAllVehicleModels();

		std::vector<Hash> tempVehicles = vehicles;

		for (Hash model : vehicles)
		{
			int chosenIndex = Random::GetRandomInt(0, tempVehicles.size() - 1);

			m_vehTable.emplace(model, tempVehicles[chosenIndex]);

			tempVehicles.erase(tempVehicles.begin() + chosenIndex);
		}
	}

	std::unordered_map<Hash, Hash>::iterator result = m_vehTable.find(_model);

	return result != m_vehTable.end() ? result->second : _model;
}

__int64 REQUEST_MODEL_hook(Hash _model)
{
	/*DWORD dummy;
	__int64 result = sub_7FF69D359E24_og(_model, &dummy);
	if (result)
	{
		if ((*reinterpret_cast<BYTE*>(result + 157) & 0x1F) == 5 && IsModelAVehicle(_model)) // is vehicle model
		{
			_model = _GET_HASH_KEY("Trash");
		}
	}*/

	if (IsModelAVehicle(_model)) // is vehicle model
	{
		_model = GetReplacementVehicle(_model);
	}

	return REQUEST_MODEL_og(_model);
}

bool(*HAS_MODEL_LOADED_og)(Hash _model);
bool HAS_MODEL_LOADED_hook(Hash _model)
{
	/*DWORD dummy;
	__int64 result = sub_7FF69D359E24_og(_model, &dummy);
	if (result)
	{
		if ((*reinterpret_cast<BYTE*>(result + 157) & 0x1F) == 5 && IsModelAVehicle(_model)) // is vehicle model
		{
			_model = _GET_HASH_KEY("Trash");
		}
	}*/

	if (IsModelAVehicle(_model)) // is vehicle model
	{
		_model = GetReplacementVehicle(_model);
	}

	return HAS_MODEL_LOADED_og(_model);
}

// Function related to model hash to some struct convertion
__int64 sub_7FF69D359E24_hook(Hash _model, DWORD* _a2)
{
	/*if (m_ignoreNextModelHook)
	{
		m_ignoreNextModelHook = false;
	}
	else
	{
		__int64 result = sub_7FF69D359E24_og(_model, _a2);
		if (result)
		{
			if ((*reinterpret_cast<BYTE*>(result + 157) & 0x1F) == 5 && IsModelAVehicle(_model)) // is vehicle model
			{
				//	int v3 = *reinterpret_cast<DWORD*>(result + 832);
				//	if (!v3 || static_cast<unsigned int>(v3 - 5) <= 1)
				//	{
				_REQUEST_MODEL(_GET_HASH_KEY("Trash"));
				_model = _GET_HASH_KEY("Trash");
				//	}
			}
		}
	}*/

	if (IsModelAVehicle(_model)) // is vehicle model
	{
		_model = GetReplacementVehicle(_model);
	}

	return sub_7FF69D359E24_og(_model, _a2);
}

__int64(*CREATE_VEHICLE_og)(Hash _model, int* _a2, __int64 _a3, char _a4, char _a5, char _a6);
__int64 CREATE_VEHICLE_hook(Hash _model, int* _a2, __int64 _a3, char _a4, char _a5, char _a6)
{
	/*static const std::vector<Hash>& vehs = Memory::Vehicle::GetAllVehModels();

	Hash trash = vehs[Random::GetRandomInt(0, vehs.size() - 1)];

	REQUEST_MODEL(trash);

	DWORD64 timestamp = GetTickCount64();

	while (!HAS_MODEL_LOADED(trash) && timestamp > GetTickCount64() - 1000)
	{
		//DWORD64 tempTimestamp = GetTickCount64();

		invoke<Void>(0x4EDE34FBADD967A6, 100);

		/*if (tempTimestamp > GetTickCount64() - 50)
		{
			WAIT(100);
		}
	}*/

	return CREATE_VEHICLE_og(GetReplacementVehicle(_model), _a2, _a3, _a4, _a5, _a6);
}

__int64(*sub_7FF79F1AE8E0_og)(__int64 a1, __int64 a2, char a3);
__int64 sub_7FF79F1AE8E0_hook(__int64 a1, __int64 a2, char a3)
{
	/*for (DWORD64* entry = *reinterpret_cast<DWORD64**>(a2 + 8); entry; entry = reinterpret_cast<DWORD64*>(entry[1]))
	{
		LOG(*entry << " " << IS_MODEL_VALID(*entry));
	}*/

	return sub_7FF79F1AE8E0_og(a1, a2, a3);
}

static void OnHook()
{
	if (!g_optionsManager.ReadBool("vehicles_EnableModelRandomizer", true))
	{
		return;
	}

	Handle handle;

	// VEHICLE MODEL RANDOMIZER WORK

	handle = Memory::FindPattern("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 50 8B 45 18 48 8D 55 20 8B D9 0D ? ? ? ? C7 45 ? ? ? ? ? 25");

	Memory::AddHook("REQUEST_MODEL", handle.Get<void>(), REQUEST_MODEL_hook, &REQUEST_MODEL_og);

	//

	handle = Memory::FindPattern("48 89 7C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 18 BF ? ? ? ? 48 8D 55 20 0B C7 89 7D 20 0D ? ? ? ? 25 ? ? ? ? 89 45 18 E8 ? ? ? ? 0F B7 4D 20");

	Memory::AddHook("HAS_MODEL_LOADED", handle.Get<void>(), HAS_MODEL_LOADED_hook, &HAS_MODEL_LOADED_og);

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 0F B7 4D 38");

	Memory::AddHook("sub_7FF69D359E24", handle.Into().Get<void>(), sub_7FF69D359E24_hook, &sub_7FF69D359E24_og);*/

	//

	handle = Memory::FindPattern("8B D9 44 22 75 60 F3 0F 11 45 ? F3 0F 10 45 ? F3 0F 11 4D ? F3 0F 11 45 ? F3 0F 11 5D ? E8 ? ? ? ? 84 C0 75 07");

	Memory::AddHook("CREATE_VEHICLE", handle.At(-0x3A).Get<void>(), CREATE_VEHICLE_hook, &CREATE_VEHICLE_og);

	//

	/*handle = Memory::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 FF 05 ? ? ? ? 41 8A F0 48 8B DA 48 8B F9 E8");

	Memory::AddHook("sub_7FF79F1AE8E0", handle.Get<void>(), sub_7FF79F1AE8E0_hook, &sub_7FF79F1AE8E0_og);*/
}

static void OnTick()
{
	static bool alreadyCleared = false;

	if (IS_SCREEN_FADED_OUT())
	{
		if (!alreadyCleared)
		{
			alreadyCleared = true;

			m_vehTable.clear();
		}
	}
	else
	{
		alreadyCleared = false;
	}
}

static RegisterHook registerHook(OnHook, OnTick);