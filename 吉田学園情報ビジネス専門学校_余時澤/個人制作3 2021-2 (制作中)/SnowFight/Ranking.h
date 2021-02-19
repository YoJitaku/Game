//=============================================================================
//
// [Ranking.h]
// Author : JITAKU YO
//
//=============================================================================
#include "DirectX.h"

#define RANK_COMPONENT (1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nZeroNum;//計算するとき0の個数
	unsigned int nMultipleNum;//
	int nDisplayNum;//表示したいnumber
	bool bUse;
}SCORE_NUM;

HRESULT InitRank(void);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);