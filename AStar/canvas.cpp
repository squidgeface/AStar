/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2019 Media Design School

  File Name   :   canvas.cpp
  Description :   Canvas initialisation file
  Author      :   Alexander Jenkins
  Mail        :   alexander.jen8470@mediadesign.school.nz
********************/

#include "shape.h"
#include "backBuffer.h"
#include "canvas.h"

CCanvas::CCanvas()
{
	m_pBackBuffer = new CBackBuffer();
}
CCanvas::~CCanvas()
{

}

bool CCanvas::Initialise(HWND _hwnd, int _iWidth, int _iHeight)
{
	m_pBackBuffer->Initialise(_hwnd, _iWidth, _iHeight);
	return true;
}

CBackBuffer* CCanvas::GetBackBuffer()
{
	return m_pBackBuffer;
}

bool CCanvas::Draw(HDC _hdc)
{
	auto iter = m_shapes.begin();
	m_pBackBuffer->Clear();
	while (iter != m_shapes.end())
	{
		(*iter)->Draw(m_pBackBuffer->GetBFDC());
		iter++;
	}
	m_pBackBuffer->Present();
	return true;
}

void CCanvas::Save(HWND _hwnd)
{

}

void CCanvas::AddShape(IShape* _shape)
{
	m_shapes.push_back(_shape);
}

void CCanvas::AddStamp(CStamp*)
{

}