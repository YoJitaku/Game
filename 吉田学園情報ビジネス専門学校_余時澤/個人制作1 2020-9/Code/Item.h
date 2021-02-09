//=============================================================================
//
// [Item.h]
// Author : Yo Jitaku
//
//=============================================================================
#include "DirectX.h"

#define ITEM_NUMBER (10)
#define ITEM_TYPE (2)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR3 move;
	bool bUse;
	int nTypeItem;
}ITEM;

HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
ITEM *GetItem(void);