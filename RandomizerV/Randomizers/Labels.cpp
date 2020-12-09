#include <stdafx.h>

static std::unordered_map<Hash, Hash> m_labelsMap;

static __int64 m_labelPool = 0;

static inline Hash GetReplacementLabelHash(Hash _labelHash)
{
	if (m_labelsMap.empty())
	{
		return _labelHash;
	}

	const auto& result = m_labelsMap.find(_labelHash);
	if (result != m_labelsMap.end())
	{
		return result->second;
	}

	return _labelHash;
}

static inline const char* GetLabelText(Hash _labelHash)
{
	if (!m_labelPool)
	{
		return "NULL";
	}

	static const char*(*sub_7FF79F04C244)(__int64 _a1, Hash _labelHash) = nullptr;

	if (!sub_7FF79F04C244)
	{
		Handle handle = Memory::FindPattern("48 83 EC 28 E8 ? ? ? ? 48 85 C0 75 34 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9 80 E1 01 0F B6 C1 48 8D 0D");
		if (!handle.IsValid())
		{
			return "NULL";
		}

		sub_7FF79F04C244 = handle.Get<const char*(__int64, Hash)>();
	}

	return sub_7FF79F04C244(m_labelPool, _labelHash);
}

const char* (*_GET_LABEL_TEXT_og)(const char* _label);
const char* _GET_LABEL_TEXT_hook(const char* _label)
{
	return GetLabelText(GetReplacementLabelHash(GET_HASH_KEY(_label)));

	//return _GET_LABEL_TEXT_og(_label);
}

const char*(*sub_7FF79F04C28C_og)(__int64 _a1, const char* _label);
const char* __fastcall sub_7FF79F04C28C_hook(__int64 _a1, const char* _label)
{
	return GetLabelText(GetReplacementLabelHash(GET_HASH_KEY(_label)));

	//return sub_7FF79F04C28C_og(_a1, _label);
}

const char*(*sub_7FF79E422238_og)(const char* _label, DWORD64* _a2, __int64 _a3);
const char* sub_7FF79E422238_hook(const char* _label, DWORD64* _a2, __int64 _a3)
{
	return "NULL";
}

static void OnHook()
{
	if (!g_optionsManager.ReadBool("labels_EnableRandomizer", true))
	{
		return;
	}

	Handle handle;

	//

	handle = Memory::FindPattern("40 53 48 83 EC 20 48 8B D9 48 8B D1 48 8D 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 34 48 8D 0D ? ? ? ? 48 8B D3");
	Memory::AddHook("_GET_LABEL_TEXT", handle.Get<void>(), _GET_LABEL_TEXT_hook, &_GET_LABEL_TEXT_og);

	//

	m_labelPool = handle.At(0xC).At(2).Into().Addr();

	//

	handle = Memory::FindPattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8");
	Memory::AddHook("sub_7FF79F04C28C", handle.Get<void>(), sub_7FF79F04C28C_hook, &sub_7FF79F04C28C_og);

	//

	/*handle = Memory::FindPattern("4C 8B DA 48 8B C1 41 B9 ? ? ? ? EB 18 4D 8B 13 4D 85 D2 74 15 43 8A 14 0A 84 D2 74 0D 88 11 48 FF C1 49 FF C1");
	Memory::AddHook("sub_7FF79E422238", handle.Get<void>(), sub_7FF79E422238_hook, &sub_7FF79E422238_og);*/
}

static void OnTick()
{
	static int labelsCount = 0;

	static DWORD64 timestamp = GetTickCount64();
	DWORD64 curTimestamp = GetTickCount64();
	if (timestamp < curTimestamp - 1000)
	{
		timestamp = curTimestamp;

		Handle handle = m_labelPool;

		int thisLabelsCount = 0;

		for (int i = 0; i < 20; i++)
		{
			Handle poolHandle = handle.At(8 * i).Value<__int64>();
			unsigned int poolSize = poolHandle.At(4).Value<unsigned int>();

			thisLabelsCount += poolSize;
		}

		if (labelsCount != thisLabelsCount)
		{
			DEBUG_LOG("Reshuffling labels, previous count: " << labelsCount << ", new count: " << thisLabelsCount);

			labelsCount = thisLabelsCount;

			m_labelsMap.clear();

			std::vector<Hash> labelHashList;

			for (int i = 0; i < 20; i++)
			{
				Handle poolHandle = handle.At(8 * i).Value<__int64>();
				unsigned int poolSize = poolHandle.At(4).Value<unsigned int>();

				for (int j = 0; j < poolSize; j++)
				{
					labelHashList.push_back(poolHandle.At(8 * j).Value<Hash>());
				}
			}

			std::vector<Hash> temp = labelHashList;

			for (Hash labelHash : labelHashList)
			{
				int chosenIndex = Random::GetRandomInt(0, temp.size() - 1);

				m_labelsMap[labelHash] = temp[chosenIndex];

				temp.erase(temp.begin() + chosenIndex);
			}
		}
	}
}

static RegisterHook registerHook(OnHook, OnTick);