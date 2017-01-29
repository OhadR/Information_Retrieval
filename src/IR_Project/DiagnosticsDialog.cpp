// DiagnosticsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "IR_Project.h"
#include "DiagnosticsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagnosticsDialog dialog


CDiagnosticsDialog::CDiagnosticsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagnosticsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiagnosticsDialog)
	m_NumOfWordsFilteredSinceTooShort = 0;
	m_NumOfWordsFilteredSinceTooLong = 0;
	m_NumOfTotalWords = 0;
	m_NumOfUniqueWords = 0;
	m_nStopListSize = 0;
	//}}AFX_DATA_INIT
}


void CDiagnosticsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagnosticsDialog)
	DDX_Control(pDX, IDC_STOP_LIST_EDIT, m_StopListEdit);
	DDX_Control(pDX, IDC_GROUPS_EDIT, m_GroupsEditCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_NumOfWordsFilteredSinceTooShort);
	DDX_Text(pDX, IDC_EDIT2, m_NumOfWordsFilteredSinceTooLong);
	DDX_Text(pDX, IDC_TOTAL_WORDS_EDIT, m_NumOfTotalWords);
	DDX_Text(pDX, IDC_UNIQUE_WORDS_EDIT, m_NumOfUniqueWords);
	DDX_Text(pDX, IDC_STOPLIST_SIZE_EDIT, m_nStopListSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiagnosticsDialog, CDialog)
	//{{AFX_MSG_MAP(CDiagnosticsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagnosticsDialog message handlers

BOOL CDiagnosticsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString GroupsEditText;

	TGroups::const_iterator GroupIt;
	TWordsCollection::const_iterator	WordsIt;

	//groups:
	for( GroupIt = m_groups.begin();
	GroupIt != m_groups.end();
	++GroupIt )
	{
		SGroup theGroup = *GroupIt;
		GroupsEditText += "\r\n";
		GroupsEditText += theGroup._name.c_str();
		GroupsEditText += "\r\n=========\r\n";
		
		for( WordsIt = theGroup._Words.begin();
		WordsIt != theGroup._Words.end();
		++WordsIt )
		{
			std::string theWord = *WordsIt;
			GroupsEditText += theWord.c_str();
			GroupsEditText += "\r\n";
		}
	}
	m_GroupsEditCtrl.SetWindowText(GroupsEditText);

	//stop list:
	GroupsEditText = "";
	for( WordsIt = m_StopList.begin();
	WordsIt != m_StopList.end();
	++WordsIt )
	{
		std::string theWord = *WordsIt;
		GroupsEditText += theWord.c_str();
		GroupsEditText += " ";
	}
	m_StopListEdit.SetWindowText(GroupsEditText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
