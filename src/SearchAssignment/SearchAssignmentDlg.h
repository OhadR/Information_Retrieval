/****************************************************************/
/*			     SearchAssignmentDlg.h							*/
/*	  Definition of the CSearchAssignmentDlg Class				*/
/****************************************************************/

#if !defined(AFX_SEARCHASSIGNMENTDLG_H__)
#define AFX_SEARCHASSIGNMENTDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VectorianModel.h"				//CVectorianModel, Status, etc...
#include "../Basic/ColorStaticEx.h"		//CColorStaticEx
#include "../Basic/StaticControls.h"	//CTitleStaticField



/////////////////////////////////////////////////////////////////////////////
// CSearchAssignmentDlg dialog

class CSearchAssignmentDlg : public CDialog
{
public:
	CSearchAssignmentDlg(CWnd* pParent = NULL);	// standard constructor

	//{{AFX_DATA(CSearchAssignmentDlg)
	enum { IDD = IDD_SEARCHASSIGNMENT_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchAssignmentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSearchAssignmentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSearch();
	afx_msg void OnBuild();
	afx_msg void OnShow();
	//}}AFX_MSG
	void OnListDblclk( NMHDR* pNMHDR, LRESULT* pResult );

	//creating a CVectorianModel instance:
	CVectorianModel m_VectorianModel;

	DECLARE_MESSAGE_MAP()
	void PrintResultsToList( char ppcResultsSortedVector[][SIZE_OF_FILENAME] );

	CTitleStaticField	m_Title;
	CEdit				m_FilesToBuildPath;
	CEdit				m_Query;
	CEdit				m_OutputFilesPath;
	CButton				m_ShowButton;		//will be highlighted
	CListCtrl			m_SearchResultsList;
	CColorStaticEx		m_StatusStatic;
};

#endif // !defined(AFX_SEARCHASSIGNMENTDLG_H__)
