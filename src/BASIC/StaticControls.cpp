// TitleStaticField.cpp: implementation of the CTitleStaticField class.
//
//////////////////////////////////////////////////////////////////////

#include "StaticControls.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//class CColoredStatic
//this class lets the user set the background and text font

BEGIN_MESSAGE_MAP(CColoredStatic, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


CColoredStatic::CColoredStatic()
{
    //Use system colors for defaults
    //
    m_TextColor = ::GetSysColor( COLOR_WINDOWTEXT );
    m_BkColor   = ::GetSysColor( COLOR_3DFACE     );
	m_BkBrush.CreateSolidBrush(m_BkColor);
}

CColoredStatic::~CColoredStatic()
{

}

void CColoredStatic::SetBkColor( COLORREF Color )
{   
    m_BkColor = Color;
    
    m_BkBrush.DeleteObject();
	m_BkBrush.CreateSolidBrush(m_BkColor);
    
    Invalidate();

}

void CColoredStatic::SetTextColor( COLORREF Color )
{   
    m_TextColor = Color;
    
    Invalidate();
}

HBRUSH CColoredStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    pDC->SetTextColor( m_TextColor );
  
    pDC->SetBkColor  ( m_BkColor );

    return (HBRUSH)m_BkBrush;
}

//CBlueStatic this class is a blue static with a font specified in GetTheFont 

void CBlueStatic::PreSubclassWindow() 
{
	SetFont(GetTheFont());
	SetTextColor(RGB(0,0,255));
	CStatic::PreSubclassWindow();
}

CFont* CBlueStatic::GetTheFont()
{
	static BOOL IsCreated = FALSE;
	static CFont font;
	if (!IsCreated)
	{
		font.CreateFont (-17,0,0,0, FW_BOLD, 0, 0, 0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS , DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
		IsCreated = TRUE;
	}
	return &font;
}

//CTitleStaticField class
void CTitleStaticField::PreSubclassWindow() 
{
	SetFont(GetTheFont());
	CStatic::PreSubclassWindow();
}

CFont* CTitleStaticField::GetTheFont()
{
	static BOOL IsCreated = FALSE;
	static CFont font;
	if (!IsCreated)
	{
		font.CreateFont (-20,0,0,0, FW_BOLD, 0, 1, 0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS , DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
		IsCreated = TRUE;
	}
	return &font;
}

void CSmallTitleStaticField::PreSubclassWindow() 
{
	SetFont(GetTheFont());
	CStatic::PreSubclassWindow();
}

CFont* CSmallTitleStaticField::GetTheFont()
{
	static BOOL IsCreated = FALSE;
	static CFont font;
	if (!IsCreated)
	{
		font.CreateFont (-15,0,0,0, FW_BOLD, 0, 0, 0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS , DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
		IsCreated = TRUE;
	}
	return &font;
}
