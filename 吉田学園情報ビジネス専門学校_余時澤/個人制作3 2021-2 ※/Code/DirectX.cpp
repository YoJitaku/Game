//=============================================================================
//
// [DirectX.cpp]
// Author : JITAKU YO
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "DirectX.h"
#include "Xinput.h"
#include "Dinput8.h"
#include "Fade.h"
#include "sound.h"

//画面遷移
#include "Company.h"
#include "Title.h"
#include "Menu.h"
#include "GameClearOver.h"
#include "Ranking.h"
#include "Tutorial.h"

//Main Game
#include "Light.h"
#include "Camera.h"
#include "Ground.h"
#include "WorldBillboard.h"
#include "WorldModel.h"
#include "UI.h"
#include "SkyBox.h"

#include "Player.h"
#include "SnowBall.h"
#include "Enemy.h"
#include "SnowParticle.h"

LPD3DXFONT g_pFont = NULL;
LPDIRECT3D9 g_pD3D = NULL;//user pc's graphics caxrd information get
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_Mode;
bool g_bPause;

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//why use HRESULT?
{
	g_bPause = false;
	g_Mode = MODE_COMPANY;
	//g_Mode = MODE_GAME;
	srand((int)time(0));
	//check the user's hardware character
	D3DDISPLAYMODE d3ddm;//graphics card mode

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//create a d3d object
	if (g_pD3D == NULL) return E_FAIL;

	//check the default graphics card's displaymode
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))return E_FAIL;

	//prepare for get userdevice interface
	D3DPRESENT_PARAMETERS d3dpp;//struct group
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;//FULLSCREEN mode is false
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//check pc device about vertex draw（graphics card version 2 HAL and REF 3 object window handle 4 定点运算标志类型 互斥 5 point to a struct, this struct is describe the device Set which we want to create. 6 return device pointer
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//Render set base
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//Render set about fade (alpha)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//FPS表示 create
	D3DXCreateFont
	(
		g_pD3DDevice,
		30,//size
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont
	);

	Initkeyboard(hInstance, hWnd);
	InitMouse(hInstance, hWnd);
	InitLight();
	InitCamera();
	InitSnowParticle();
	InitGround();
	InitSkyBox();
	InitWorldModel();
	InitWorldBillboard();
	InitSound(hWnd);

	InitFade(MODE_COMPANY);
	SetMode(MODE_COMPANY);
	//InitFade(MODE_GAME);
	//SetMode(MODE_GAME);
	return S_OK;
}

void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	Uninitkeyboard();
	UninitMouse();
	UninitGround();
	UninitWorldModel();
	UninitSkyBox();
	UninitWorldBillboard();
	UninitSnowParticle();
	UninitSound();
	StopSound();

}

void Update(void)
{
	Updatekeyboard();
	UpdateMouse();
	UpdateFade();
	UpdateMode(g_Mode);
}

void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//BeginScene and EndScene to tell the system when it should be start or end the rendering, u can put anyother rendering set between
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawFPS();
		DrawMode(g_Mode);
		DrawFade();
		SetCamera();
#ifdef _DEBUG
		DrawFPS();
#endif
		g_pD3DDevice->EndScene();
	}
	//show the rendering
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

void SetMode(MODE mode)
{
	switch (g_Mode)
	{
	case MODE_COMPANY:
		UninitCompany();
		break;
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_MENU:
		UninitMenu();
		UninitEnemyM();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitUI();
		UninitSnowBall();
		break;
	case MODE_GCO:
		UninitGCO();
		break;
	case MODE_RANKING:
		UninitEnemy();
		UninitRank();
		UninitPlayer();
		break;
	}

	switch (mode)
	{
	case MODE_COMPANY:
		InitCompany();
		break;
	case MODE_TITLE:
		InitTitle();
		PlaySound(SOUND_LABEL_BGM);
		InitPlayer();
		break;
	case MODE_MENU:
		InitEnemyMenu();
		InitMenu();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitPlayer();
		InitEnemy();
		InitUI();
		InitSnowBall();
		break;
	case MODE_GCO:
		InitGCO();
		break;
	case MODE_RANKING:
		InitRank();
		break;
	}
	g_Mode = mode;
}
void UpdateMode(MODE mode)
{
	switch (mode)
	{
	case MODE_COMPANY:
		UpdateCompany();
		break;
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_MENU:
		UpdateMenu();
		UpdateCamera();
		UpdateSnowParticle();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_GAME:
		UpdateUI();
		UpdateWorldModel();
		UpdateSnowBall();
		UpdateEnemy();
		UpdateSnowParticle();
		UpdatePlayer();
		UpdateCamera();
		if (GetkeyboardPress(DIK_RETURN) == TRUE)
		{
			SetFade(FADE_OUT, MODE_RANKING);
		}
		break;
	case MODE_GCO:
		UpdateGCO();
		break;
	case MODE_RANKING:
		UpdateEnemy();
		UpdateWorldModel();
		UpdateCamera();
		UpdateRank();
		UpdateSnowParticle();
		break;
	}
}

void DrawMode(MODE mode)
{
	switch (mode)
	{
	case MODE_COMPANY:
		DrawCompany();
		break;
	case MODE_TITLE:
		DrawTitle();
		break;
	case MODE_MENU:
		DrawSkyBox();
		DrawGround();
		DrawEnemyM();
		DrawSnowParticle();
		DrawWorldBillboard();
		DrawMenu();
		break;
	case MODE_TUTORIAL:
		DrawTutorial();
		break;
	case MODE_GAME:
		DrawGround();
		DrawSkyBox();
		DrawPlayer();
		DrawSnowParticle();
		DrawWorldModel();
		DrawWorldBillboard();
		DrawSnowBall();
		DrawEnemy();
		DrawUI();
		break;
	case MODE_GCO:
		DrawGCO();
		break;
	case MODE_RANKING:
		DrawGround();
		DrawSkyBox();
		DrawSnowParticle();
		DrawWorldModel();
		DrawWorldBillboard();
		DrawEnemy();
		DrawRank();
		break;
	}
}

MODE GetMode(void)
{
	return g_Mode;//今のmod type
}

void SetPause(bool bPause)
{
	g_bPause = bPause;
}

void DrawFPS(void)
{
	//int nCountFPS = GetFps();
	//int nCntString = 0;
	//char aString[1000];
	//RECT rect = { 0, 0, WIDTH_SCREEN, HEIGHT_SCREEN };//check area
	//g_pFont->DrawText(NULL, &aString[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));//draw
}