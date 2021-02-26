//=============================================================================
//
// [Dinput8.h] DirectX input 8
// Author : JITAKU YO
//
//=============================================================================
#ifndef _DINPUT8_H_
#define _DINPUT8_H_
#include "DirectX.h"

#define MOUSE_LOSS 1
typedef enum
{
	LEFT_BUTTON = 0,
	RIGHT_BUTTON,
	MID_BUTTON,
	MAX_BUTTON,
}MOUSEBUTTON;

HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard(void);
void Updatekeyboard(void);
bool GetkeyboardPress(int nkey);
bool GetkeyboardTrigger(int nkey);
bool GetkeyboardRelease(int nkey);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool OnMouseDown(MOUSEBUTTON button_type);
D3DXVECTOR2 GetMouseVelocity(void);
bool GetMouseTrigger(void);
bool GetMouseRelease(void);
#endif // ! _DINPUT8_H
