//=============================================================================
//
// [UI.h]
// Author : JITAKU YO
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_
#include "DirectX.h"

#define UI_POLYGON (0)
#define UI_NUMBER (4)
#define UI_TYPE (2)
#define UI_POS_SPEED 2.f
#define UI_SIZE_SPEED 1.f
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
#endif

