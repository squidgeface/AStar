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
#include <Windows.h>
#include <string>

#include "utils.h"
#include "HUD.h"

CHUD::CHUD()
{
	m_hwnd = 0;
}

CHUD::CHUD(HWND _hwnd)
	:m_hwnd(_hwnd),
	m_MouseX(0),
	m_MouseY(0)
{
	m_WindowCoords.x = 0;
	m_WindowCoords.y = 0;
}

CHUD::~CHUD()
{

}


void CHUD::SetMousePosition(int _iX, int _iY)
{
	m_MouseX = _iX;
	m_MouseY = _iY;
}


void CHUD::DrawHUD()
{
	HDC hdc = GetDC(m_hwnd);
	std::string output;

	SetTextColor(hdc, RGB(0, 0, 0));

	output = "Mouse X: ";
	output += ToString(m_MouseX);

	TextOutA(hdc, 15, 15, output.c_str(), output.length());
	
	output = "Mouse Y: ";
	output += ToString(m_MouseY);

	TextOutA(hdc, 15, 30, output.c_str(), output.length());
	
	
	ReleaseDC(m_hwnd, hdc);
}