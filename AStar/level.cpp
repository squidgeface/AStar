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
#include "SearchCell.h"


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
	, blocker(false)
	, m_iStartPos(0)
	, m_iEndPos(0)
	, m_iBlocker(0)
	, m_iCounter(0)
	, process(false)
{
	startCell = new SearchCell(-1, -1);
	endCell = new SearchCell(-1, -1);
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

		blankCell = new SearchCell(0,0,0);
		vecAllCells.push_back(blankCell);

		

		if (i <= 9)
		{
			vecAllCells[i]->Ypos = 0;
			vecAllCells[i]->Xpos = i;
		}
		else if (i >= 10 && i <= 19)
		{

			vecAllCells[i]->Ypos = 1;
			vecAllCells[i]->Xpos = i - 10;
		}
		else if (i >= 20 && i <= 29)
		{

			vecAllCells[i]->Ypos = 2;
			vecAllCells[i]->Xpos = i - 20;
		}
		else if (i >= 30 && i <= 39)
		{

			vecAllCells[i]->Ypos = 3;
			vecAllCells[i]->Xpos = i - 30;

		}
		else if (i >= 40 && i <= 49)
		{

			vecAllCells[i]->Ypos = 4;
			vecAllCells[i]->Xpos = i - 40;

		}
		else if (i >= 50 && i <= 59)
		{

			vecAllCells[i]->Ypos = 5;
			vecAllCells[i]->Xpos = i - 50;

		}
		else if (i >= 60 && i <= 69)
		{

			vecAllCells[i]->Ypos = 6;
			vecAllCells[i]->Xpos = i - 60;

		}
		else if (i >= 70 && i <= 79)
		{
			vecAllCells[i]->Ypos = 7;
			vecAllCells[i]->Xpos = i - 70;

		}
		else if (i >= 80 && i <= 89)
		{
			vecAllCells[i]->Ypos = 8;
			vecAllCells[i]->Xpos = i - 80;
		}
		else if (i >= 90 && i <= 99)
		{
			vecAllCells[i]->Ypos = 9;
			vecAllCells[i]->Xpos = i - 90;
			
		}
	
	}

	

	return (true);
}

