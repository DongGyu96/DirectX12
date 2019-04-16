#pragma once
#include "Component.h"
class CShader:public CComponent
{
private:
	CShader(ID3D12Device* pGraphic_Device);
	CShader(const CShader& rhs);
	~CShader()=default;
public:
	HRESULT		Ready_Shader(const _tchar* pFilePath, const char* pVSEntryPoint, const char* pPSEntryPoint, _uint iFlag);
	HRESULT		Compile_Shader();
private:
	ID3DBlob*			m_pVertexShader = nullptr;
	ID3DBlob*			m_pPixelShader = nullptr;
	_uint				m_iCompileFlags = 0;
private:
	const _tchar*		m_pFilePath = nullptr;
	const char*			m_pVSEntryPoint = nullptr;
	const char*			m_pPSEntryPoint = nullptr;
public:
	ID3DBlob*			GetVertexShader() { return m_pVertexShader; }
	ID3DBlob*			GetPixelShader() { return m_pPixelShader; }
public:
	static CShader* Create(ID3D12Device* pGraphic_Device, const _tchar* pFilePath, const char* pVSEntryPoint, const char* pPSEntryPoint);
	virtual CComponent*	Clone_Component();
	virtual void Free();
};

