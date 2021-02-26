//=============================================================================
//
// [GCO.h] game clear and game over
// Author : JITAKU YO
//
//=============================================================================
#ifndef _GCO_H_
#define _GCO_H_
#include "DirectX.h"

#define GCO_COMPONENT (2)
HRESULT InitGCO(void);
void UninitGCO(void);
void UpdateGCO(void);
void DrawGCO(void);
#endif