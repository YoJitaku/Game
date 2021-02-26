//=============================================================================
//
// [DirectX.h]
// Author : JITAKU YO
//
//=============================================================================
#pragma once
#include "d3dx9.h"
#include "d3dx9math.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"
//#include <XInput.h>
#include <time.h>
#include <stdio.h>
#include "Main.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")//D3DXCreateTextureFromFile
#pragma comment(lib, "winmm.lib")//FPS計測
#pragma comment(lib, "dinput8.lib")//keyboard
#pragma comment(lib, "dxguid.lib")//IID_IDirectInput8A,GUID_SysKeyboard,GUID_Key
//#pragma comment(lib, "xinput.lib")

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define WIDTH_SCREEN 1920
#define HEIGHT_SCREEN 1080

typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線vector
	D3DCOLOR col; //頂点color
	D3DXVECTOR2 tex; //UV座標
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;//2D頂点情報を保存する

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}POLYGON_2D;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 nor;//法線の向き
	D3DXVECTOR3 size;
}POLYGON_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTexture, nPatternAnime;
	bool bUse;
	int nDisplayNumber;//表示するnum
	int nZeroNumber;//位数計算用
	int nMultipleNumber;//位数計算用
}POLYGON_NUM;

typedef struct
{
	LPD3DXMESH Xfile_Mesh = NULL;//mesh
	LPD3DXBUFFER Xfile_Materials = NULL;//材質buffer
	DWORD Xfile_MaterialNum = 0;//材質num
	D3DXMATRIX Xfile_Mtxworld;//
	D3DXVECTOR3 pos;//各パーツの位置
	D3DXVECTOR3 rot;//各パーツの向き
	D3DXVECTOR3 move;//移動量
	LPDIRECT3DTEXTURE9 g_Textures[10];
	D3DXVECTOR3 MinColBox;
	D3DXVECTOR3 MaxColBox;
	int nIdxModelParent;//親パーツのID
	int nID;
	int nMoveRange;
	float fMoveSpeed;//移動速度
	bool bUse;
	bool bMove;
}MODEL;

typedef enum
{
	MODE_COMPANY = 0, //company name
	MODE_TITLE, //Game title
	MODE_TUTORIAL,
	MODE_MENU,
	MODE_GAME,
	MODE_GCO,//game clear and game over
	MODE_RANKING,
	MODE_MAX,
}MODE;

typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR2 size; //大きさ
	D3DXVECTOR3 move; //移動
	D3DXVECTOR3 nor; //法線向き　normal vector
	bool bUse, bAnime;
	int nPatternAnime, nTextureID, nID;
}BILLBOARD;


HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Update(void);
void Draw(void);
void Uninit(void);
LPDIRECT3DDEVICE9 GetDevice(void);

void UpdateMode(MODE mode);
void DrawMode(MODE mode);
MODE GetMode(void);
void SetMode(MODE mode);
void SetPause(bool bPause);
void DrawFPS(void);