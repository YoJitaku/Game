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
	int nZeroNum;//åvéZÇ∑ÇÈÇ∆Ç´0ÇÃå¬êî
	unsigned int nMultipleNum;//
	int nDisplayNum;//ï\é¶ÇµÇΩÇ¢number
	bool bUse;
}SCORE_NUM;

HRESULT InitRank(void);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);