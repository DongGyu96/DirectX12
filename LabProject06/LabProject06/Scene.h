#pragma once
#include "Timer.h"
#include "Shader.h"

class CScene
{
public:
	CScene();
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList *pd3dCommandList);

	void ReleaseUploadBuffers();

	// �׷��� ��Ʈ �ñ׳�ó�� �����Ѵ�.
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSSignature();

protected:
	// ���� ���̴����� �����̴�. ���̴����� ���� ��ü���� �����̴�.
	CShader **m_ppShaders = NULL;
	int m_nShaders = 0;


	ID3D12RootSignature *m_pd3dGraphicRootSignature = NULL;
	// ��Ʈ �ñ״�ó�� ��Ÿ���� �������̽� �������̴�.
	// ID3D12PipelineState *m_pd3dPipelineState;
	// ���������� ���¸� ��Ÿ���� �������̽� �������̴�.
};

