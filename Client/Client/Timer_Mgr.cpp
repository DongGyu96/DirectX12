#include "stdafx.h"
#include "Timer_Mgr.h"
#include "Timer.h"

_IMPLEMENT_SINGLETON(CTimer_Mgr)
CTimer_Mgr::CTimer_Mgr()
{
}

HRESULT CTimer_Mgr::Add_Timer(const _tchar * pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (nullptr != pTimer)
		return E_FAIL;

	pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_mapTimers.insert(MAPTIMERS::value_type(pTimerTag, pTimer));

	return S_OK;
}

_float CTimer_Mgr::Get_TimerDelta(const _tchar * pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

CTimer * CTimer_Mgr::Find_Timer(const _tchar * pTimerTag)
{
	auto iter = find_if(m_mapTimers.begin(), m_mapTimers.end(), CFinder_Tag(pTimerTag));

	if (iter == m_mapTimers.end())
		return nullptr;

	return iter->second;
}

void CTimer_Mgr::Free()
{
	for (auto& Pair : m_mapTimers)
	{
		Safe_Release(Pair.second);
	}
	m_mapTimers.clear();
}
