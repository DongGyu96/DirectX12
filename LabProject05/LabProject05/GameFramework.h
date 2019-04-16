#pragma once
#include "Timer.h"
#include "Scene.h"

class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	CGameTimer m_GameTimer;		// ���� �����ӿ�ũ���� ����� Ÿ�̸�
	_TCHAR m_pszFrameRate[50];	// ������ ����Ʈ�� �� �������� ĸ�ǿ� ����ϱ� ���� ���ڿ�

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4 *m_pdxgiFactory;
	//DXGI ���丮 �������̽��� ���� ������
	IDXGISwapChain3 *m_pdxgiSwapChain;
	//���� ü�� �������̽��� ���� �������̴�. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ��ϴ�
	ID3D12Device *m_pd3dDevice;
	//Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�

	bool m_bMsaa4xEndable = false;
	UINT m_nMsaa4xQualityLevels = 0;
	// MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�.

	static const UINT m_nSwapChainBuffers = 2;
	// ���� ü���� �ĸ� ������ �����̴�.
	UINT m_nSwapChainBufferIndex;
	// ���� ���� ü���� �ĸ� ���� �ε����̴�.

	ID3D12Resource *m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap *m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;
	// ���� Ÿ�� ����, ������ �� �������̽� ������, ���� Ÿ�� ������ ������ ũ���̴�.

	ID3D12Resource *m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap *m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;
	// ����-���ٽ� ����, ������ �� �������̽� ������, ����-���ٽ� ������ ������ ũ���̴�.

	ID3D12CommandQueue *m_pd3dCommandQueue;
	ID3D12CommandAllocator *m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList *m_pd3dCommandList;
	// ��� ť, ��� �Ҵ���, ��� ����Ʈ �������̽� �������̴�.

	ID3D12PipelineState *m_pd3dPipelineState;
	// �׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� �������̴�.

	ID3D12Fence *m_pd3dFence;
	// �ĸ���۸��� ������ �潺 ���� �����ϱ� ���ؼ� ����
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;
	// �潺 �������̽� ������, �潺�� ��, �̺�Ʈ �ڵ��̴�

	// ���� ���� �������
	CScene *m_pScene;

#if defined(_DEBUG)
	ID3D12Debug *m_pd3dDebugController;
#endif
	D3D12_VIEWPORT m_d3dViewport;
	D3D12_RECT m_d3dScissorRect;
	// ����Ʈ�� ���� �簢���̴�

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	// �����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ��̴�(��: �����찡 �����Ǹ� ȣ��ȴ�)
	void OnDestroy();

	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	// ����ü��, ����̽�, ������ ��, ��� ť/�Ҵ���/����Ʈ�� �����ϴ� �Լ��̴�.

	void BuildObjects();
	void ReleaseObjects();
	// �������� �޽��� ���� ��ü�� �����ϰ� �Ҹ��ϴ� �Լ��̴�.

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();
	// �����ӿ�ũ�� �ٽ�(����� �Է�, �ִϸ��̼�, ������)�� �����ϴ� �Լ��̴�.

	void WaitForGpuComplete();
	//CPU�� GPU�� ����ȭ�ϴ� �Լ��̴�.

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void OnResizeBackBuffers();
	void MoveToNextFrame();
};

