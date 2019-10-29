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
#include <vector>
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
	, m_iStartPos(0)
	, m_iEndPos(0)
	, m_iBlocker(0)
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
				/*if (i <= 9)
				{
					m_vecArray[0][i] = 1;
				}
				else if (i >= 10 && i <= 19)
				{
					m_vecArray[1][i - 10] = 1;
				}
				else if (i >= 20 && i <= 29)
				{
					m_vecArray[2][i - 20] = 1;
				}
				else if (i >= 30 && i <= 39)
				{
					m_vecArray[3][i - 30] = 1;
				}
				else if (i >= 40 && i <= 49)
				{
					m_vecArray[4][i - 40] = 1;
				}
				else if (i >= 50 && i <= 59)
				{
					m_vecArray[5][i - 50] = 1;
				}
				else if (i >= 60 && i <= 69)
				{
					m_vecArray[6][i - 60] = 1;
				}
				else if (i >= 70 && i <= 79)
				{
					m_vecArray[7][i - 70] = 1;
				}
				else if (i >= 80 && i <= 89)
				{
					m_vecArray[8][i - 80] = 1;
				}
				else if (i >= 90 && i <= 99)
				{
					m_vecArray[9][i - 90] = 1;
				}*/
				
				VALIDATE(_vecBrick[i]->Initialise(IDB_START));
				start = true;
				m_iStartPos = i;
			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == END && !end)
			{
				/*if (i <= 9)
				{
					m_vecArray[0][i] = 2;
				}
				else if (i >= 10 && i <= 19)
				{
					m_vecArray[1][i - 10] = 2;
				}
				else if (i >= 20 && i <= 29)
				{
					m_vecArray[2][i - 20] = 2;
				}
				else if (i >= 30 && i <= 39)
				{
					m_vecArray[3][i - 30] = 2;
				}
				else if (i >= 40 && i <= 49)
				{
					m_vecArray[4][i - 40] = 2;
				}
				else if (i >= 50 && i <= 59)
				{
					m_vecArray[5][i - 50] = 2;
				}
				else if (i >= 60 && i <= 69)
				{
					m_vecArray[6][i - 60] = 2;
				}
				else if (i >= 70 && i <= 79)
				{
					m_vecArray[7][i - 70] = 2;
				}
				else if (i >= 80 && i <= 89)
				{
					m_vecArray[8][i - 80] = 2;
				}
				else if (i >= 90 && i <= 99)
				{
					m_vecArray[9][i - 90] = 2;
				}*/
				VALIDATE(_vecBrick[i]->Initialise(IDB_GOAL));
				end = true;
				m_iEndPos = i;
			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == BLOCKER)
			{
				/*if (i <= 9)
				{
					m_vecArray[0][i] = 3;
				}
				else if (i >= 10 && i <= 19)
				{
					m_vecArray[1][i - 10] = 3;
				}
				else if (i >= 20 && i <= 29)
				{
					m_vecArray[2][i - 20] = 3;
				}
				else if (i >= 30 && i <= 39)
				{
					m_vecArray[3][i - 30] = 3;
				}
				else if (i >= 40 && i <= 49)
				{
					m_vecArray[4][i - 40] = 3;
				}
				else if (i >= 50 && i <= 59)
				{
					m_vecArray[5][i - 50] = 3;
				}
				else if (i >= 60 && i <= 69)
				{
					m_vecArray[6][i - 60] = 3;
				}
				else if (i >= 70 && i <= 79)
				{
					m_vecArray[7][i - 70] = 3;
				}
				else if (i >= 80 && i <= 89)
				{
					m_vecArray[8][i - 80] = 3;
				}
				else if (i >= 90 && i <= 99)
				{
					m_vecArray[9][i - 90] = 3;
				}*/
				VALIDATE(_vecBrick[i]->Initialise(IDB_BLOCKER));
				m_iBlocker = i;
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

