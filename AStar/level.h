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

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include "game.h"

// Local Includes

// Types

// Constants

// Prototypes
class CBall;
class CPlayer;
class CAlien;


class CLevel
{
	// Member Functions
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	virtual void SetMouse(int _iMouseX, int _iMouseY);
	virtual bool CheckCollision(int _iMouseX, int _iMouseY, std::vector<CAlien*> _vecBrick);
	virtual bool inRange(float _xMin, float _xMax, float x);

	virtual void isClicked(bool _iMouseIsDown);

	void SetChoice(ECHOICE _choice);


protected:


private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
public:

protected:
	
	CBall* m_pBall;
	CPlayer* m_pPaddle;
	std::vector<CAlien*> m_vecBricks;
	
	int m_iMouseX;
	int m_iMouseY;
	bool m_ismouseDown;
	bool end;
	bool start;

	int m_iStartPos;
	int m_iEndPos;
	int m_iBlocker;

	std::vector<int> m_vecConvertor;
	int m_vecArray[10][10];

	ECHOICE m_choice;

	int m_iWidth;
	int m_iHeight;

	int m_iBricksRemaining;

	std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
