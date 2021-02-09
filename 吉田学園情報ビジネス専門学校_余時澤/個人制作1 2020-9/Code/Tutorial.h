//=============================================================================
//
// [Tutorial.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define MAX_COMPONENT_TUTORIAL (1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}TUTORIAL;

void SetTutorial(void);
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);