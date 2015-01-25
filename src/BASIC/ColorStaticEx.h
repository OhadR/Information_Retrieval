// ColorStatic.h : header file
//

#ifndef __COLORSTATICEX_H__
#define __COLORSTATICEX_H__

/////////////////////////////////////////////////////////////////////////////
// CColorStatic description
//
// This class subclasses CStatic and adds flexibility in setting the text and
// background colors.
//
// In addition, this class also implements a text flashing mechanism.
// Although the default text mode is not flashing, setting the flash mode to
// TRUE causes the text to start flashing at a default rate of 500msec,
// although that value can be controlled as well.
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStaticEx : public CStatic
{
public:
	CColorStaticEx();
	virtual ~CColorStaticEx();

	COLORREF GetTextColor() const;
	void SetTextColor(const COLORREF textColor);

	COLORREF GetBkColor() const;
	void SetBkColor(const COLORREF bkColor);

	BOOL IsFlashMode() const;
	void SetFlashMode(const BOOL flashMode = TRUE);

	ULONG GetFlashRate() const;
	void SetFlashRate(const ULONG rateMilliseconds);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_TextColor;
	COLORREF m_BkColor;
	CBrush m_Brush;
	BOOL m_Flash;
	ULONG m_FlashRate;
	BOOL m_TextOn;
	COLORREF m_OriginalTextColor;

};

/////////////////////////////////////////////////////////////////////////////

#endif // __COLORSTATICEX_H__
