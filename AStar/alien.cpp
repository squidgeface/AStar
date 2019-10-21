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
#include "resource.h"
#include "utils.h"

// This Include
#include "alien.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAlien::CAlien()
	: m_bHit(false)
{
}


CAlien::~CAlien()
{
}

bool
CAlien::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_EMPTY));

	return (true);
}

void
CAlien::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CAlien::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void
CAlien::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CAlien::IsHit() const
{
	return (m_bHit);
}