//=============================================================================
//
// [WorldModel.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "DirectX.h"

#define WORLDMODEL_NUM 10
#define WORLDMODEL_POS_RANGE_X 5100
#define WORLDMODEL_POS_RANGE_Z 4500
void SetWorldModel(void);
void InitWorldModel(void);
void UninitWorldModel(void);
void UpdateWorldModel(void);
void DrawWorldModel(void);
MODEL *GetWorldModel(void);
