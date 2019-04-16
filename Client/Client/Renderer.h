#pragma once
#include"Component.h"
class CGameObject;
class CRenderer:public CComponent
{
public:
	enum RENDERGROUP{RENDER_PRIORITY, RENDER_NONEALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END};
private:
	CRenderer(ID3D12Device* pGraphic_Device);
	virtual ~CRenderer()=default;
public:
	HRESULT		Ready_Renderer();
	HRESULT		Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject);
	HRESULT		Render_RenderGroup();
private:
	list<CGameObject*>		m_RenderList[RENDER_END];
	typedef list<CGameObject*>	OBJECTLIST;
private:
	void Render_Priority();
	void Render_NoneAlpha();
	void Render_Alpha();
	void Render_UI();
public:
	static CRenderer*		Create(ID3D12Device* pGraphic_Device);
	virtual CComponent*		Clone_Component();
	virtual void			Free();
};

