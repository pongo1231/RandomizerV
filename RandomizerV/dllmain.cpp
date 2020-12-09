#include <stdafx.h>

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		Memory::Init();

		scriptRegister(hInstance, Main::Run);

		break;
	case DLL_PROCESS_DETACH:
		Memory::Uninit();
		scriptUnregister(hInstance);

		break;
	}

	return TRUE;
}