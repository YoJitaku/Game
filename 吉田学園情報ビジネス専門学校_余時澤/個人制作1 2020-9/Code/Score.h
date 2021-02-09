//=============================================================================
//
// [Score.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_SCORE (8)
#define SCORE_SIZE_X (15)
#define SCORE_SIZE_Y (25)

typedef struct
{
	D3DXVECTOR3 pos;
	int nZeroNumber;//åvéZÇ∑ÇÈÇ∆Ç´0ÇÃå¬êî
	unsigned int nMultipleNumber;//
	int nDisplayNumber;//ï\é¶ÇµÇΩÇ¢number
	bool bUse;
}SCORE;

void SetTextureScore(int nIdx, int nDisplayNumber);
HRESULT InitScore(void);
void DrawScore(void);
void UninitScore(void);
void UpdateScore(void);
void AddScore(int nValue);
void SetTextureScore(int nIdx, int nDisplayNumber);
void ReadFile(void);
int GetScore(void);