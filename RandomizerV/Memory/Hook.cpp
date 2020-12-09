#include "stdafx.h"

#include "Hook.h"

namespace Memory
{
	MH_STATUS AddHook(const char* _pName, void* _pTarget, void* _pDetour, void* _ppOrig)
	{
		MH_STATUS result = MH_CreateHook(_pTarget, _pDetour, reinterpret_cast<void**>(_ppOrig));

		if (result != MH_OK)
		{
			LOG("Error while hooking " << _pName << " (" << result << ")");
		}
		else
		{
			MH_EnableHook(_pTarget);
		}

		return result;
	}
}