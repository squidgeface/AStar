//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Clock.h"
#include "level.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sprite.h"
#include "HUD.h"


// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_pLevel(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_pHud(0)
, m_MouseX(0)
, m_MouseY(0)
, m_isClicked(0)
{

}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;

	delete m_pHud;
	m_pHud = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hApplicationInstance = _hInstance;
    m_hMainWindow = _hWnd;

    m_pClock = new CClock();
    VALIDATE(m_pClock ->Initialise());
    m_pClock->Process();

    m_pBackBuffer = new CBackBuffer();
    VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	m_pHud = new CHUD(_hWnd);
	
	
	SetMousePosition(m_MouseX, m_MouseY);
	
	//ShowCursor(false);

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();
	m_pLevel->SetMouse(m_MouseX, m_MouseY);
	/*m_pHud->SetMousePosition(m_MouseX, m_MouseY);
	m_pHud->DrawHUD();*/

// Do all the game’s drawing here...
	m_pLevel->Draw();

    m_pBackBuffer->Present();


}

void
CGame::Process(float _fDeltaTick)
{
	
    // Process all the game’s logic here.
	//Load a new sprite.
	m_pLevel->Process(_fDeltaTick);
}

void 
CGame::ExecuteOneFrame(int _iMouseX, int _iMouseY, bool _mouse, ECHOICE _choice)
{

	SetMouseClicked(_mouse);
	SetMousePosition(_iMouseX, _iMouseY);
	SetChoice(_choice);
    float fDT = m_pClock->GetDeltaTick();

    Process(fDT);
    Draw();

    m_pClock->Process();

    Sleep(1);
}

CGame&
CGame::GetInstance()
{
	

    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}



void 
CGame::DestroyInstance()
{
    delete s_pGame;
    s_pGame = 0;
}

void CGame::SetMousePosition(int _iX, int _iY)
{
	m_MouseX = _iX;
	m_MouseY = _iY;
}

void CGame::SetMouseClicked(bool _isClicked)
{
	m_isClicked = _isClicked;
	m_pLevel->isClicked(_isClicked);
}

void CGame::SetChoice(ECHOICE _choice)
{
	m_pLevel->SetChoice(_choice);
}

CBackBuffer* 
CGame::GetBackBuffer()
{
    return (m_pBackBuffer);
}

CLevel*
CGame::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE 
CGame::GetAppInstance()
{
    return (m_hApplicationInstance);
}

HWND 
CGame::GetWindow()
{
    return (m_hMainWindow);
}
