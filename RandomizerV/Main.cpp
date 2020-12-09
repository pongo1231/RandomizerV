#include <stdafx.h>

namespace Main
{
	void RunHooks()
	{
		for (RegisteredHook* pRegisteredHook = g_pRegisteredHooks; pRegisteredHook != nullptr; pRegisteredHook = pRegisteredHook->GetNext())
		{
			pRegisteredHook->RunHook();
		}
	}

	void Run()
	{
		static bool alreadyHooked = false;

		if (!alreadyHooked)
		{
			alreadyHooked = true;

			Main::RunHooks();
		}

		while (true)
		{
			WAIT(0);

			for (RegisteredHook* pRegisteredHook = g_pRegisteredHooks; pRegisteredHook != nullptr; pRegisteredHook = pRegisteredHook->GetNext())
			{
				pRegisteredHook->RunLoop();
			}
		}
	}
}