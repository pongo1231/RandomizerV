#include <stdafx.h>

__int64(*CRenderPhaseHud___Render_og)(__int64 _a1);
__int64 CRenderPhaseHud___Render_hook(__int64 _a1)
{
	return CRenderPhaseHud___Render_og(_a1);
}

DWORD*(*CRenderPhaseHud___Render__og)(__int64 _a1);
DWORD* CRenderPhaseHud___Render__hook(__int64 _a1)
{
	return CRenderPhaseHud___Render__og(_a1);
}

char(*CRenderPhaseHud__Render_Cursor_og)();
char CRenderPhaseHud__Render_Cursor_hook()
{
	return CRenderPhaseHud__Render_Cursor_og();
}

__int64(*_Load_Sprite_og)(const char* _a1);
__int64 _Load_Sprite_hook(const char* _a1)
{
	return _Load_Sprite_og(_a1);
}

__int64(*_Set_Color_String_Argb_og)(int _index, int _r, int _g, int _b, int _a);
__int64 _Set_Color_String_Argb_hook(int _index, int _r, int _g, int _b, int _a)
{
	LOG(_index << " " << _r << " " << _g << " " << _b << " " << _a);

	_r = Random::GetRandomInt(0, 255);
	_g = Random::GetRandomInt(0, 255);
	_b = Random::GetRandomInt(0, 255);

	return _Set_Color_String_Argb_og(_index, _r, _g, _b, _a);
}

#define COLOR_STRINGS_ENTRIES 224
static int* g_pColorStringsTable;

char(*sub_7FF69D4547FC_og)(DWORD64* _a1, __int64 _a2, const char* _a3, __int64 _a4, char _a5);
char sub_7FF69D4547FC_hook(DWORD64* _a1, __int64 _a2, const char* _a3, __int64 _a4, char _a5)
{
	char result = sub_7FF69D4547FC_og(_a1, _a2, _a3, _a4, _a5);

	if (!strcmp(_a3, "r") || !strcmp(_a3, "g") || !strcmp(_a3, "b"))
	{
		//LOG((int)result << " " << a1 << " " << a2 << " " << a3 << " " << a4 << " " << (int)a5);

		/*if (std::find(m_hudStructs.begin(), m_hudStructs.end(), a1) == m_hudStructs.end())
		{
			m_hudStructs.push_back(a1);
		}*/
	}

	return result;
}

void(*sub_7FF69BEA78A0_og)(__int64 _a1, __int64 _a2, const char* _a3, __int64 _a4, unsigned int _a5);
void sub_7FF69BEA78A0_hook(__int64 _a1, __int64 _a2, const char* _a3, __int64 _a4, unsigned int _a5)
{
	sub_7FF69BEA78A0_og(_a1, _a2, _a3, _a4, _a5);

	//LOG(a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5);
}

DWORD*(*sub_7FF69BED6F08_og)(DWORD* _a1, unsigned int _a2);
DWORD* sub_7FF69BED6F08_hook(DWORD* _a1, unsigned int _a2)
{
	LOG(_a1 << " " << _a2);

	*_a1 = g_pColorStringsTable[0];

	return _a1;
}

__int64(*sub_7FF69BF81D50_og)(float _a1, float _a2, float _a3);
__int64 sub_7FF69BF81D50_hook(float _a1, float _a2, float _a3)
{
	return sub_7FF69BF81D50_og(.1f, .2f, .3f);
}

__int64(*sub_7FF69D05017C_og)(DWORD64* _a1, int* _a2);
__int64 sub_7FF69D05017C_hook(DWORD64* _a1, int* _a2)
{
	return 0;
}

float* (*sub_7FF69BEA6954_og)(float* _a1, float* _a2, float* _a3, char _a4, char _a5);
float* sub_7FF69BEA6954_hook(float* _a1, float* _a2, float* _a3, char _a4, char _a5)
{
	float* result = sub_7FF69BEA6954_og(_a1, _a2, _a3, _a4, _a5);

	LOG(*result << " " << *_a1 << " " << *_a2 << " " << *_a3 << " " << _a4 << " " << _a5);

	return result;
}

