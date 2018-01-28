#pragma once
#include "LoginManager.h"
#include "LoginingMessageDlg.h"
#include "AccountManager.h"




// HomePageDlg 对话框

class HomePageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HomePageDlg)

public:
	HomePageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HomePageDlg();


    int mFlag;
	void FinallyFree();


	void AllShowFalg(int flag);


	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_HOMEPAGEDLG };
#endif

	enum { IDD = IDD_HOMEPAGEDLG };

protected:
	E_LoginState m_LoginState;
	UINT CountWait;
	LoginManager* pLoginManager;
	LoginingMessageDlg* pLoginingMessageDlg;
	CAccountManager* pAccountManager;
	

	int StartY,CountFlag;
	CHAR * pFlagChar;
	LPCSTR pUserName;
	LPCSTR pAppName;
	LPCSTR pDeveloperName;
	LPCSTR pCoprRightName;
	LPCSTR pUsableName;

	int mUserNameFontCout;
	int mAppNameFontCout;
	int mDeveloperNameFontCout;
	int mCoprRightNameFontCout;
	int mUsableNameFontCout;
	int mFlagCharFontCout;

	CSize mUserNameSize;
	CSize mAppNameSize;
	CSize mDeveloperNameSize;
	CSize mCoprRightNameSize;
	CSize mUsableNameSize;
	CSize mFlagCharSize;

	CMemBitmap m_MemBitmap;

public:
	void DoneClose();
	

	void LoginLiveRoom();
	//void InitiLiveSDK();

private:
	//static void OniLiveLoginSuccess(void* data);
	//static void OniLiveLoginError(int code, const std::string& desc, void* data);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
	afx_msg LRESULT LiveLoginHandler(WPARAM, LPARAM);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
