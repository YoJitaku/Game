//=============================================================================
//
// [Title1.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_TITLE1 (4)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nPatterAnim;
	bool bUse;
}TITLE1;

void SetTitle1(void);
HRESULT InitTitle1(void);
void UninitTitle1(void);
void UpdateTitle1(void);
void DrawTitle1(void);

