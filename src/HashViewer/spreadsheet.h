#if !defined(AFX_SPREADSHEET_H__3EEAA223_AAFE_11D3_9A2C_0050040A20EA__INCLUDED_)
#define AFX_SPREADSHEET_H__3EEAA223_AAFE_11D3_9A2C_0050040A20EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPicture;
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CSpreadSheet wrapper class
#include <afxwin.h>
#include <afxctl.h>
#include <afxcmn.h>

class CSpreadSheet : public CWnd
{
protected:
	DECLARE_DYNCREATE(CSpreadSheet)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xe2454650, 0x4d87, 0x11d2, { 0xb8, 0xb2, 0x0, 0x0, 0xc0, 0xa, 0x95, 0x8c } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	long GetAction();
	void SetAction(long);
	long GetActiveCol();
	void SetActiveCol(long);
	long GetActiveRow();
	void SetActiveRow(long);
	BOOL GetAllowCellOverflow();
	void SetAllowCellOverflow(BOOL);
	BOOL GetAllowDragDrop();
	void SetAllowDragDrop(BOOL);
	BOOL GetAllowMultiBlocks();
	void SetAllowMultiBlocks(BOOL);
	BOOL GetAllowUserFormulas();
	void SetAllowUserFormulas(BOOL);
	BOOL GetArrowsExitEditMode();
	void SetArrowsExitEditMode(BOOL);
	BOOL GetAutoCalc();
	void SetAutoCalc(BOOL);
	BOOL GetAutoClipboard();
	void SetAutoClipboard(BOOL);
	BOOL GetAutoSize();
	void SetAutoSize(BOOL);
	BOOL GetBlockMode();
	void SetBlockMode(BOOL);
	short GetButtonDrawMode();
	void SetButtonDrawMode(short);
	unsigned long GetCellBorderColor();
	void SetCellBorderColor(unsigned long);
	long GetCellBorderStyle();
	void SetCellBorderStyle(long);
	short GetCellBorderType();
	void SetCellBorderType(short);
	long GetCellType();
	void SetCellType(long);
	BOOL GetChangeMade();
	void SetChangeMade(BOOL);
	CString GetClip();
	void SetClip(LPCTSTR);
	CString GetClipValue();
	void SetClipValue(LPCTSTR);
	long GetCol();
	void SetCol(long);
	long GetCol2();
	void SetCol2(long);
	long GetColHeaderDisplay();
	void SetColHeaderDisplay(long);
	BOOL GetColHidden();
	void SetColHidden(BOOL);
	BOOL GetColPageBreak();
	void SetColPageBreak(BOOL);
	long GetColsFrozen();
	void SetColsFrozen(long);
	long GetCursorStyle();
	void SetCursorStyle(long);
	long GetCursorType();
	void SetCursorType(long);
	BOOL GetDataChanged();
	void SetDataChanged(BOOL);
	long GetDataColCnt();
	void SetDataColCnt(long);
	CString GetDataField();
	void SetDataField(LPCTSTR);
	BOOL GetDataFillEvent();
	void SetDataFillEvent(BOOL);
	long GetDataRowCnt();
	void SetDataRowCnt(long);
	LPUNKNOWN GetDataSource();
	void SetDataSource(LPUNKNOWN);
	BOOL GetDAutoCellTypes();
	void SetDAutoCellTypes(BOOL);
	BOOL GetDAutoFill();
	void SetDAutoFill(BOOL);
	BOOL GetDAutoHeadings();
	void SetDAutoHeadings(BOOL);
	BOOL GetDAutoSave();
	void SetDAutoSave(BOOL);
	long GetDAutoSizeCols();
	void SetDAutoSizeCols(long);
	long GetDestCol();
	void SetDestCol(long);
	long GetDestRow();
	void SetDestRow(long);
	BOOL GetDInformActiveRowChange();
	void SetDInformActiveRowChange(BOOL);
	BOOL GetDisplayColHeaders();
	void SetDisplayColHeaders(BOOL);
	BOOL GetDisplayRowHeaders();
	void SetDisplayRowHeaders(BOOL);
	long GetEditEnterAction();
	void SetEditEnterAction(long);
	BOOL GetEditMode();
	void SetEditMode(BOOL);
	BOOL GetEditModePermanent();
	void SetEditModePermanent(BOOL);
	BOOL GetEditModeReplace();
	void SetEditModeReplace(BOOL);
	short GetFileNum();
	void SetFileNum(short);
	short GetFloatDefCurrencyChar();
	void SetFloatDefCurrencyChar(short);
	short GetFloatDefDecimalChar();
	void SetFloatDefDecimalChar(short);
	short GetFloatDefSepChar();
	void SetFloatDefSepChar(short);
	CString GetFormula();
	void SetFormula(LPCTSTR);
	unsigned long GetGrayAreaBackColor();
	void SetGrayAreaBackColor(unsigned long);
	unsigned long GetGridColor();
	void SetGridColor(unsigned long);
	BOOL GetGridShowHoriz();
	void SetGridShowHoriz(BOOL);
	BOOL GetGridShowVert();
	void SetGridShowVert(BOOL);
	BOOL GetGridSolid();
	void SetGridSolid(BOOL);
	long GetHDCPrinter();
	void SetHDCPrinter(long);
	short GetInterfaceDesigner();
	void SetInterfaceDesigner(short);
	BOOL GetIsBlockSelected();
	void SetIsBlockSelected(BOOL);
	long GetLeftCol();
	void SetLeftCol(long);
	BOOL GetLock();
	void SetLock(BOOL);
	unsigned long GetLockBackColor();
	void SetLockBackColor(unsigned long);
	unsigned long GetLockForeColor();
	void SetLockForeColor(unsigned long);
	long GetMaxCols();
	void SetMaxCols(long);
	long GetMaxRows();
	void SetMaxRows(long);
	double GetMaxTextCellHeight();
	void SetMaxTextCellHeight(double);
	double GetMaxTextCellWidth();
	void SetMaxTextCellWidth(double);
	BOOL GetMoveActiveOnFocus();
	void SetMoveActiveOnFocus(BOOL);
	long GetMultiSelCount();
	void SetMultiSelCount(long);
	long GetMultiSelIndex();
	void SetMultiSelIndex(long);
	BOOL GetNoBeep();
	void SetNoBeep(BOOL);
	BOOL GetNoBorder();
	void SetNoBorder(BOOL);
	long GetOperationMode();
	void SetOperationMode(long);
	long GetPosition();
	void SetPosition(long);
	CString GetPrintAbortMsg();
	void SetPrintAbortMsg(LPCTSTR);
	BOOL GetPrintBorder();
	void SetPrintBorder(BOOL);
	BOOL GetPrintColHeaders();
	void SetPrintColHeaders(BOOL);
	BOOL GetPrintColor();
	void SetPrintColor(BOOL);
	CString GetPrintFooter();
	void SetPrintFooter(LPCTSTR);
	BOOL GetPrintGrid();
	void SetPrintGrid(BOOL);
	CString GetPrintHeader();
	void SetPrintHeader(LPCTSTR);
	CString GetPrintJobName();
	void SetPrintJobName(LPCTSTR);
	long GetPrintMarginBottom();
	void SetPrintMarginBottom(long);
	long GetPrintMarginLeft();
	void SetPrintMarginLeft(long);
	long GetPrintMarginRight();
	void SetPrintMarginRight(long);
	long GetPrintMarginTop();
	void SetPrintMarginTop(long);
	short GetPrintPageEnd();
	void SetPrintPageEnd(short);
	short GetPrintPageStart();
	void SetPrintPageStart(short);
	BOOL GetPrintRowHeaders();
	void SetPrintRowHeaders(BOOL);
	BOOL GetPrintShadows();
	void SetPrintShadows(BOOL);
	long GetPrintType();
	void SetPrintType(long);
	BOOL GetPrintUseDataMax();
	void SetPrintUseDataMax(BOOL);
	BOOL GetProcessTab();
	void SetProcessTab(BOOL);
	BOOL GetProtect();
	void SetProtect(BOOL);
	BOOL GetReDraw();
	void SetReDraw(BOOL);
	BOOL GetRestrictCols();
	void SetRestrictCols(BOOL);
	BOOL GetRestrictRows();
	void SetRestrictRows(BOOL);
	BOOL GetRetainSelBlock();
	void SetRetainSelBlock(BOOL);
	long GetRow();
	void SetRow(long);
	long GetRow2();
	void SetRow2(long);
	long GetRowHeaderDisplay();
	void SetRowHeaderDisplay(long);
	BOOL GetRowHidden();
	void SetRowHidden(BOOL);
	BOOL GetRowPageBreak();
	void SetRowPageBreak(BOOL);
	long GetRowsFrozen();
	void SetRowsFrozen(long);
	BOOL GetScrollBarExtMode();
	void SetScrollBarExtMode(BOOL);
	BOOL GetScrollBarMaxAlign();
	void SetScrollBarMaxAlign(BOOL);
	long GetScrollBars();
	void SetScrollBars(long);
	BOOL GetScrollBarShowMax();
	void SetScrollBarShowMax(BOOL);
	long GetSelBlockCol();
	void SetSelBlockCol(long);
	long GetSelBlockCol2();
	void SetSelBlockCol2(long);
	long GetSelBlockRow();
	void SetSelBlockRow(long);
	long GetSelBlockRow2();
	void SetSelBlockRow2(long);
	short GetSelectBlockOptions();
	void SetSelectBlockOptions(short);
	long GetSelLength();
	void SetSelLength(long);
	long GetSelModeIndex();
	void SetSelModeIndex(long);
	long GetSelModeSelCount();
	void SetSelModeSelCount(long);
	BOOL GetSelModeSelected();
	void SetSelModeSelected(BOOL);
	long GetSelStart();
	void SetSelStart(long);
	CString GetSelText();
	void SetSelText(LPCTSTR);
	unsigned long GetShadowColor();
	void SetShadowColor(unsigned long);
	unsigned long GetShadowDark();
	void SetShadowDark(unsigned long);
	unsigned long GetShadowText();
	void SetShadowText(unsigned long);
	long GetSortBy();
	void SetSortBy(long);
	long GetStartingColNumber();
	void SetStartingColNumber(long);
	long GetStartingRowNumber();
	void SetStartingRowNumber(long);
	long GetTopRow();
	void SetTopRow(long);
	long GetTypeButtonAlign();
	void SetTypeButtonAlign(long);
	unsigned long GetTypeButtonBorderColor();
	void SetTypeButtonBorderColor(unsigned long);
	unsigned long GetTypeButtonColor();
	void SetTypeButtonColor(unsigned long);
	unsigned long GetTypeButtonDarkColor();
	void SetTypeButtonDarkColor(unsigned long);
	unsigned long GetTypeButtonLightColor();
	void SetTypeButtonLightColor(unsigned long);
	CPicture GetTypeButtonPicture();
	void SetTypeButtonPicture(LPDISPATCH);
	CPicture GetTypeButtonPictureDown();
	void SetTypeButtonPictureDown(LPDISPATCH);
	short GetTypeButtonShadowSize();
	void SetTypeButtonShadowSize(short);
	CString GetTypeButtonText();
	void SetTypeButtonText(LPCTSTR);
	unsigned long GetTypeButtonTextColor();
	void SetTypeButtonTextColor(unsigned long);
	long GetTypeButtonType();
	void SetTypeButtonType(long);
	BOOL GetTypeCheckCenter();
	void SetTypeCheckCenter(BOOL);
	CString GetTypeCheckText();
	void SetTypeCheckText(LPCTSTR);
	long GetTypeCheckTextAlign();
	void SetTypeCheckTextAlign(long);
	short GetTypeComboBoxCount();
	void SetTypeComboBoxCount(short);
	short GetTypeComboBoxCurSel();
	void SetTypeComboBoxCurSel(short);
	BOOL GetTypeComboBoxEditable();
	void SetTypeComboBoxEditable(BOOL);
	short GetTypeComboBoxIndex();
	void SetTypeComboBoxIndex(short);
	CString GetTypeComboBoxList();
	void SetTypeComboBoxList(LPCTSTR);
	CString GetTypeComboBoxString();
	void SetTypeComboBoxString(LPCTSTR);
	BOOL GetTypeDateCentury();
	void SetTypeDateCentury(BOOL);
	long GetTypeDateFormat();
	void SetTypeDateFormat(long);
	CString GetTypeDateMax();
	void SetTypeDateMax(LPCTSTR);
	CString GetTypeDateMin();
	void SetTypeDateMin(LPCTSTR);
	short GetTypeDateSeparator();
	void SetTypeDateSeparator(short);
	long GetTypeEditCharCase();
	void SetTypeEditCharCase(long);
	long GetTypeEditCharSet();
	void SetTypeEditCharSet(long);
	BOOL GetTypeEditMultiLine();
	void SetTypeEditMultiLine(BOOL);
	BOOL GetTypeEditPassword();
	void SetTypeEditPassword(BOOL);
	short GetTypeFloatCurrencyChar();
	void SetTypeFloatCurrencyChar(short);
	short GetTypeFloatDecimalChar();
	void SetTypeFloatDecimalChar(short);
	short GetTypeFloatDecimalPlaces();
	void SetTypeFloatDecimalPlaces(short);
	double GetTypeFloatMax();
	void SetTypeFloatMax(double);
	double GetTypeFloatMin();
	void SetTypeFloatMin(double);
	BOOL GetTypeFloatMoney();
	void SetTypeFloatMoney(BOOL);
	BOOL GetTypeFloatSeparator();
	void SetTypeFloatSeparator(BOOL);
	short GetTypeFloatSepChar();
	void SetTypeFloatSepChar(short);
	long GetTypeHAlign();
	void SetTypeHAlign(long);
	long GetTypeIntegerMax();
	void SetTypeIntegerMax(long);
	long GetTypeIntegerMin();
	void SetTypeIntegerMin(long);
	long GetTypeIntegerSpinInc();
	void SetTypeIntegerSpinInc(long);
	BOOL GetTypeIntegerSpinWrap();
	void SetTypeIntegerSpinWrap(BOOL);
	long GetTypeOwnerDrawStyle();
	void SetTypeOwnerDrawStyle(long);
	CString GetTypePicDefaultText();
	void SetTypePicDefaultText(LPCTSTR);
	CString GetTypePicMask();
	void SetTypePicMask(LPCTSTR);
	BOOL GetTypePictCenter();
	void SetTypePictCenter(BOOL);
	BOOL GetTypePictMaintainScale();
	void SetTypePictMaintainScale(BOOL);
	CPicture GetTypePictPicture();
	void SetTypePictPicture(LPDISPATCH);
	BOOL GetTypePictStretch();
	void SetTypePictStretch(BOOL);
	BOOL GetTypeSpin();
	void SetTypeSpin(BOOL);
	BOOL GetTypeTextPrefix();
	void SetTypeTextPrefix(BOOL);
	BOOL GetTypeTextShadow();
	void SetTypeTextShadow(BOOL);
	BOOL GetTypeTextShadowIn();
	void SetTypeTextShadowIn(BOOL);
	BOOL GetTypeTextWordWrap();
	void SetTypeTextWordWrap(BOOL);
	long GetTypeTime24Hour();
	void SetTypeTime24Hour(long);
	CString GetTypeTimeMax();
	void SetTypeTimeMax(LPCTSTR);
	CString GetTypeTimeMin();
	void SetTypeTimeMin(LPCTSTR);
	BOOL GetTypeTimeSeconds();
	void SetTypeTimeSeconds(BOOL);
	short GetTypeTimeSeparator();
	void SetTypeTimeSeparator(short);
	long GetUnitType();
	void SetUnitType(long);
	long GetUserResize();
	void SetUserResize(long);
	long GetUserResizeCol();
	void SetUserResizeCol(long);
	long GetUserResizeRow();
	void SetUserResizeRow(long);
	CString GetValue();
	void SetValue(LPCTSTR);
	long GetVirtualCurRowCount();
	void SetVirtualCurRowCount(long);
	long GetVirtualCurTop();
	void SetVirtualCurTop(long);
	long GetVirtualMaxRows();
	void SetVirtualMaxRows(long);
	BOOL GetVirtualMode();
	void SetVirtualMode(BOOL);
	long GetVirtualOverlap();
	void SetVirtualOverlap(long);
	long GetVirtualRows();
	void SetVirtualRows(long);
	BOOL GetVirtualScrollBuffer();
	void SetVirtualScrollBuffer(BOOL);
	long GetVisibleCols();
	void SetVisibleCols(long);
	long GetVisibleRows();
	void SetVisibleRows(long);
	BOOL GetVScrollSpecial();
	void SetVScrollSpecial(BOOL);
	short GetVScrollSpecialType();
	void SetVScrollSpecialType(short);
	BOOL GetFontBold();
	void SetFontBold(BOOL);
	BOOL GetFontItalic();
	void SetFontItalic(BOOL);
	CString GetFontName();
	void SetFontName(LPCTSTR);
	float GetFontSize();
	void SetFontSize(float);
	BOOL GetFontStrikethru();
	void SetFontStrikethru(BOOL);
	BOOL GetFontUnderline();
	void SetFontUnderline(BOOL);
	CPicture GetCursorIcon();
	void SetCursorIcon(LPDISPATCH);
	long GetPrintOrientation();
	void SetPrintOrientation(long);
	long GetBackColorStyle();
	void SetBackColorStyle(long);
	BOOL GetFormulaSync();
	void SetFormulaSync(BOOL);
	long GetTypeCheckType();
	void SetTypeCheckType(long);
	long GetAppearance();
	void SetAppearance(long);
	short GetTypeComboBoxMaxDrop();
	void SetTypeComboBoxMaxDrop(short);
	short GetTypeMaxEditLen();
	void SetTypeMaxEditLen(short);
	short GetTypeComboBoxWidth();
	void SetTypeComboBoxWidth(short);
	long GetTextTip();
	void SetTextTip(long);
	long GetTextTipDelay();
	void SetTextTipDelay(long);
	long GetScrollBarTrack();
	void SetScrollBarTrack(long);
	long GetTypeVAlign();
	void SetTypeVAlign(long);
	short GetClipboardOptions();
	void SetClipboardOptions(short);
	BOOL GetPrintSmartPrint();
	void SetPrintSmartPrint(BOOL);
	long GetPrintPageOrder();
	void SetPrintPageOrder(long);
	long GetPrintPageCount();
	void SetPrintPageCount(long);
	long GetPrintFirstPageNumber();
	void SetPrintFirstPageNumber(long);
	long GetPrintNextPageBreakCol();
	void SetPrintNextPageBreakCol(long);
	long GetPrintNextPageBreakRow();
	void SetPrintNextPageBreakRow(long);
	long GetTypeComboBoxhWnd();
	void SetTypeComboBoxhWnd(long);
	unsigned long GetSelBackColor();
	void SetSelBackColor(unsigned long);
	unsigned long GetSelForeColor();
	void SetSelForeColor(unsigned long);
	short GetTwoDigitYearMax();
	void SetTwoDigitYearMax(short);
	long GetOLEDropMode();
	void SetOLEDropMode(long);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	short GetBorderStyle();
	void SetBorderStyle(short);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	OLE_HANDLE GetHWnd();
	void SetHWnd(OLE_HANDLE);
	CString GetText();
	void SetText(LPCTSTR);

// Operations
public:
	double GetColWidth(long lCol);
	void SetColWidth(long lCol, double newValue);
	double GetMaxTextColWidth(long lCol);
	void SetMaxTextColWidth(long lCol, double newValue);
	double GetMaxTextRowHeight(long lRow);
	void SetMaxTextRowHeight(long lRow, double newValue);
	double GetRowHeight(long lRow);
	void SetRowHeight(long lRow, double newValue);
	long GetSortKey(short nIndex);
	void SetSortKey(short nIndex, long nNewValue);
	long GetSortKeyOrder(short nIndex);
	void SetSortKeyOrder(short nIndex, long nNewValue);
	CPicture GetTypeCheckPicture(short Index);
	void SetTypeCheckPicture(short Index, LPDISPATCH newValue);
	BOOL AddCustomFunction(LPCTSTR FunctionName, short ParameterCnt);
	BOOL AddCustomFunctionExt(LPCTSTR FunctionName, short MinParamCnt, short MaxParamCnt, long Flags);
	void CFGetCellParam(short Param, long* Col, long* Row);
	double CFGetDoubleParam(short Param);
	double CFGetDoubleParamExt(short Param, double* ParamValue);
	long CFGetLongParam(short Param);
	BOOL CFGetParamInfo(short Param, short* Type, short* Status);
	void CFGetRangeParam(short Param, long* Col, long* Row, long* Col2, long* Row2);
	CString CFGetStringParam(short Param);
	void CFSetResult(const VARIANT& Var);
	CString ColNumberToLetter(long HeaderNumber);
	void ColWidthToTwips(float Width, long* Twips);
	void GetBottomRightCell(long* Col, long* Row);
	BOOL GetCellDirtyFlag(long Col, long Row);
	void GetCellFromScreenCoord(long* Col, long* Row, long x, long y);
	BOOL GetCellPos(long Col, long Row, long* x, long* y, long* Width, long* Height);
	void GetClientArea(long* Width, long* Height);
	long GetColItemData(long Col);
	CString QueryCustomName(LPCTSTR Name);
	CString GetCustomName(LPCTSTR Name);
	BOOL GetDataFillData(VARIANT* Var, short VarType);
	void GetFirstValidCell(long* Col, long* Row);
	long GetItemData();
	BOOL GetIteration(short* MaxIterations, double* MaxChange);
	void GetLastValidCell(long* Col, long* Row);
	long GetMultiSelItem(long SelPrev);
	short GetRefStyle();
	long GetRowItemData(long Row);
	BOOL GetText(long Col, long Row, VARIANT* Var);
	BOOL IsCellSelected(long Col, long Row);
	BOOL IsFormulaValid(LPCTSTR Formula);
	BOOL IsVisible(long Col, long Row, BOOL Partial);
	BOOL LoadFromFile(LPCTSTR FileName);
	BOOL LoadTabFile(LPCTSTR FileName);
	void RowHeightToTwips(long Row, float Height, long* Twips);
	BOOL SaveTabFile(LPCTSTR FileName);
	BOOL SaveToFile(LPCTSTR FileName, BOOL DataOnly);
	BOOL SetCellDirtyFlag(long Col, long Row, BOOL Dirty);
	void SetColItemData(long Col, long Value);
	BOOL SetCustomName(LPCTSTR Name, LPCTSTR Value);
	BOOL SetDataFillData(const VARIANT& Var);
	void SetItemData(long Value);
	void SetIteration(BOOL Iteration, short MaxIterations, double MaxChange);
	void SetRefStyle(short RefStyle);
	void SetRowItemData(long Row, long Value);
	void SetText(long Col, long Row, const VARIANT& Var);
	void TwipsToColWidth(long Twips, float* ColWidth);
	void TwipsToRowHeight(long Row, long Twips, float* RowHeight);
	BOOL GetActionKey(short Action, BOOL* fShift, BOOL* fCtrl, short* Key);
	BOOL SetActionKey(short Action, BOOL fShift, BOOL fCtrl, short Key);
	BOOL GetOddEvenRowColor(long* clrBackOdd, long* clrForeOdd, long* clrBackEven, long* clrForeEven);
	BOOL SetOddEvenRowColor(long clrBackOdd, long clrForeOdd, long clrBackEven, long clrForeEven);
	BOOL GetFloat(long Col, long Row, double* Value);
	BOOL SetFloat(long Col, long Row, double Value);
	BOOL GetInteger(long Col, long Row, long* Value);
	BOOL SetInteger(long Col, long Row, long Value);
	void SetCalText(LPCTSTR ShortDays, LPCTSTR LongDays, LPCTSTR ShortMonths, LPCTSTR LongMonths, LPCTSTR OkText, LPCTSTR CancelText);
	BOOL GetTextTipAppearance(BSTR* FontName, short* FontSize, BOOL* FontBold, BOOL* FontItalic, long* BackColor, long* ForeColor);
	BOOL SetTextTipAppearance(LPCTSTR FontName, short FontSize, BOOL FontBold, BOOL FontItalic, long BackColor, long ForeColor);
	BOOL ExportToHTML(LPCTSTR FileName, BOOL AppendFlag, LPCTSTR LogFile);
	BOOL ExportRangeToHTML(long Col, long Row, long Col2, long Row2, LPCTSTR FileName, BOOL AppendFlag, LPCTSTR LogFile);
	BOOL GetArray(long ColLeft, long RowTop, const VARIANT& VarArray);
	BOOL SetArray(long ColLeft, long RowTop, const VARIANT& VarArray);
	short IsExcelFile(LPCTSTR FileName);
	BOOL GetExcelSheetList(LPCTSTR FileName, const VARIANT& VarArray, short* ListCount, LPCTSTR LogFileName, short* WorkbookHandle, BOOL Replace);
	BOOL ImportExcelSheet(short WorkbookHandle, const VARIANT& Sheet);
	BOOL ExportToExcel(LPCTSTR FileName, LPCTSTR SheetName, LPCTSTR LogFileName);
	BOOL EnumCustomFunction(LPCTSTR PrevFuncName, BSTR* FuncName);
	BOOL GetCustomFunction(LPCTSTR FuncName, short* MinArgs, short* MaxArgs, long* Flags);
	BOOL RemoveCustomFunction(LPCTSTR FuncName);
	BOOL ReCalcCell(long Col, long Row);
	void OLEDrag();
	void Refresh();
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPREADSHEET_H__3EEAA223_AAFE_11D3_9A2C_0050040A20EA__INCLUDED_)