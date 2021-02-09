//=============================================================================
//
// [Title2.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_TITLE2 (8)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nPatterAnim;
	bool bUse;
}TITLE2;

void SetTitle2(void);
HRESULT InitTitle2(void);
void UninitTitle2(void);
void UpdateTitle2(void);
void DrawTitle2(void);