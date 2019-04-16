#pragma once

#include "Base.h"
#include "MainApp.h"

class CDevice :public CBase
{
	_DECLARE_SINGLETON(CDevice)
private:
	CDevice();
	virtual ~CDevice() = default;
public:
	HRESULT Initialize();
private:
	HINSTANCE m_hInstance;
	int m_nWndClientWidth;
	int m_nWndClientHeight;
	IDXGIFactory4 *m_pdxgiFactory;
	IDXGISwapChain3 *m_pdxgiSwapChain;
	ID3D12Device *m_pd3dDevice;
	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;
	static const UINT m_nSwapChainBuffers = 2;

	UINT m_nSwapChainBufferIndex;
	ID3D12Resource *m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap *m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;
	ID3D12Resource *m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap *m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;
	ID3D12CommandQueue *m_pd3dCommandQueue;
	ID3D12CommandAllocator *m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList *m_pd3dCommandList;
	ID3D12PipelineState *m_pd3dPipelineState;
	ID3D12Fence *m_pd3dFence;
	HANDLE m_hFenceEvent;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
#if defined(_DEBUG)
	ID3D12Debug *m_pd3dDebugController;
#endif
	D3D12_VIEWPORT m_d3dViewport;
	D3D12_RECT m_d3dScissorRect;
public:
	D3D12_VIEWPORT		GetViewPort() { return m_d3dViewport; }
public:
	bool OnCreate(HINSTANCE hInstance);
	void OnDestroy();
	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void BuildObjects();
	void ReleaseObjects();
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance(CMainApp* pMainApp, _float& fTimeDelta);
	void WaitForGpuComplete();
	void MoveToNextFrame();
	//CPU와 GPU를 동기화하는 함수이다.
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
private:
	_matrix			m_matProj;
	_matrix			m_matView;
public:
	_matrix			GetProjectionMatrix() { return m_matProj; }
	_matrix			GetViewMatrix() { return m_matView; }
public:
	void			SetProjectionMatrix(_matrix matProj) { m_matProj = matProj; }
	void			SetViewMatrix(_matrix matView) { m_matView = matView; }
public:
	ID3D12Device*				GetDevice() { return m_pd3dDevice; }
	ID3D12GraphicsCommandList*	GetList() { return m_pd3dCommandList; }
	ID3D12CommandQueue*			GetQueue() { return m_pd3dCommandQueue; }
	ID3D12CommandAllocator*		GetAllocator() { return m_pd3dCommandAllocator; }
public:
	void Begin();
	void End();

public:
	virtual void Free();


}; 