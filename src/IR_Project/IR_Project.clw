; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDiagnosticsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IR_Project.h"

ClassCount=4
Class1=CIR_ProjectApp
Class2=CIR_ProjectDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IR_PROJECT_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_IR_PROJECT_DIALOG (English (U.S.))
Class4=CDiagnosticsDialog
Resource6=IDD_DIAGNOSTICS_DIALOG

[CLS:CIR_ProjectApp]
Type=0
HeaderFile=IR_Project.h
ImplementationFile=IR_Project.cpp
Filter=N
LastObject=CIR_ProjectApp

[CLS:CIR_ProjectDlg]
Type=0
HeaderFile=IR_ProjectDlg.h
ImplementationFile=IR_ProjectDlg.cpp
Filter=D
LastObject=CIR_ProjectDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=IR_ProjectDlg.h
ImplementationFile=IR_ProjectDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_IR_PROJECT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CIR_ProjectDlg

[DLG:IDD_IR_PROJECT_DIALOG (English (U.S.))]
Type=1
Class=CIR_ProjectDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDC_PATH_EDIT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_QUERY_EDIT,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SEARCH_RESULTS_LIST,SysListView32,1350631425
Control8=IDC_BUILD_BUTTON,button,1342242816
Control9=IDC_SEARCH_BUTTON,button,1342242816
Control10=IDC_FILE_VIEWER_EDIT,edit,1353777348
Control11=IDC_SHOW_BUTTON,button,1342242816
Control12=IDC_GRP_NAME_EDIT,edit,1350631552
Control13=IDC_GRP_MMBRS_EDIT,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SET_GRP_BUTTON,button,1342242816
Control17=IDC_STATIC,button,1342177287
Control18=IDC_DIAGNOSTICS_BUTTON,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIAGNOSTICS_DIALOG]
Type=1
Class=CDiagnosticsDialog
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_EDIT2,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TOTAL_WORDS_EDIT,edit,1350633600
Control9=IDC_UNIQUE_WORDS_EDIT,edit,1350633600
Control10=IDC_GROUPS_EDIT,edit,1353908420
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STOP_LIST_EDIT,edit,1350633600
Control13=IDC_STOPLIST_SIZE_EDIT,edit,1350633600
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352

[CLS:CDiagnosticsDialog]
Type=0
HeaderFile=DiagnosticsDialog.h
ImplementationFile=DiagnosticsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_STOP_LIST_EDIT
VirtualFilter=dWC

