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
#pragma comment(lib, "winmm.lib")//FPS�v��
#pragma comment(lib, "dinput8.lib")//keyboard
#pragma comment(lib, "dxguid.lib")//IID_IDirectInput8A,GUID_SysKeyboard,GUID_Key
//#pragma comment(lib, "xinput.lib")

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define WIDTH_SCREEN 1920
#define HEIGHT_SCREEN 1080

typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@��vector
	D3DCOLOR col; //���_color
	D3DXVECTOR2 tex; //UV���W
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;//2D���_����ۑ�����

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}POLYGON_2D;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 nor;//�@���̌���
	D3DXVECTOR3 size;
}POLYGON_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTexture, nPatternAnime;
	bool bUse;
	int nDisplayNumber;//�\������num
	int nZeroNumber;//�ʐ��v�Z�p
	int nMultipleNumber;//�ʐ��v�Z�p
}POLYGON_NUM;

typedef struct
{
	LPD3DXMESH Xfile_Mesh = NULL;//mesh
	LPD3DXBUFFER Xfile_Materials = NULL;//�ގ�buffer
	DWORD Xfile_MaterialNum = 0;//�ގ�num
	D3DXMATRIX Xfile_Mtxworld;//
	D3DXVECTOR3 pos;//�e�p�[�c�̈ʒu
	D3DXVECTOR3 rot;//�e�p�[�c�̌���
	D3DXVECTOR3 move;//�ړ���
	LPDIRECT3DTEXTURE9 g_Textures[10];
	D3DXVECTOR3 MinColBox;
	D3DXVECTOR3 MaxColBox;
	int nIdxModelParent;//�e�p�[�c��ID
	int nID;
	int nMoveRange;
	float fMoveSpeed;//�ړ����x
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
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR2 size; //�傫��
	D3DXVECTOR3 move; //�ړ�
	D3DXVECTOR3 nor; //�@�������@normal vector
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