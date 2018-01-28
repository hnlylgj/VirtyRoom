#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CRestfulqtcomcore1 包装器类

class CRestfulqtcomcore1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CRestfulqtcomcore1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x217C4B43, 0xF28A, 0x4D8C, { 0xA2, 0xFC, 0x34, 0x93, 0xBB, 0xE0, 0x32, 0xE2 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    ArrowCursor = 0,
    UpArrowCursor = 1,
    CrossCursor = 2,
    WaitCursor = 3,
    IBeamCursor = 4,
    SizeVerCursor = 5,
    SizeHorCursor = 6,
    SizeBDiagCursor = 7,
    SizeFDiagCursor = 8,
    SizeAllCursor = 9,
    BlankCursor = 10,
    SplitVCursor = 11,
    SplitHCursor = 12,
    PointingHandCursor = 13,
    ForbiddenCursor = 14,
    WhatsThisCursor = 15,
    BusyCursor = 16
}MousePointer;
enum
{
    NoFocus = 0,
    TabFocus = 1,
    ClickFocus = 2,
    StrongFocus = 11,
    WheelFocus = 15
}FocusPolicy;


// 操作
public:

// IRestfulQtComCore

// Functions
//

	void setEnabled(BOOL p0)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p0);
	}
	void setDisabled(BOOL p0)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p0);
	}
	void setWindowModified(BOOL p0)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p0);
	}
	void setWindowTitle(LPCTSTR p0)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p0);
	}
	void setStyleSheet(LPCTSTR p_styleSheet)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_styleSheet);
	}
	void setFocus()
	{
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void setVisible(BOOL p_visible)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_visible);
	}
	void show()
	{
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void hide()
	{
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL close()
	{
		BOOL result;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void raise()
	{
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void lower()
	{
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH grab(VARIANT p_rectangle)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &p_rectangle);
		return result;
	}
	void Registry(LPCTSTR p_UserID, LPCTSTR p_UserPass)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_UserID, p_UserPass);
	}
	void Login(LPCTSTR p_UserID, LPCTSTR p_UserPass)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_UserID, p_UserPass);
	}
	void Loginout()
	{
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void getTokenID()
	{
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void getUserSig()
	{
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyParaTo(LPCTSTR p_UserID, LPCTSTR p_UserSig, LPCTSTR p_UserToken)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_UserID, p_UserSig, p_UserToken);
	}
	void MasterPlanSpace()
	{
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MasterGetSpace()
	{
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MasterCreateRoom()
	{
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MasterJoinRoom(long p_mUserType)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_mUserType);
	}
	void MasterReportRoom(LPCTSTR p_RoomTitle)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_RoomTitle);
	}
	void MasterKeepLive(long p_mthumbup)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms, p_mthumbup);
	}
	void MasterQuitRoom()
	{
		InvokeHelper(0x41, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

BOOL Getmodal()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}
void Setmodal(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}
BOOL Getenabled()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}
void Setenabled(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}
QRect GetnormalGeometry()
{
	QRect result;
	GetProperty(0x4, VT_EMPTY, (void*)&result);
	return result;
}
void SetnormalGeometry(QRect propVal)
{
	SetProperty(0x4, VT_EMPTY, propVal);
}
int Getx()
{
	int result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}
void Setx(int propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}
int Gety()
{
	int result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}
void Sety(int propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}
int Getwidth()
{
	int result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}
