// IR_ProjectDlg.h : header file
//

#if !defined(AFX_IR_PROJECTDLG_H__3CB11C0B_24FB_4BD8_9A55_21DF81585311__INCLUDED_)
#define AFX_IR_PROJECTDLG_H__3CB11C0B_24FB_4BD8_9A55_21DF81585311__INCLUDED_

#include "AlgorithmManager.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIR_ProjectDlg dialog

#include "TWScriptEdit.h"

class CIR_ProjectDlg : public CDialog, public CRegistrated
{
private:
	CString m_strSearchKeywords;
// Construction
public:
	CIR_ProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIR_ProjectDlg)
	enum { IDD = IDD_IR_PROJECT_DIALOG };
	CEdit	m_GrpNameEdit;
	CEdit	m_GrpMembersEdit;
	CListCtrl	m_ResultsList;
	CEdit	m_QueryEdit;
	CEdit	m_PathEdit;
	CTWScriptEdit	m_FileViewer;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIR_ProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void Write(const std::string&);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIR_ProjectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBuildButton();
	afx_msg void OnSearchButton();
	afx_msg void OnShowButton();
	afx_msg void OnSetGrpButton();
	afx_msg void OnDiagnosticsButton();
	virtual void OnOK();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void PrintResultsToList( const TDocIdVector& ResultsSortedVector );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IR_PROJECTDLG_H__3CB11C0B_24FB_4BD8_9A55_21DF81585311__INCLUDED_)
