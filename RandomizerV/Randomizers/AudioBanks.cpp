#include <stdafx.h>

char(*sub_7FF69C132FF4_og)(__int64 _a1, const char* _a2, char _a3, __int64 _a4, char _a5);
char sub_7FF69C132FF4_hook(__int64 _a1, const char* _a2, char _a3, __int64 _a4, char _a5)
{
	LOG("wut");

	return sub_7FF69C132FF4_og(_a1, "MICHAEL_EVENT_AMANDA_1", _a3, _a4, _a5);
}

__int64(*PLAY_SOUND_og)(__int64 _a1, int _a2, const char* _a3, const char* _a4, char _a5, int _a6, char _a7);
__int64 PLAY_SOUND_hook(__int64 _a1, int _a2, const char* _a3, const char* _a4, char _a5, int _a6, char _a7)
{
	LOG(_a1 << " " << _a2 << " " << std::string(_a3) << " " << std::string(_a4) << " " << (int)_a5 << " " << _a6 << " " << _a7);

	return PLAY_SOUND_og(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
}

__int64(*PLAY_SOUND_FRONTEND_og)(__int64 _a1, int _a2, const char* _a3, const char* _a4, char _a5);
__int64 PLAY_SOUND_FRONTEND_hook(__int64 _a1, int _a2, const char* _a3, const char* _a4, char _a5)
{
	LOG(_a1 << " " << _a2 << " " << std::string(_a3) << " " << std::string(_a4) << " " << (int)_a5);

	return PLAY_SOUND_FRONTEND_og(_a1, -1, "Camera_Shoot", "Phone_SoundSet_Franklin", 1);
}

void(*_PLAY_AMBIENT_SPEECH1_og)(__int64 _a1, const char* _a2, const char* _a3, char _a4);
void _PLAY_AMBIENT_SPEECH1_hook(__int64 _a1, const char* _a2, const char* _a3, char _a4)
{
	LOG(_a1 << " " << std::string(_a2) << " " << std::string(_a3) << " " << (int)_a4);

	//_PLAY_AMBIENT_SPEECH_WITH_VOICE(_a1, "bples_avaa", "ljt", "SPEECH_PARAMS_FORCE_NO_REPEAT_FRONTEND", 0);

	return _PLAY_AMBIENT_SPEECH1_og(_a1, _a2, "SPEECH_PARAMS_FORCE_MEGAPHONE", _a4);
}

void(*_PLAY_AMBIENT_SPEECH2_og)(__int64 _a1, const char* _a2, const char* _a3, char _a4);
void _PLAY_AMBIENT_SPEECH2_hook(__int64 _a1, const char* _a2, const char* _a3, char _a4)
{
	LOG(_a1 << " " << std::string(_a2) << " " << std::string(_a3) << " " << (int)_a4);

	//_PLAY_AMBIENT_SPEECH_WITH_VOICE(_a1, "bples_avaa", "ljt", "SPEECH_PARAMS_FORCE_NO_REPEAT_FRONTEND", 0);

	return _PLAY_AMBIENT_SPEECH2_og(_a1, _a2, "SPEECH_PARAMS_FORCE_MEGAPHONE", _a4);
}

__int64(*sub_7FF69C136F80_og)(__int64 _a1, unsigned int _a2, const char* _a3, unsigned int _a4, int _a5, __int64 _a6, int _a7, int _a8, float _a9, char _a10, __int64* _a11, DWORD* _a12);
__int64 sub_7FF69C136F80_hook(__int64 _a1, unsigned int _a2, const char* _a3, unsigned int _a4, int _a5, __int64 _a6, int _a7, int _a8, float _a9, char _a10, __int64* _a11, DWORD* _a12)
{
	static unsigned int(*sub_7FF69CFE60F0)(const char* _a1, unsigned int _a2) = nullptr;

	if (!sub_7FF69CFE60F0)
	{
		Handle handle;

		handle = Memory::FindPattern("E8 ? ? ? ? 8D 1C C0");
		if (!handle.IsValid())
		{
			LOG("Error while finding pattern");
		}

		sub_7FF69CFE60F0 = handle.Into().Get<unsigned int(const char*, unsigned int)>();
	}

	LOG(_a1 << " " << _a2 << " " << std::string(_a3) << " " << _a4 << " " << _a5 << " " << _a6 << " " << _a7 << " " << _a8 << " " << _a9 << " " << _a10 << " " << _a11 << " " << _a12);

	return sub_7FF69C136F80_og(_a1, /*sub_7FF69CFE60F0("CRASH_CAR_RANDOM", 0)*/ _a2, "SPEECH_PARAMS_FORCE_MEGAPHONE", _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12);
}

__int64(*sub_7FF69C1370E4_og)(__int64 _a1, unsigned int _a2, __int64 _a3, unsigned int _a4, int _a5, __int64 _a6, int _a7, int _a8, float _a9, __int64* _a10, DWORD* _a11);
__int64 sub_7FF69C1370E4_hook(__int64 _a1, unsigned int _a2, __int64 _a3, unsigned int _a4, int _a5, __int64 _a6, int _a7, int _a8, float _a9, __int64* _a10, DWORD* _a11)
{
	LOG(_a1 << " " << _a2 << " " << _a3 << " " << _a4 << " " << _a5 << " " << _a6 << " " << _a7 << " " << _a8 << " " << _a9 << " " << _a10 << " " << _a11);

	static unsigned int(*sub_7FF69CFE60F0)(const char* _a1, unsigned int _a2) = nullptr;
	static __int64(*sub_7FF69CFE6210)(const char* _a1, unsigned int _a2);
	static const char*(*sub_7FF69CF95504)(__int64 _a1, __int64 _a2, int _a3);
	static DWORD64* qword_7FF69DCFB170;
	static bool(*sub_7FF69C0C29AC)(__int64 _a1, __int64 _a2, __int64 _a3);

	if (!sub_7FF69CFE60F0)
	{
		Handle handle;

		handle = Memory::FindPattern("E8 ? ? ? ? 8D 1C C0");

		sub_7FF69CFE60F0 = handle.Into().Get<unsigned int(const char*, unsigned int)>();

		handle = Memory::FindPattern("E8 ? ? ? ? 39 47 04");

		sub_7FF69CFE6210 = handle.Into().Get<__int64(const char*, unsigned int)>();

		handle = Memory::FindPattern("E8 ? ? ? ? 44 8D 47 2F");

		sub_7FF69CF95504 = handle.Into().Get<const char*(__int64, __int64, int)>();

		handle = Memory::FindPattern("48 8D 0D ? ? ? ? 41 B8 ? ? ? ? 8B D0 E8 ? ? ? ? 33 C9 48 85 C0 0F 84 ? ? ? ? 48 89 4D C7 48 89 4D CF 89 4D DF 88 4D E5 48 8D 55 C7 4C 8B C0 48 8B CB 48 C7 45");

		qword_7FF69DCFB170 = handle.At(2).Into().Get<DWORD64>();

		handle = Memory::FindPattern("E8 ? ? ? ? 8A 45 DB");

		sub_7FF69C0C29AC = handle.Into().Get<bool(__int64, __int64, __int64)>();
	}

	unsigned int v15 = sub_7FF69CFE6210("SPEECH_PARAMS_FORCE_MEGAPHONE", 0);
	__int64 result = (__int64)sub_7FF69CF95504((__int64)qword_7FF69DCFB170, v15, 14);

	if (result)
	{
		__int64 v13 = _a1;
		__int64 v17 = 0;
		sub_7FF69C0C29AC(v13, (__int64)&v17, result);

		return sub_7FF69C1370E4_og(v13, _a2, (__int64)&v17, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11);
	}

	return 0;
}

static void OnHook()
{
	Handle handle;

	/*handle = Memory::FindPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 41 8B F9 41 8A F0 48 8B DA 48 8B E9 48 85 D2 0F 84");
	Memory::AddHook(handle.Get<void>(), sub_7FF69C132FF4_hook, &sub_7FF69C132FF4);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 90 EB 81 90 3D CC CC E9 52");
	Memory::AddHook(handle.Into().Get<void>(), PLAY_SOUND_hook, &PLAY_SOUND_og);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 90 EB 80 90 F3 CC");
	Memory::AddHook(handle.Into().Get<void>(), PLAY_SOUND_FRONTEND_hook, &PLAY_SOUND_FRONTEND_og);*/

	//

	handle = Memory::FindPattern("85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 70");
	Memory::AddHook("_PLAY_AMBIENT_SPEECH1", handle.Get<void>(), _PLAY_AMBIENT_SPEECH1_hook, &_PLAY_AMBIENT_SPEECH1_og);

	//

	handle = Memory::FindPattern("85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 60 41 8A F9");
	Memory::AddHook("_PLAY_AMBIENT_SPEECH2", handle.Get<void>(), _PLAY_AMBIENT_SPEECH2_hook, &_PLAY_AMBIENT_SPEECH2_og);

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 41 88 3E");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69C136F80_hook, &sub_7FF69C136F80);*/

	//

	handle = Memory::FindPattern("E8 ? ? ? ? EB 26 48 83 A3");
	Memory::AddHook("sub_7FF69C1370E4", handle.Into().Get<void>(), sub_7FF69C1370E4_hook, &sub_7FF69C1370E4_og);
}

//static RegisterHook registerHook(OnHook);