//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes
#include "resource.h"
// Local Includes
#include "Game.h"
//#include "Player.h"
#include "alien.h"
//#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"



// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL



CLevel::CLevel()
	: m_iBricksRemaining(0)
	, m_pPaddle(0)
	, m_pBall(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_ismouseDown(false)
	, end(false)
	, start(false)
{

}

CLevel::~CLevel()
{
	while (m_vecBricks.size() > 0)
	{
		CAlien* pBrick = m_vecBricks[m_vecBricks.size() - 1];

		m_vecBricks.pop_back();

		delete pBrick;
	}

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBallVelX = 200.0f;
	const float fBallVelY = 75.0f;

	const int kiNumBricks = 100;
	const int kiStartX = 150;
	const int kiStartY = 150;
	const int kiGap = 7;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartY;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		CAlien* pBrick = new CAlien();
		VALIDATE(pBrick->Initialise(IDB_EMPTY));

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

		if (iCurrentX > _iWidth - 150)
		{
			iCurrentX = kiStartX;
			iCurrentY += 50;
		}

		m_vecBricks.push_back(pBrick);
	}


	return (true);
}

void
CLevel::Draw()
{
	
	CheckCollision(m_iMouseX, m_iMouseY, m_vecBricks);

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Draw();
	}
	
}

void
CLevel::Process(float _fDeltaTick)
{

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Process(_fDeltaTick);
	}

}

void CLevel::SetMouse(int _iMouseX, int _iMouseY)
{
	m_iMouseX = _iMouseX;
	m_iMouseY = _iMouseY;
}

bool CLevel::CheckCollision(int _iMouseX, int _iMouseY, std::vector<CAlien*> _vecBrick)
{
	for (int i = 0; i < _vecBrick.size(); i++)
	{
		
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == START && !start)
			{
				
				VALIDATE(_vecBrick[i]->Initialise(IDB_START));
				start = true;
			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == END && !end)
			{

				VALIDATE(_vecBrick[i]->Initialise(IDB_GOAL));
				end = true;
			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == BLOCKER)
			{

				VALIDATE(_vecBrick[i]->Initialise(IDB_BLOCKER));

			}
	}
	return(true);
}

bool CLevel::inRange(float _xMin, float _xMax, float x)
{
	return(_xMin <= x && x <= _xMax);
}

void CLevel::isClicked(bool _iMouseIsDown)
{
	m_ismouseDown = _iMouseIsDown;
}

void CLevel::SetChoice(ECHOICE _choice)
{
	m_choice = _choice;
}

