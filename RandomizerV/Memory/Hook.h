#pragma once

enum MH_STATUS : int;

namespace Memory
{
	MH_STATUS AddHook(const char* _pName, void* _pTarget, void* _pDetour, void* _ppOrig = nullptr);
}

class RegisteredHook;
inline RegisteredHook* g_pRegisteredHooks = nullptr;

class RegisteredHook
{
public:
	RegisteredHook(void(*_pHookFunc)(), void(*_pLoopFunc)()) : m_pHookFunc(_pHookFunc), m_pLoopFunc(_pLoopFunc)
	{
		if (g_pRegisteredHooks)
		{
			m_pNext = g_pRegisteredHooks;
		}

		g_pRegisteredHooks = this;
	}

	inline void RunHook() const
	{
		m_pHookFunc();
	}

	inline void RunLoop() const
	{
		if (m_pLoopFunc)
		{
			m_pLoopFunc();
		}
	}

	inline RegisteredHook* GetNext() const
	{
		return m_pNext;
	}

private:
	RegisteredHook* m_pNext = nullptr;
	void(*m_pHookFunc)();
	void(*m_pLoopFunc)();
};

class RegisterHook
{
public:
	RegisterHook(void(*_pHookFunc)(), void(*_pLoopFunc)() = nullptr) : m_registeredHook(_pHookFunc, _pLoopFunc)
	{

	}

private:
	const RegisteredHook m_registeredHook;
};