void
CLevel::Draw()
{
	
	CheckCollision(m_iMouseX, m_iMouseY, m_vecBricks);
	InitialisePath();
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
				
				
				if (i <= 9)
				{
					startCell = new SearchCell(i, 0, 0);
				}
				else if (i >= 10 && i <= 19)
				{

					startCell = new SearchCell(i - 10, 1, 0);
				}
				else if (i >= 20 && i <= 29)
				{
					
					startCell = new SearchCell(i - 20, 2, 0);
				}
				else if (i >= 30 && i <= 39)
				{
					
					startCell = new SearchCell(i - 30, 3, 0);
				}
				else if (i >= 40 && i <= 49)
				{
					
					startCell = new SearchCell(i - 40, 4, 0);
				}
				else if (i >= 50 && i <= 59)
				{
					
					startCell = new SearchCell(i - 50, 5, 0);
				}
				else if (i >= 60 && i <= 69)
				{
				
					startCell = new SearchCell(i - 60, 6, 0);
				}
				else if (i >= 70 && i <= 79)
				{
				
					startCell = new SearchCell(i - 70, 7, 0);
				}
				else if (i >= 80 && i <= 89)
				{
					
					startCell = new SearchCell(i - 80, 8, 0);
				}
				else if (i >= 90 && i <= 99)
				{
					startCell = new SearchCell(i - 90, 9, 0);
					
				}
				
				VALIDATE(_vecBrick[i]->Initialise(IDB_START));
				start = true;
			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == END && !end)
			{
				

				if (i <= 9)
				{
					endCell = new SearchCell(i, 0, 0);


				}
				else if (i >= 10 && i <= 19)
				{

					endCell = new SearchCell(i - 10, 1, 0);
				}
				else if (i >= 20 && i <= 29)
				{

					endCell = new SearchCell(i - 20, 2, 0);
				}
				else if (i >= 30 && i <= 39)
				{

					endCell = new SearchCell(i - 30, 3, 0);
				}
				else if (i >= 40 && i <= 49)
				{

					endCell = new SearchCell(i - 40, 4, 0);
				}
				else if (i >= 50 && i <= 59)
				{

					 endCell = new SearchCell(i - 50, 5, 0);
				}
				else if (i >= 60 && i <= 69)
				{

					endCell = new SearchCell(i - 60, 6, 0);
				}
				else if (i >= 70 && i <= 79)
				{

					endCell = new SearchCell(i - 70, 7, 0);
				}
				else if (i >= 80 && i <= 89)
				{

					endCell = new SearchCell(i - 80, 8, 0);
				}
				else if (i >= 90 && i <= 99)
				{
					endCell = new SearchCell(i - 90, 9, 0);

				}
				
				VALIDATE(_vecBrick[i]->Initialise(IDB_GOAL));
				end = true;

			}
			if (inRange(_vecBrick[i]->GetX() - 24, _vecBrick[i]->GetX() + 24, _iMouseX) && inRange(_vecBrick[i]->GetY() - 24, _vecBrick[i]->GetY() + 24, _iMouseY) && m_ismouseDown && m_choice == BLOCKER)
			{
				if (m_ismouseDown && m_iCounter > 0)
				{
					m_ismouseDown = false;
				}

				if (i <= 9)
				{
					blockerCell = new SearchCell(i, 0, 0);

				}
				else if (i >= 10 && i <= 19)
				{

					blockerCell = new SearchCell(i - 10, 1, 0);
				}
				else if (i >= 20 && i <= 29)
				{

					blockerCell = new SearchCell(i - 20, 2, 0);
				}
				else if (i >= 30 && i <= 39)
				{

					blockerCell = new SearchCell(i - 30, 3, 0);
				}
				else if (i >= 40 && i <= 49)
				{

					blockerCell = new SearchCell(i - 40, 4, 0);
				}
				else if (i >= 50 && i <= 59)
				{

					blockerCell = new SearchCell(i - 50, 5, 0);
				}
				else if (i >= 60 && i <= 69)
				{

					blockerCell = new SearchCell(i - 60, 6, 0);
				}
				else if (i >= 70 && i <= 79)
				{

					blockerCell = new SearchCell(i - 70, 7, 0);
				}
				else if (i >= 80 && i <= 89)
				{

					blockerCell = new SearchCell(i - 80, 8, 0);
				}
				else if (i >= 90 && i <= 99)
				{
					blockerCell = new SearchCell(i - 90, 9, 0);

				}
				
				vecblockerCell.push_back(blockerCell);
				
				

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
	if (_iMouseIsDown && m_iCounter == 0)
	{
		m_ismouseDown = _iMouseIsDown;
		m_iCounter++;
	}
	
	if (!_iMouseIsDown)
	{
		m_ismouseDown = _iMouseIsDown;
		m_iCounter = 0;
	}

}

void CLevel::SetChoice(ECHOICE _choice)
{
	m_choice = _choice;
}

bool
CLevel::ShowPath()
{
	return 0;
}

bool CLevel::InitialisePath()
{
	if (!process)
	{
		if (vecPathCells.size() > 0)
		{
			bool noPath = false;

			for (int j = 0; j < vecAllCells.size(); j++)
			{
				for (int i = 0; i < vecPathCells.size(); i++)
				{
					if (vecPathCells[i]->isBlocker)
					{
						noPath = true;
					}
				}

				if (noPath == false)
				{
					for (int i = 0; i < vecPathCells.size(); i++)
					{
						if (vecAllCells[j]->Xpos == vecPathCells[i]->Xpos && vecAllCells[j]->Ypos == vecPathCells[i]->Ypos)
						{
							m_vecBricks[j]->Initialise(IDB_PATH);
						}
					}
				}
			}
			noPath = false;
			process = true;
		}
		
	}
	return(true);
}