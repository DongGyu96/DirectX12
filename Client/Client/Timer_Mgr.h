#pragma once
#include "Base.h"
class CTimer;
class CTimer_Mgr :public CBase
{
	_DECLARE_SINGLETON(CTimer_Mgr)
private:
	CTimer_Mgr();
	virtual ~CTimer_Mgr() = default;
public:
	HRESULT Add_Timer(const _tchar* pTimerTag);
	_float	Get_TimerDelta(const _tchar* pTimerTag);
private:
	map<const _tchar*, CTimer*>			m_mapTimers;
	typedef map<const _tchar*, CTimer*>	MAPTIMERS;
private:
	CTimer*		Find_Timer(const _tchar* pTimerTag);
public:
	virtual void Free();
};

