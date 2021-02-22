//=============================================================================
//
// [WorldModel.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define WORLDMODEL_NUM 1

void SetWorldModel(void);
void InitWorldModel(void);
void UninitWorldModel(void);
void UpdateWorldModel(void);
void DrawWorldModel(void);
MODEL *GetWorldModel(void);