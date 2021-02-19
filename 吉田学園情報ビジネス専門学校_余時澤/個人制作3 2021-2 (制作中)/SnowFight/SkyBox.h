//=============================================================================
//
// [SkyBox.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1
#define SKYBOX_LENGTH 20000
#define SKYBOX_POLY 5
const float fSkyboxSpeed  = -0.000005f;

HRESULT InitSkyBox(void);
void UninitSkyBox(void);
void DrawSkyBox(void);