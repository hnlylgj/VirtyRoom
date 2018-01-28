
// 版权所有(C) Maxenmed Corporation
// 保留所有权利。

// UltrasoundBiopsy.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "VirtyRoom.h"
#include "MainFrm.h"

#include "VirtyRoomDoc.h"
#include "VirtyRoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CMainFrame* gpMainFrame;



// CVirtyRoomApp

BEGIN_MESSAGE_MAP(CVirtyRoomApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CVirtyRoomApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_APP_EXIT, &CVirtyRoomApp::OnAppExit)	
END_MESSAGE_MAP()


// CVirtyRoomApp 构造

CVirtyRoomApp::CVirtyRoomApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("hnlylgj-shuishuo.1.0.0.1"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	 mPUSGFW2ForMX=NULL;
	 mFlag = 0;
	 pUnkSinkLiveRoomHelper = NULL;

	 pAccountManager = NULL;

	 m_szUserToken = _T("0000000000");
	 m_szUserSig = _T("000000000000000000000000");
	 m_RoomID = _T("1008888");

	// piLiveSDK=NULL;

}

// 唯一的一个 CVirtyRoomApp 对象

CVirtyRoomApp theApp;


// CVirtyRoomApp 初始化

BOOL CVirtyRoomApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	
	//InitiLiveSDK();

	//--------------------
	//mHomePageDlg.DoModal();
	//if (this->mFlag != 100)
	//{
	
	//  return true;

	//}


	


	//mStartingSplashDlg.DoModal(); //启动客户单位画面
	//=============================================================================
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	//------已经完成COM库的初始化才能开始自定义初始化----------------
	
	mHomePageDlg.DoModal();
	if (this->mFlag != 100)
	{

		return true;

	}
	//-------------------------------------------
#ifdef VersionStud 
	//mAxStudMgrDlg.mAxStudMgrDlg.CopyParaTo(m_szUserId, m_szUserSig, m_szUserToken);
	INT_PTR nResponse = mAxStudMgrDlg.DoModal();
	if (nResponse == IDOK)
	{
	 //TODO: 在此放置处理 “确定”来关闭对话框的代码
    


	}
	else if (nResponse == IDCANCEL)
	{
	  // TODO: 在此放置处理何时用 “取消”来关闭对话框的代码
		return true;

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	
		return true;
	}
#endif


	InitiLiveSDK();
	
   

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	SetRegistryKey(_T("蔚来课堂教育科技有限公司"));
	LoadStdProfileSettings(2);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);


	
	//CAccountManager mCAccountManager;
	//m_pMainWnd = &mCAccountManager;
	

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVirtyRoomDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CVirtyRoomView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//mHomePageDlg.DoModal();
	//if (mFlag != 0)
	//{
	///	m_pMainWnd->SendMessage(WM_CLOSE);
	///	return true;
	//}
	//else
	//{

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	////m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->ShowWindow(SW_SHOW);//SW_HIDE SW_SHOWMINIMIZED SW_SHOW
	m_pMainWnd->UpdateWindow();


	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;

	
}

int CVirtyRoomApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	if(mPUSGFW2ForMX!=NULL)
	{
	 mPUSGFW2ForMX->DisconnectToDevice();
	 delete mPUSGFW2ForMX; 
	 mPUSGFW2ForMX = NULL;
     }

	
	if(pUnkSinkLiveRoomHelper !=NULL)
	{
		pUnkSinkLiveRoomHelper->CloseAllCall();
	    delete pUnkSinkLiveRoomHelper;
		pUnkSinkLiveRoomHelper = NULL;
     }

	if (pAccountManager != NULL)
	{
		pAccountManager->DestroyWindow();
		delete pAccountManager;
		pAccountManager = NULL;
	}
	
	return CWinAppEx::ExitInstance();
}

