#include "stdafx.h"
#include "Input.h"


_IMPLEMENT_SINGLETON(CInput)
CInput::CInput()
{
}

HRESULT CInput::Ready_Input_Device(HINSTANCE hInstane, HWND hWnd)
{

	if (FAILED(DirectInput8Create(hInstane, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pSDK, nullptr)))
		return E_FAIL;

	if (FAILED(Ready_KeyBoard(hWnd)))
		return E_FAIL;

	if (FAILED(Ready_Mouse(hWnd)))
		return E_FAIL;

	return S_OK;
}

void CInput::SetUp_InputState()
{
	if (nullptr == m_pKeyBoard)
		return;
	if (nullptr == m_pMouse)
		return;

	m_pKeyBoard->GetDeviceState(256, m_KeyState);

	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);
}

HRESULT CInput::Ready_KeyBoard(HWND hWnd)
{
	if (FAILED(m_pSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// 키보드의 활동영역을 설정한다(협조레벨)
	if (FAILED(m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY)))
		return E_FAIL;

	// 장치의 타입을 셋팅한다.
	if (FAILED(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;

	// 키보드를 활성화한다.
	m_pKeyBoard->Acquire();

	return S_OK;
}

HRESULT CInput::Ready_Mouse(HWND hWnd)
{
	if (FAILED(m_pSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// 키보드의 활동영역을 설정한다(협조레벨)
	if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return E_FAIL;

	// 장치의 타입을 셋팅한다.
	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;

	// 키보드를 활성화한다.
	m_pMouse->Acquire();

	return NOERROR;
}

void CInput::Free()
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);

	Safe_Release(m_pSDK);
}
