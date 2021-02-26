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
void SetWorldBillboard(void);
HRESULT InitWorldBillboard(void);
void UninitWorldBillboard(void);
void UpdateWorldBillboard(void);
void DrawWorldBillboard(void);