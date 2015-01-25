// StaticControls.h : interface for the CTitleStaticField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TITLESTATICFIELD_H__582BFF00_7B21_11D3_8881_0050040A20EA__INCLUDED_)
#define AFX_TITLESTATICFIELD_H__582BFF00_7B21_11D3_8881_0050040A20EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>
#include "StaticControls.h"

//CColored Static
class CColoredStatic : public CStatic  
{
public:
	CColoredStatic();
	virtual ~CColoredStatic();
	void SetBkColor  ( COLORREF Color);    
    void SetTextColor( COLORREF Color);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
private:
	COLORREF m_TextColor;
	COLORREF m_BkColor;
	CBrush m_BkBrush;
};

//CBlue Static
class CBlueStatic : public CColoredStatic
{
protected:
	virtual void PreSubclassWindow();
private:
	CFont* GetTheFont();
};

//CTitleStaticField
class CTitleStaticField : public CColoredStatic  
{
public:
	CTitleStaticField() {}
	virtual ~CTitleStaticField() {}
protected:
	virtual void PreSubclassWindow();
private:
	CFont* GetTheFont();
};


//CSmallTitleStaticField
class CSmallTitleStaticField : public CColoredStatic  
{
protected:
	virtual void PreSubclassWindow();
private:
	CFont* GetTheFont();
};

#endif // !defined(AFX_TITLESTATICFIELD_H__582BFF00_7B21_11D3_8881_0050040A20EA__INCLUDED_)