static void OnHook()
{
	Handle handle;

	//

	/*handle = Memory::FindPattern("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 30 48 8B 81");
	Memory::AddHook(handle.Get<void>(), CRenderPhaseHud___Render_hook, &CRenderPhaseHud___Render);

	//

	handle = Memory::FindPattern("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 4C 8B F9 48 8B 0D ? ? ? ? BA");
	Memory::AddHook(handle.Get<void>(), CRenderPhaseHud___Render__hook, &CRenderPhaseHud___Render_);

	//

	handle = Memory::FindPattern("48 8B C4 48 89 58 10 48 89 78 18 55 48 8D 68 A1 48 81 EC ? ? ? ? 0F 29 70 E8 0F 29 78 D8 E8 ? ? ? ? 8B 1D ? ? ? ? 8B");
	Memory::AddHook(handle.Get<void>(), CRenderPhaseHud__Render_Cursor_hook, &CRenderPhaseHud__Render_Cursor);

	//

	handle = Memory::FindPattern("E8 ? ? ? ? 42 89 44 3B");
	Memory::AddHook(handle.Into().Get<void>(), _Load_Sprite_hook, &_Load_Sprite);

	//

	handle = Memory::FindPattern("48 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 89 45 D7 C6 45 1E 01 C7 45 ? ? ? ? ? 66 89 7D 27 E8");

	/*char* text = handle.At(2).Into().Get<char>();
	memset(text, 0, 15);
	strcpy_s(text, 15, "mouse_cursor");*/

	//

	// Randomize color strings table (on game launch)
	/*handle = Memory::FindPattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 44 8B 5C 24 ? 41 8B D9 BD ? ? ? ? 44 3B DD 48 63 F9 41 0F B6");
	Memory::AddHook(handle.Get<void>(), _Set_Color_String_Argb_hook, &_Set_Color_String_Argb);*/

	//

	// Randomize color strings table (rainboooooooow)
	handle = Memory::FindPattern("48 8D 0D ? ? ? ? 8B 0C 81 81 C9 ? ? ? ? 89 4D 58 48 8D 4D 48 E8 ? ? ? ? 48 8D 4D 48 E8");
	g_pColorStringsTable = handle.At(2).Into().Get<int>();

	//

	// Something
	/*handle = Memory::FindPattern("E8 ? ? ? ? 48 8D 5D C0 8B 43 F0");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69D4547FC_hook, &sub_7FF69D4547FC);*/

	//

	/*handle = Memory::FindPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 83 CE FF 45 33 E4");
	Memory::AddHook(handle.Get<void>(), sub_7FF69BEA78A0_hook, &sub_7FF69BEA78A0);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 84 DB 8B 08");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69BED6F08_hook, &sub_7FF69BED6F08);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 41 0F 28 FF");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69BF81D50_hook, &sub_7FF69BF81D50);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 4C 8D 0D ? ? ? ? 45 33 C0 49 8B C1");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69D05017C_hook, &sub_7FF69D05017C);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 4C 63 2F");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69CFD2568_hook, &sub_7FF69CFD2568);*/

	//

	/*handle = Memory::FindPattern("E8 ? ? ? ? 83 65 DF 00 F3 0F 10 45");
	Memory::AddHook(handle.Into().Get<void>(), sub_7FF69BEA6954_hook, &sub_7FF69BEA6954);*/
}

static void OnTick()
{
	static bool enabled = g_optionsManager.ReadBool("hud_EnableRandomizedColors", true);
	if (!enabled)
	{
		return;
	}

	static const int a = 255;

	DWORD64 curTime = GetTickCount64();
	int r = std::floor(std::sin(curTime * .001f) * 127 + 128);
	int g = std::floor(std::sin(curTime * .001f + 2) * 127 + 128);
	int b = std::floor(std::sin(curTime * .001f + 4) * 127 + 128);

	for (int i = 0; i < COLOR_STRINGS_ENTRIES; i++)
	{
		if (i == 2 || i == 4) // used by texts
		{
			continue;
		}

		int v12 = (r | (a << 8)) << 8;
		int v15 = (g | v12) << 8;
		int color = b | v15;

		g_pColorStringsTable[i] = color;
	}
}

static RegisterHook registerHook(OnHook, OnTick);