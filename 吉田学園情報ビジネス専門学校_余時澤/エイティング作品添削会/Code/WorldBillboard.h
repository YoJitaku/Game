//=============================================================================
//
// [WorldBillboard.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORLDBILLBOARD_TEX_NUM 2
#define WORLDBILLBOARD_NUM 164

void ReadFileBillboard(void);
HRESULT InitWorldBillboard(void);
void UninitWorldBillboard(void);
void DrawWorldBillboard(void);