#pragma once
#include "Timer.h"
#include "Scene.h"

class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	CGameTimer m_GameTimer;		// 게임 프레임워크에서 사용할 타이머
	_TCHAR m_pszFrameRate[50];	// 프레임 레이트를 주 윈도우의 캡션에 출력하기 위한 문자열

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4 *m_pdxgiFactory;
	//DXGI 팩토리 인터페이스에 대한 포인터
	IDXGISwapChain3 *m_pdxgiSwapChain;
	//스왑 체인 인터페이스에 대한 포인터이다. 주로 디스플레이를 제어하기 위하여 필요하다
	ID3D12Device *m_pd3dDevice;
	//Direct3D 디바이스 인터페이스에 대한 포인터이다. 주로 리소스를 생성하기 위하여 필요하다

	bool m_bMsaa4xEndable = false;
	UINT m_nMsaa4xQualityLevels = 0;
	// MSAA 다중 샘플링을 활성화하고 다중 샘플링 레벨을 설정한다.

	static const UINT m_nSwapChainBuffers = 2;
	// 스왑 체인의 후면 버퍼의 개수이다.
	UINT m_nSwapChainBufferIndex;
	// 현재 스왑 체인의 후면 버퍼 인덱스이다.

	ID3D12Resource *m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap *m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;
	// 렌더 타겟 버퍼, 서술자 힙 인터페이스 포인터, 렌더 타겟 서술자 원소의 크기이다.

	ID3D12Resource *m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap *m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;
	// 깊이-스텐실 버퍼, 서술자 힙 인터페이스 포인터, 깊이-스텐실 서술자 원소의 크기이다.

	ID3D12CommandQueue *m_pd3dCommandQueue;
	ID3D12CommandAllocator *m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList *m_pd3dCommandList;
	// 명령 큐, 명령 할당자, 명령 리스트 인터페이스 포인터이다.

	ID3D12PipelineState *m_pd3dPipelineState;
	// 그래픽스 파이프라인 상태 객체에 대한 인터페이스 포인터이다.

	ID3D12Fence *m_pd3dFence;
	// 후면버퍼마다 현재의 펜스 값을 관리하기 위해서 수정
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;
	// 펜스 인터페이스 포인터, 펜스의 값, 이벤트 핸들이다

	// 씬을 위한 멤버변수
	CScene *m_pScene;

#if defined(_DEBUG)
	ID3D12Debug *m_pd3dDebugController;
#endif
	D3D12_VIEWPORT m_d3dViewport;
	D3D12_RECT m_d3dScissorRect;
	// 뷰포트와 씨저 사각형이다

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	// 프레임워크를 초기화하는 함수이다(주: 윈도우가 생성되면 호출된다)
	void OnDestroy();

	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	// 스왑체인, 디바이스, 서술자 힙, 명령 큐/할당자/리스트를 생성하는 함수이다.

	void BuildObjects();
	void ReleaseObjects();
	// 렌더링할 메쉬와 게임 객체를 생성하고 소멸하는 함수이다.

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();
	// 프레임워크의 핵심(사용자 입력, 애니메이션, 렌더링)을 구현하는 함수이다.

	void WaitForGpuComplete();
	//CPU와 GPU를 동기화하는 함수이다.

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void OnResizeBackBuffers();
	void MoveToNextFrame();
};

