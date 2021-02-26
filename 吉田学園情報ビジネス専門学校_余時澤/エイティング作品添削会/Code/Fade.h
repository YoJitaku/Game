//=============================================================================
//
// [Fade.h]
// Author : Yo Jitaku
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "DirectX.h"

typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;

HRESULT InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, MODE modeNext);
FADE GetFade(void);
#endif