void Setwidth(int propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}
int Getheight()
{
	int result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void Setheight(int propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}
int GetminimumWidth()
{
	int result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetminimumWidth(int propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
int GetminimumHeight()
{
	int result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetminimumHeight(int propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
int GetmaximumWidth()
{
	int result;
	GetProperty(0xc, VT_I4, (void*)&result);
	return result;
}
void SetmaximumWidth(int propVal)
{
	SetProperty(0xc, VT_I4, propVal);
}
int GetmaximumHeight()
{
	int result;
	GetProperty(0xd, VT_I4, (void*)&result);
	return result;
}
void SetmaximumHeight(int propVal)
{
	SetProperty(0xd, VT_I4, propVal);
}
IFontDisp * Getfont()
{
	IFontDisp * result;
	GetProperty(0xf, VT_DISPATCH, (void*)&result);
	return result;
}
void Setfont(IFontDisp * propVal)
{
	SetProperty(0xf, VT_DISPATCH, propVal);
}
long Getcursor()
{
	long result;
	GetProperty(0x10, VT_I4, (void*)&result);
	return result;
}
void Setcursor(long propVal)
{
	SetProperty(0x10, VT_I4, propVal);
}
BOOL GetmouseTracking()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}
void SetmouseTracking(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}
long GetFocusPolicy()
{
	long result;
	GetProperty(0x12, VT_I4, (void*)&result);
	return result;
}
void SetFocusPolicy(long propVal)
{
	SetProperty(0x12, VT_I4, propVal);
}
BOOL GetupdatesEnabled()
{
	BOOL result;
	GetProperty(0x14, VT_BOOL, (void*)&result);
	return result;
}
void SetupdatesEnabled(BOOL propVal)
{
	SetProperty(0x14, VT_BOOL, propVal);
}
BOOL Getmaximized()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}
void Setmaximized(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}
BOOL GetfullScreen()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}
void SetfullScreen(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}
BOOL GetacceptDrops()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}
void SetacceptDrops(BOOL propVal)
{
	SetProperty(0x17, VT_BOOL, propVal);
}
CString GetwindowTitle()
{
	CString result;
	GetProperty(0x18, VT_BSTR, (void*)&result);
	return result;
}
void SetwindowTitle(CString propVal)
{
	SetProperty(0x18, VT_BSTR, propVal);
}
CString GetwindowIconText()
{
	CString result;
	GetProperty(0x1a, VT_BSTR, (void*)&result);
	return result;
}
void SetwindowIconText(CString propVal)
{
	SetProperty(0x1a, VT_BSTR, propVal);
}
BOOL GetwindowModified()
{
	BOOL result;
	GetProperty(0x1b, VT_BOOL, (void*)&result);
	return result;
}
void SetwindowModified(BOOL propVal)
{
	SetProperty(0x1b, VT_BOOL, propVal);
}
CString GettoolTip()
{
	CString result;
	GetProperty(0x1c, VT_BSTR, (void*)&result);
	return result;
}
void SettoolTip(CString propVal)
{
	SetProperty(0x1c, VT_BSTR, propVal);
}
int GettoolTipDuration()
{
	int result;
	GetProperty(0x1d, VT_I4, (void*)&result);
	return result;
}
void SettoolTipDuration(int propVal)
{
	SetProperty(0x1d, VT_I4, propVal);
}
CString GetstatusTip()
{
	CString result;
	GetProperty(0x1e, VT_BSTR, (void*)&result);
	return result;
}
void SetstatusTip(CString propVal)
{
	SetProperty(0x1e, VT_BSTR, propVal);
}
CString GetwhatsThis()
{
	CString result;
	GetProperty(0x1f, VT_BSTR, (void*)&result);
	return result;
}
void SetwhatsThis(CString propVal)
{
	SetProperty(0x1f, VT_BSTR, propVal);
}
CString GetaccessibleName()
{
	CString result;
	GetProperty(0x20, VT_BSTR, (void*)&result);
	return result;
}
void SetaccessibleName(CString propVal)
{
	SetProperty(0x20, VT_BSTR, propVal);
}
CString GetaccessibleDescription()
{
	CString result;
	GetProperty(0x21, VT_BSTR, (void*)&result);
	return result;
}
void SetaccessibleDescription(CString propVal)
{
	SetProperty(0x21, VT_BSTR, propVal);
}
BOOL GetautoFillBackground()
{
	BOOL result;
	GetProperty(0x23, VT_BOOL, (void*)&result);
	return result;
}
void SetautoFillBackground(BOOL propVal)
{
	SetProperty(0x23, VT_BOOL, propVal);
}
CString GetstyleSheet()
{
	CString result;
	GetProperty(0x24, VT_BSTR, (void*)&result);
	return result;
}
void SetstyleSheet(CString propVal)
{
	SetProperty(0x24, VT_BSTR, propVal);
}
CString GetwindowFilePath()
{
	CString result;
	GetProperty(0x26, VT_BSTR, (void*)&result);
	return result;
}
void SetwindowFilePath(CString propVal)
{
	SetProperty(0x26, VT_BSTR, propVal);
}


};