void CVirtyRoomApp::InitiLiveSDK()
 {

	pUnkSinkLiveRoomHelper = new CUnkSinkLiveRoomHelper();
	pUnkSinkLiveRoomHelper->InitCreateInstance();

	
	//m_nAppId = 1400019352;
	//m_nAccountType = 8970;

	//theApp.m_szUserId = "lgj1";
	//m_szUserToken = "bGdqMTE0OTExMzQ3MTIK";
	//m_szUserSig="eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//m_szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";
		
	// piLiveLoginMgr = iLiveLoginMgr::getInstance();
	// piLiveLoginMgr->setForceOfflineCallback(ilivemainwin::onForceOffline);

	
	/*
	piLiveRoomMgr = iLiveRoomMgr::getInstance();
	piLiveRoomMgr->setGroupMessageCallBack(ilivemainwin::OnGropuMessage);
	piLiveRoomMgr->setC2CMessageCallBack(ilivemainwin::OnC2CMessage);	

	piLiveRoomMgr->setLocalVideoCallBack(ilivemainwin::OnLocalVideo, this);
	piLiveRoomMgr->setRemoteVideoCallBack(ilivemainwin::OnRemoteVideo, this);
	
	piLiveSDK = iLiveSDK::getInstance();
	
	//lenght++;
	//CTime time; 
	//time= CTime::GetCurrentTime();
	theApp.m_RoomID=1000000+8888;

	int nRet = piLiveSDK->initSdk(theApp.m_nAppId, theApp.m_nAccountType);
	*/
	

 }



void CVirtyRoomApp::LoginLiveRoom()
{
	// TODO: 
	// m_szUserId = "lgj1";
	// std::string szUserId=CT2A(m_szUserId);
	//std::string szUserId = "lgj1";
	//std::string szUserId = "lgj2";
	// std::string  szUserSig = "eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//std::string  szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";
		
	///piLiveLoginMgr->iLiveLogin(szUserId, szUserSig, OniLiveLoginSuccess, OniLiveLoginError, this);
	
	pUnkSinkLiveRoomHelper->Login(m_szUserId, m_szPassWord);

}
/*
oid CVirtyRoomApp::OniLiveLoginSuccess(void* data)
{
// TODO:
//CVirtyRoomApp *pCVirtyRoomApp =reinterpret_cast<CVirtyRoomApp *>(data);
//theApp.mHomePageDlg.DoneClose();

//int nRet = 0;
//CString nRetStr;
//nRetStr.Format(TEXT("LoginSuccess:%d"), nRet

//pMainWin->m_wndOutput.PrintMessage(nRetStr);
//pMainWin->SendMessage(WM_LiveLogin,10,0);
//::SendMessage(pMainWin->m_hWnd,WM_LiveLogin,10,0);
//::PostMessage(pMainWin->m_hWnd,WM_LiveLogin,10,0);
// 显示消息对话框
//int nRes = pMainWin->MessageBox("LoginSuccess！","返回消息", MB_OKCANCEL | MB_ICONQUESTION);
//int nvalue=pMainWin->MessageBox("LoginSuccess！","返回消息",MB_ABORTRETRYIGNORE|MB_ICONERROR);

}

void CVirtyRoomApp::OniLiveLoginError(int code, const std::string& desc, void* data)
{
// TODO:
//CMainFrame *pMainWin = (CMainFrame *)data;//AfxGetMainWnd();

//CVirtyRoomApp *pCVirtyRoomApp =reinterpret_cast<CVirtyRoomApp *>(data);

//theApp.mHomePageDlg.PostMessage(WM_LiveLogin, 200,  code);//邮寄登录操作失败消息



//CString nRetStr;
//nRetStr.Format(TEXT("Login Error:%d"), nRet);
//theApp.mHomePageDlg.pLoginingMessageDlg->DoLoginUpdateUI(nRetStr);


//pMainWin->m_wndOutput.PrintMessage(nRetStr);
//pMainWin->SendMessage(WM_LiveLogin,10,1);
//::SendMessage(pMainWin->m_hWnd,WM_LiveLogin,10,code);
//::PostMessage(pMainWin->m_hWnd,WM_LiveLogin,10,code);
}

*/


// CVirtyRoomApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CVirtyRoomApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVirtyRoomApp 自定义加载/保存方法

void CVirtyRoomApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CVirtyRoomApp::LoadCustomState()
{
}

void CVirtyRoomApp::SaveCustomState()
{
}

// CVirtyRoomApp 消息处理程序

LRESULT  CVirtyRoomApp::LiveLoginHandler(WPARAM W, LPARAM L)
{

	//if (W = 1000)
	//{
//
	///	LoginLiveRoom();
	//}

	return 0;

}



void CVirtyRoomApp::OnAppExit()
{
	// TODO: 
	if(gpMainFrame->isCloseFlag!=100)
	{
		if(AfxMessageBox(_T("是否退出师说数字课堂?"),MB_YESNO)==IDYES)
		{
			//gpMainFrame->isCloseFlag=100;
			//gpMainFrame->SendMessage(WM_LiveRoom,100,0);
			gpMainFrame->SendMessage(WM_CLOSE);
		}
		else
		{
		
		}

	}
	else
	{

		gpMainFrame->SendMessage(WM_CLOSE);
	}
	   
}
