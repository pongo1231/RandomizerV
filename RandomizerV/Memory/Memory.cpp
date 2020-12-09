#include <stdafx.h>

#include "Memory.h"

namespace Memory
{
	DWORD64 m_baseAddr;
	DWORD64 m_endAddr;

	void Init()
	{
		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &moduleInfo, sizeof(moduleInfo));

		m_baseAddr = reinterpret_cast<DWORD64>(moduleInfo.lpBaseOfDll);
		m_endAddr = m_baseAddr + moduleInfo.SizeOfImage;

		MH_Initialize();
	}

	void Uninit()
	{
		MH_Uninitialize();
	}

	Handle FindPattern(const std::string& _pattern)
	{
		std::vector<int> bytes;

		std::string sub = _pattern;
		int offset = 0;
		while ((offset = sub.find(' ')) != sub.npos)
		{
			std::string byteStr = sub.substr(0, offset);

			if (byteStr == "?" || byteStr == "??")
			{
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(std::stoi(byteStr, nullptr, 16));
			}

			sub = sub.substr(offset + 1);
		}
		if ((offset = _pattern.rfind(' ')) != sub.npos)
		{
			std::string byteStr = _pattern.substr(offset + 1);
			bytes.push_back(std::stoi(byteStr, nullptr, 16));
		}

		if (bytes.empty())
		{
			LOG("Invalid Pattern");

			return Handle();
		}

		int count = 0;
		for (auto addr = m_baseAddr; addr < m_endAddr; addr++)
		{
			if (bytes[count] == -1 || *reinterpret_cast<BYTE*>(addr) == bytes[count])
			{
				if (++count == bytes.size())
				{
					return Handle(addr - count + 1);
				}
			}
			else
			{
				count = 0;
			}
		}

		LOG("Couldn't find pattern \"" << _pattern << "\"");

		return Handle();
	}
}