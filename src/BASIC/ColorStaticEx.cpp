// ColorStatic.cpp : implementation file
//

#include <afxwin.h>
#include "ColorStaticEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLORSTATIC_FLASH_TIMER_ID	1

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStaticEx::CColorStaticEx()
{
	m_TextColor = ::GetSysColor(COLOR_WINDOWTEXT);
	m_BkColor = ::GetSysColor(COLOR_MENU);

	m_Brush.CreateSolidBrush(m_BkColor);

	m_Flash = FALSE;
	m_FlashRate = 500;
	m_TextOn = TRUE;

	m_OriginalTextColor = m_TextColor;
}

CColorStaticEx::~CColorStaticEx()
{
}

COLORREF CColorStaticEx::GetTextColor() const
{
	return m_TextColor;
}

void CColorStaticEx::SetTextColor(const COLORREF textColor)
{
	if ( m_TextColor != textColor )
	{
		m_TextColor = textColor;

		Invalidate();
	}
}

COLORREF CColorStaticEx::GetBkColor() const
{
	return m_BkColor;
}

void CColorStaticEx::SetBkColor(const COLORREF bkColor)
{
	if ( m_BkColor != bkColor )
	{
		m_BkColor = bkColor;

		if ( (HBRUSH)m_Brush )
		{
			m_Brush.DeleteObject();
		}

		m_Brush.CreateSolidBrush(m_BkColor);

		Invalidate();
	}
}

BOOL CColorStaticEx::IsFlashMode() const
{
	return m_Flash;
}

void CColorStaticEx::SetFlashMode(const BOOL flashMode)
{
	m_Flash = flashMode;

	if ( m_Flash )
	{
		m_TextOn = TRUE;

		SetTimer(COLORSTATIC_FLASH_TIMER_ID, m_FlashRate, NULL);
	}
	else
	{
		KillTimer(COLORSTATIC_FLASH_TIMER_ID);

		m_TextColor = m_OriginalTextColor;

		m_TextOn = TRUE;

		Invalidate();
	}
}

ULONG CColorStaticEx::GetFlashRate() const
{
	return m_FlashRate;
}

void CColorStaticEx::SetFlashRate(const ULONG flashRateMilliseconds)
{
	m_FlashRate = flashRateMilliseconds;

	if ( m_Flash )
	{
		SetFlashMode(FALSE);
		SetFlashMode(TRUE);
	}
}


BEGIN_MESSAGE_MAP(CColorStaticEx, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

void CColorStaticEx::OnTimer(UINT nIDEvent) 
{
	if ( m_TextOn )
	{
		m_OriginalTextColor = m_TextColor;
		m_TextColor = m_BkColor;

		m_TextOn = FALSE;
	}
	else
	{
		m_TextColor = m_OriginalTextColor;

		m_TextOn = TRUE;
	}

	Invalidate();

	CStatic::OnTimer(nIDEvent);
}

HBRUSH CColorStaticEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_TextColor);
	pDC->SetBkColor(m_BkColor);

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return (HBRUSH)m_Brush;
}

/////////////////////////////////////////////////////////////////////////////
// CColorStatic private methods
