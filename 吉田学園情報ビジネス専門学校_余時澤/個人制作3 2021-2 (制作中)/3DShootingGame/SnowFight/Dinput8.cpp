//=============================================================================
//
// [Input.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "Dinput8.h"

//get device
LPDIRECTINPUT8 g_pInputkeyboard = NULL;
LPDIRECTINPUTDEVICE8 g_pDevkeyborad = NULL;
LPDIRECTINPUT8 g_pInputMouse = NULL;
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;

BYTE g_aKeyState[256];//save the last frame
BYTE g_aKeyStateTrigger[256];//trigger処理
BYTE g_aKeyStateRelease[256];//release処理

DIMOUSESTATE g_CurrentMouseState;//マウスの現在の入力情報
DIMOUSESTATE g_PrevMouseState;//マウスの一フレーム前の入力情報
D3DXVECTOR2 g_MouseMove;//移動量

HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//create the directinput object 1 application handle 2 version 3 defalut value DIRECTINPUT_VERSION (define in dinput.h) 3 interface label default value IID_IDirectInput8 4 save the Directinput pointer after success create
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputkeyboard, NULL))) return E_FAIL;
	//create a keyboard object use got interface 1 GUID mouse has a different one 2 pointer of this device
	if (FAILED(g_pInputkeyboard->CreateDevice(GUID_SysKeyboard, &g_pDevkeyborad, NULL))) return E_FAIL;
	//set the data type of keyboard c_dfDIKeyboard 
	if (FAILED(g_pDevkeyborad->SetDataFormat(&c_dfDIKeyboard)))	return E_FAIL;
	//set the cooperativelevel
	/*
	DISCL_FOREGROUND
	have been chosen can get the message
	DISCL_BACKGROUND
	any time can get the message
	DISCL_EXCLUSIVE monopolize
	DISCL_NONEXCLUSIVE unmonopolize
	*/
	if (FAILED(g_pDevkeyborad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) return E_FAIL;
	//use acquire function to get the device
	if (FAILED(g_pDevkeyborad->Acquire())) return E_FAIL;
	if (FAILED(g_pDevkeyborad->Poll())) return E_FAIL;
	return S_OK;
}
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputMouse, NULL))) return E_FAIL;
	if (FAILED(g_pInputMouse->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL))) return E_FAIL;
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))	return E_FAIL;
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) return E_FAIL;
	if (FAILED(g_pDevMouse->Acquire())) return E_FAIL;
	if (FAILED(g_pDevMouse->Poll())) return E_FAIL;
	return S_OK;
}

//release the memory
void Uninitkeyboard(void)
{
	if (g_pDevkeyborad != NULL)
	{
		g_pDevkeyborad->Unacquire();
		g_pDevkeyborad->Release();
		g_pDevkeyborad = NULL;
	}
	if (g_pInputkeyboard != NULL)
	{
		g_pInputkeyboard->Release();
		g_pInputkeyboard = NULL;
	}
}
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{			
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	if (g_pInputMouse != NULL)
	{			
		g_pInputMouse->Release();
		g_pInputMouse = NULL;
	}
}

void Updatekeyboard(void)
{
	BYTE aKeyState[256];//currently frame

	//get the information which input by keyboard 1 the data save struct's size 2 save position
	if (SUCCEEDED(g_pDevkeyborad->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & (aKeyState[nKey] & 0x80);
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & (g_aKeyState[nKey] & 0x80);
			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else g_pDevkeyborad->Acquire();
}

void UpdateMouse(void)
{
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(g_CurrentMouseState), &g_CurrentMouseState)))
	{
		g_MouseMove.x = (float)g_CurrentMouseState.lX;
		g_MouseMove.y = (float)g_CurrentMouseState.lY;
		g_PrevMouseState = g_CurrentMouseState;
	}
	else g_pDevMouse->Acquire();
}

bool GetMouseTrigger(void)
{
	return false;
}

bool GetMouseRelease(void)
{
	return false;
}

bool GetkeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;
}
bool GetkeyboardTrigger(int nkey)
{
	return (g_aKeyStateTrigger[nkey] & 0x80) ? true : false;
}
bool GetkeyboardRelease(int nkey)
{
	return (g_aKeyStateRelease[nkey] & 0x80) ? true : false;
}

D3DXVECTOR2 GetMouseVelocity(void)
{
	return D3DXVECTOR2(g_MouseMove);
}