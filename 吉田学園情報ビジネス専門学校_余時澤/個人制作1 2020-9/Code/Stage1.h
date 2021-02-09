//=============================================================================
//
// [Stage1.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_STAGE1 (6)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 move;
	int nType, nPatterAnim;
	bool bUse;

}STAGE1;

void SetStage1(void);
HRESULT InitStage1Bg(void);
void UninitStage1Bg(void);
void UpdateStage1Bg(void);
void DrawStage1Bg(void);
STAGE1 *GetStage1Next(void);