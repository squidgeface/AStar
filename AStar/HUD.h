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

#ifndef __HUD_H__
#define __HUD_H__

#include <string>
#include <Windows.h>



class CHUD
{
public:
	CHUD();
	CHUD(HWND _hwnd);
	~CHUD();
	void DrawHUD();
	
	void SetMousePosition(int _iX, int _iY);
	
	

private:
	HWND m_hwnd;
	POINT m_WindowCoords;
	int m_MouseX;
	int m_MouseY;
	
};
#endif