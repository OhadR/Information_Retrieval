; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSearchAssignmentDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SearchAssignment.h"

ClassCount=2
Class1=CSearchAssignmentApp
Class2=CSearchAssignmentDlg

ResourceCount=5
Resource2=IDR_MAINFRAME
Resource3=IDD_SEARCHASSIGNMENT_DIALOG
Resource4=IDD_SEARCHASSIGNMENT_DIALOG (English (U.S.))
Resource5=IDD_FILE_VIEWER

[CLS:CSearchAssignmentApp]
Type=0
HeaderFile=SearchAssignment.h
ImplementationFile=SearchAssignment.cpp
Filter=N

[CLS:CSearchAssignmentDlg]
Type=0
HeaderFile=SearchAssignmentDlg.h
ImplementationFile=SearchAssignmentDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSearchAssignmentDlg



[DLG:IDD_SEARCHASSIGNMENT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSearchAssignmentDlg

[DLG:IDD_SEARCHASSIGNMENT_DIALOG (English (U.S.))]
Type=1
Class=CSearchAssignmentDlg
ControlCount=14
Control1=IDOK,button,1342242816
Control2=IDC_QUERYEDIT,edit,1350631552
Control3=IDC_SHOWBUTTON,button,1342242817
Control4=IDC_SEARCHBUTTON,button,1342242816
Control5=IDC_BUILDBUTTON,button,1342242816
Control6=IDC_BUILDPATHEDIT,edit,1350631552
Control7=IDC_BUILDSTATIC,static,1342308352
Control8=IDC_SEARCHSTATIC,static,1342308352
Control9=IDC_OUTPUTFILESSTATIC,static,1342308352
Control10=IDC_OUTPUTFILESPATHEDIT,edit,1350631552
Control11=IDC_RESULTS_STATIC,static,1342308352
Control12=IDC_SEARCH_RESULTS_LIST,SysListView32,1350631425
Control13=IDC_STATUS_STATIC,static,1342308352
Control14=IDC_TITLE_STATIC,static,1342308353

[DLG:IDD_FILE_VIEWER]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_FILE_VIEWER_TITLE_STATIC,static,1342308353
Control3=IDC_FILE_VIEWER_EDIT,edit,1353777348

