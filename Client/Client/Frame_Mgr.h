#pragma once
#include "Base.h"
class CFrame;
class CFrame_Mgr:public CBase
{
	_DECLARE_SINGLETON(CFrame_Mgr)
private:
	CFrame_Mgr();
	virtual ~CFrame_Mgr() = default;
public:
	HRESULT Add_Frame(const _tchar* pFrameTag, const _float& fCallCnt);
	_bool	Permit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
private:
	map<const _tchar*, CFrame*>			m_mapFrame;
	typedef map<const _tchar*, CFrame*> MAPFRAME;
private:
	CFrame* Find_Frame(const _tchar* pFrameTag);
public:
	virtual void Free();
};

