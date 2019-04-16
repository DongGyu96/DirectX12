#include "stdafx.h"
#include "Frame_Mgr.h"
#include "Frame.h"

_IMPLEMENT_SINGLETON(CFrame_Mgr)
CFrame_Mgr::CFrame_Mgr()
{
}

HRESULT CFrame_Mgr::Add_Frame(const _tchar * pFrameTag, const _float & fCallCnt)
{
	CFrame* pFrame = Find_Frame(pFrameTag);
	if (nullptr != pFrame)
		return E_FAIL;

	pFrame = CFrame::Create(fCallCnt);
	if (nullptr == pFrame)
		return E_FAIL;

	m_mapFrame.insert(MAPFRAME::value_type(pFrameTag, pFrame));
	return S_OK;
}

_bool CFrame_Mgr::Permit_Call(const _tchar * pFrameTag, const _float & fTimeDelta)
{
	CFrame* pFrame = Find_Frame(pFrameTag);
	if (nullptr == pFrame)
		return false;

	return pFrame->Permit_Call(fTimeDelta);
}

CFrame * CFrame_Mgr::Find_Frame(const _tchar * pFrameTag)
{
	auto iter = find_if(m_mapFrame.begin(), m_mapFrame.end(), CFinder_Tag(pFrameTag));

	if (iter == m_mapFrame.end())
		return nullptr;

	return iter->second;
}

void CFrame_Mgr::Free()
{
	for (auto& Pair : m_mapFrame)
	{
		Safe_Release(Pair.second);
	}
	m_mapFrame.clear();
}
