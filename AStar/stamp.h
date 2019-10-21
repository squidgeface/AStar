/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2019 Media Design School

  File Name   :   stamp.h
  Description :   Stamp header file
  Author      :   Alexander Jenkins
  Mail        :   alexander.jen8470@mediadesign.school.nz
********************/

#ifndef __STAMP_H__
#define __STAMP_H__

#include <Windows.h>

#include "shape.h"
class CStamp : public IShape
{
public:
	CStamp();
	CStamp(HINSTANCE _hInstance, int _ID);
	virtual ~CStamp();

	virtual void Draw(HDC _hdc);
	void SetStartX(int _iX);
	void SetStartY(int _iY);

private:
	HBITMAP m_hBitMap;
	BITMAP m_bitmapStructure;
	HINSTANCE hInstance;
	HBRUSH myBrush;
};

#endif