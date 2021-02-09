//=============================================================================
//
// [Ranking.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_RANK (2)
#define MAX_COMPONENT_RESULT (8)
#define RESULT_ROW (5)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nType, nPatterAnim = 0;
	bool bUse;
}RANK;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nZeroNum;//�v�Z����Ƃ�0�̌�
	unsigned int nMultipleNum;//
	int nDisplayNum;//�\��������number
	bool bUse;
}RESULT;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
	int nType;//����texture��ۑ����Ă���ԍ�
	bool NewsIn;
}NAME;

typedef struct
{
	int nScore, nHistory;
	char aName[256];
}RANKPLAYER;

void InputNewScore(RANKPLAYER *pRankPlayer);
void OutPutRanking(RANKPLAYER *pRankPlayer);
void SetRank(void);
void ReadFile(RANKPLAYER *pRankPlayer);
void SetTextureResult(int nIdx, int nDisplayNumber);
HRESULT InitRank(void);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);