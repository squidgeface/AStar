/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2019 Media Design School

  File Name   :   shape.cpp
  Description :   Shape initialisation file
  Author      :   Alexander Jenkins
  Mail        :   alexander.jen8470@mediadesign.school.nz
********************/
#include "shape.h"

IShape::IShape()
{

}

IShape::~IShape() 
{

}


void IShape::SetStartX(int _iStartX)
{
	m_iStartX = _iStartX;
}

void IShape::SetEndX(int _iEndX)
{
	m_iEndX = _iEndX;
}

void IShape::SetStartY(int _iStartY)
{
	m_iStartY = _iStartY;
}

void IShape::SetEndY(int _iEndY)
{
	m_iEndY = _iEndY;
}

void IShape::SetColor(COLORREF _newColor)
{
	m_ColorRef = _newColor;
}
