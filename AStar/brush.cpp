/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2019 Media Design School

  File Name   :   brush.cpp
  Description :   Brush initialisation file
  Author      :   Alexander Jenkins
  Mail        :   alexander.jen8470@mediadesign.school.nz
********************/
#include "brush.h"



CBrush::CBrush(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY)
{
}

CBrush::CBrush()
{
}

CBrush::~CBrush()
{
}

void CBrush::Draw(HDC _hdc)
{
	// Create the green pen: 
	HPEN black_pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	// Select the pen into the context: 
	HPEN old_pen = static_cast<HPEN>(SelectObject(_hdc, black_pen));

	//start x to end x
	
	LineTo(_hdc, m_iStartX, m_iStartY);
	MoveToEx(_hdc, m_iStartX, m_iStartY, NULL);
	SelectObject(_hdc, old_pen);
	// Restore old pen. 
	DeleteObject(black_pen);
	// Delete the green pen. 
}

void CBrush::SetWidth(int _iNewWidth)
{
}
