//=============================================================================
//
// [BackGround.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define BACKGROUND_NUM (6)//StageÇÃêî
#define BACKGROUND_STAGE_1 1//title 
#define BACKGROUND_STAGE_2 6//menu 
#define BACKGROUND_STAGE_3 1//handbook 
#define BACKGROUND_STAGE_4 6//stage1 
#define BACKGROUND_STAGE_5 6//stage2 
#define BACKGROUND_STAGE_6 1//rank
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 size;
	int nType;
	float fSpeed, fTexture;
}BACKGROUND;

void SetBackground(int nStage);
HRESULT InitBackground(int nStage);
void UninitBackground(int nStage);
void UpdateBackground(int nStage);
void DrawBackground(int nStage);
BACKGROUND GetBackground(void);