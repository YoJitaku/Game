#pragma once
#include "DirectX.h"

//两部分组成 texture 和 particle
#define FOOT_PRINT_FILE_NUM 3
#define FOOT_PRINT_PARTICLE_POLY 20
#define FOOT_PRINT_TEXTURE_POLY 5
HRESULT InitFootPrint(void);
void UninitFootPrint(void);
void UpdateFootPrint(void);
void DrawFootPrint(void);
void SetFootPrint(D3DXVECTOR3 pos, D3DXVECTOR3 rot);