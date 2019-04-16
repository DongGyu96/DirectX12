#pragma once
#include "Base.h"
#include "Transform.h"
#include "Renderer.h"
#include "Shader.h"
#include "Buffer_TriCol.h"
#include "Buffer_Cube.h"
#include "Buffer_Terrain.h"
#include "Combine.h"
class CComponent;
class CComponent_Mgr:public CBase
{
	_DECLARE_SINGLETON(CComponent_Mgr)
private:
	CComponent_Mgr();
	virtual ~CComponent_Mgr()=default;
public:
	HRESULT Reserve_Component_Manager(const _uint& iNumScene);
	HRESULT Add_Prototype_Component(const _uint& iNumScene, const _tchar* pComponentTag, CComponent* pComponent);
	CComponent*	Clone_Component(const _uint& iSceneID, const _tchar* pComponentTag);
private:
	map<const _tchar*, CComponent*>*			m_pMapPrototype = nullptr;
	typedef map<const _tchar*, CComponent*>		MAPPROTOTYPE;
private:
	_uint		m_iNumScene = 0;
private:
	CComponent*		Find_Component(const _uint& iSceneID, const _tchar* pComponentTag);
	virtual void	Free();
};

