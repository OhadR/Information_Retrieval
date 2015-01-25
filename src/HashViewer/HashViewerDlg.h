// HashViewerDlg.h : header file
//

#if !defined(_HASHVIEWERDLG_H__)
#define _HASHVIEWERDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpreadSheet.h"
#include "../Basic/IndexFile.h"

/////////////////////////////////////////////////////////////////////////////
// CHashViewerDlg dialog

class CHashViewerDlg : public CDialog
{
public:
	CHashViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHashViewerDlg)
	enum { IDD = IDD_HASHVIEWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	CSpreadSheet		m_Spread;
	CIndexFile*			m_Dictionary;

	void InitSpread();

	// Generated message map functions
	//{{AFX_MSG(CHashViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFillViewer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_HASHVIEWERDLG_H__)
