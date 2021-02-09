//=============================================================================
//
// [UI.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_UI_COMPONET (7)
#define UI_TYPE (4)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nType, nPatterAnim = 0;
	bool bUse;
}UI;

void SetUI(void);
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

