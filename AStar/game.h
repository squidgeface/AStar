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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "clock.h"
#include "PathFinding.h"

// Types

// Constants

// Prototypes
class CLevel;
class CBackBuffer;
class CHUD;
class CPathFinding;

enum ECHOICE
{
	NONE,
	START,
	END,
	BLOCKER
};

class CGame
{
    // Member Functions
public:
    virtual ~CGame();
	CGame();
    virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    void ExecuteOneFrame(int _iMouseX, int _iMouseY, bool _mouse, ECHOICE _choice, bool _pathing);

    CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
    HINSTANCE GetAppInstance();
    HWND GetWindow();

	bool PathFinding();

	void InitialisePath();

	bool RestartLevel(int _iWidth, int _iHeight);

	

    // Singleton Methods
    static CGame& GetInstance();
    static void DestroyInstance();
	void SetMousePosition(int _iX, int _iY);

	void SetMouseClicked(bool _isClicked);

	void SetChoice(ECHOICE _choice);

protected:

private:
    
    CGame(const CGame& _kr);
    CGame& operator= (const CGame& _kr);

    // Member Variables
public:
	

protected:
    CClock* m_pClock;
	CLevel* m_pLevel;
	CHUD* m_pHud;
	CPathFinding* m_pPathFinding;
	SearchCell* cellPathing;

    CBackBuffer* m_pBackBuffer;

    //Application data
    HINSTANCE m_hApplicationInstance;
    HWND m_hMainWindow;
	POINT m_WindowCoords;

	int m_MouseX;
	int m_MouseY;
	bool m_isClicked;
	bool isPathing;

	int m_PathCounter;

	

    // Singleton Instance
    static CGame* s_pGame;

private:

};

#endif    // __GAME_H__
