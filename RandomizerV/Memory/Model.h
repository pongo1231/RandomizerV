#pragma once

#include "Macros.h"
#include "Memory/Memory.h"

#include "../../vendor/minhook/include/MinHook.h"

#define LOWORD(x)   (*((WORD*)&(x)))

typedef unsigned long Hash;

namespace Memory::Model
{
	inline __int64 HashToModel(Hash hash)
	{
		static void(*_HashToSomething)(Hash hash, unsigned int* modelOut);

		static bool firstTime = true;
		if (firstTime)
		{
			firstTime = false;

			Handle handle = Memory::FindPattern("E8 ? ? ? ? 0F B7 4D 38");

			_HashToSomething = handle.Into().Get<void(Hash, unsigned int*)>();
		}

		unsigned int v27;
		_HashToSomething(hash, &v27);

		unsigned int v28 = v27;
		v28 = (v28 | 0xFFF0000) & 0xEFFFFFFF;
		LOWORD(v27) = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v28));
		v27 = ((v28 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x10000000 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x3FFFFFFF;
		LOWORD(v27) = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v28));
		v27 = ((v28 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x10000000 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x3FFFFFFF;
		LOWORD(v27) = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v28));
		v27 = ((v28 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x10000000 ^ ((v28 ^ v27) & 0xFFF0000 ^ v27) & 0xDFFFFFFF) & 0x3FFFFFFF;

		unsigned int a1 = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v28));
		unsigned int v61;
		v61 = (((unsigned __int16)(a1 ^ v61) ^ v61) & 0xCFFFFFFF | 0xFFF0000) & 0x3FFFFFFF;
		unsigned int v45;
		LOWORD(v45) = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v61));
		v45 = ((v61 ^ ((v61 ^ v45) & 0xFFF0000 ^ v45) & 0xDFFFFFFF) & 0x10000000 ^ ((v61 ^ v45) & 0xFFF0000 ^ v45) & 0xDFFFFFFF) & 0x3FFFFFFF;
		unsigned int v46;
		LOWORD(v46) = *reinterpret_cast<__int64*>(reinterpret_cast<WORD*>(&v61));
		v46 = ((v61 ^ ((v61 ^ v46) & 0xFFF0000 ^ v46) & 0xDFFFFFFF) & 0x10000000 ^ ((v61 ^ v46) & 0xFFF0000 ^ v46) & 0xDFFFFFFF) & 0x3FFFFFFF;

		return v46;
	}
}