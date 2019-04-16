#include "stdafx.h"
#include "Shader.h"

CShader::CShader(ID3D12Device * pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CShader::CShader(const CShader & rhs)
	: CComponent(rhs)
	, m_pPixelShader(rhs.m_pPixelShader)
	, m_pVertexShader(rhs.m_pVertexShader)
	, m_iCompileFlags(rhs.m_iCompileFlags)
	, m_pFilePath(rhs.m_pFilePath)
	, m_pVSEntryPoint(rhs.m_pVSEntryPoint)
	, m_pPSEntryPoint(rhs.m_pPSEntryPoint)
{
}

HRESULT CShader::Ready_Shader(const _tchar* pFilePath, const char* pVSEntryPoint, const char* pPSEntryPoint, _uint iFlag)
{
	m_pFilePath = pFilePath;
	m_pVSEntryPoint = pVSEntryPoint;
	m_pPSEntryPoint = pPSEntryPoint;
	m_iCompileFlags = iFlag;

	return S_OK;
}

HRESULT CShader::Compile_Shader()
{
	ID3DBlob*	ErrMsg = nullptr;
	if (FAILED(D3DCompileFromFile(m_pFilePath, nullptr, nullptr, m_pVSEntryPoint, "vs_5_1", m_iCompileFlags, 0, &m_pVertexShader, &ErrMsg)))
		return E_FAIL;
	if (FAILED(D3DCompileFromFile(m_pFilePath, nullptr, nullptr, m_pPSEntryPoint, "ps_5_1", m_iCompileFlags, 0, &m_pPixelShader, &ErrMsg)))
		return E_FAIL;

	return S_OK;
}

CShader * CShader::Create(ID3D12Device * pGraphic_Device, const _tchar * pFilePath, const char* pVSEntryPoint, const char* pPSEntryPoint)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	CShader* pInstance = new CShader(pGraphic_Device);
	if (FAILED(pInstance->Ready_Shader(pFilePath, pVSEntryPoint, pPSEntryPoint, nCompileFlags)))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CShader::Clone_Component()
{
	return new CShader(*this);
}

void CShader::Free()
{
	CComponent::Free();
}
