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
		VALIDATE(pBrick->Initialise());

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

