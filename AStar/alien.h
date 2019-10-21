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

#if !defined(__ALIEN_H__)
#define __ALIEN_H__

// Library Includes

// Local Includes
#include "entity.h"

class CAlien : public CEntity
{
public:
	CAlien();
	virtual ~CAlien();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

protected:

private:
	CAlien(const CAlien& _kr);
	CAlien& operator= (const CAlien& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;

private:

};

#endif //__ALIEN_H__