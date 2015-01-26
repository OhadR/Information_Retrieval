#if !defined(AFX_DIAGNOSTICSDIALOG_H__5BA20B2A_E5CE_4451_8718_1752914ABEE2__INCLUDED_)
#define AFX_DIAGNOSTICSDIALOG_H__5BA20B2A_E5CE_4451_8718_1752914ABEE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

#include "Utils.h"
/////////////////////////////////////////////////////////////////////////////
// CDiagnosticsDialog dialog

class CDiagnosticsDialog : public CDialog
{
// Construction
public:
	CDiagnosticsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiagnosticsDialog)
	enum { IDD = IDD_DIAGNOSTICS_DIALOG };
	CEdit	m_StopListEdit;
	CEdit	m_GroupsEditCtrl;
	int		m_NumOfWordsFilteredSinceTooShort;
	int		m_NumOfWordsFilteredSinceTooLong;
	int		m_NumOfTotalWords;
	int		m_NumOfUniqueWords;
	int		m_nStopListSize;
	//}}AFX_DATA
	TGroups	m_groups;
	TWordsCollection m_StopList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagnosticsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiagnosticsDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGNOSTICSDIALOG_H__5BA20B2A_E5CE_4451_8718_1752914ABEE2__INCLUDED_)
