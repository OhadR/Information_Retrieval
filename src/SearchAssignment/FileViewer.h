/****************************************************************/
/*						FileViewer.H					        */
/*				      by: Ohad Redlich							*/
/*						18.8.2000								*/
/****************************************************************/


#if !defined(AFX_FILEVIEWER_H__)
#define AFX_FILEVIEWER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../Basic/StaticControls.h"
#include "VectorianModel.h"		//MAX_LINE_SIZE


class CFileViewer : public CDialog
{
public:
	CFileViewer( CString FileName, UINT IDD);
	virtual ~CFileViewer() {}

	void ShowFile();

protected:
	DECLARE_MESSAGE_MAP()

    enum { IDD = IDD_FILE_VIEWER };
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	//void OnOk();

private:
    FILE*				m_File;

	CTitleStaticField	m_Title;
	CString				m_FileName;
	CEdit				m_Viewer;
};

#endif // !defined(AFX_FILEVIEWER_H__)
