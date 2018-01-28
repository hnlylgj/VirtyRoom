
// ��Ȩ����(C) Maxenmed Corporation
// ��������Ȩ����

// UltrasoundBiopsy.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_APP_EXIT, &CVirtyRoomApp::OnAppExit)	
END_MESSAGE_MAP()


// CVirtyRoomApp ����

CVirtyRoomApp::CVirtyRoomApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("hnlylgj-shuishuo.1.0.0.1"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	 mPUSGFW2ForMX=NULL;
	 mFlag = 0;
	 pUnkSinkLiveRoomHelper = NULL;

	 pAccountManager = NULL;

	 m_szUserToken = _T("0000000000");
	 m_szUserSig = _T("000000000000000000000000");
	 m_RoomID = _T("1008888");

	// piLiveSDK=NULL;

}

// Ψһ��һ�� CVirtyRoomApp ����

CVirtyRoomApp theApp;


// CVirtyRoomApp ��ʼ��

BOOL CVirtyRoomApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	
	//InitiLiveSDK();

	//--------------------
	//mHomePageDlg.DoModal();
	//if (this->mFlag != 100)
	//{
	
	//  return true;

	//}


	


	//mStartingSplashDlg.DoModal(); //�����ͻ���λ����
	//=============================================================================
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	//------�Ѿ����COM��ĳ�ʼ�����ܿ�ʼ�Զ����ʼ��----------------
	
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
	 //TODO: �ڴ˷��ô��� ��ȷ�������رնԻ���Ĵ���
    


	}
	else if (nResponse == IDCANCEL)
	{
	  // TODO: �ڴ˷��ô����ʱ�� ��ȡ�������رնԻ���Ĵ���
		return true;

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	
		return true;
	}
#endif


	InitiLiveSDK();
	
   

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	SetRegistryKey(_T("ε�����ý����Ƽ����޹�˾"));
	LoadStdProfileSettings(2);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);


	
	//CAccountManager mCAccountManager;
	//m_pMainWnd = &mCAccountManager;
	

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVirtyRoomDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CVirtyRoomView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
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

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	////m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->ShowWindow(SW_SHOW);//SW_HIDE SW_SHOWMINIMIZED SW_SHOW
	m_pMainWnd->UpdateWindow();


	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;

	
}

int CVirtyRoomApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
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
// ��ʾ��Ϣ�Ի���
//int nRes = pMainWin->MessageBox("LoginSuccess��","������Ϣ", MB_OKCANCEL | MB_ICONQUESTION);
//int nvalue=pMainWin->MessageBox("LoginSuccess��","������Ϣ",MB_ABORTRETRYIGNORE|MB_ICONERROR);

}

void CVirtyRoomApp::OniLiveLoginError(int code, const std::string& desc, void* data)
{
// TODO:
//CMainFrame *pMainWin = (CMainFrame *)data;//AfxGetMainWnd();

//CVirtyRoomApp *pCVirtyRoomApp =reinterpret_cast<CVirtyRoomApp *>(data);

//theApp.mHomePageDlg.PostMessage(WM_LiveLogin, 200,  code);//�ʼĵ�¼����ʧ����Ϣ



//CString nRetStr;
//nRetStr.Format(TEXT("Login Error:%d"), nRet);
//theApp.mHomePageDlg.pLoginingMessageDlg->DoLoginUpdateUI(nRetStr);


//pMainWin->m_wndOutput.PrintMessage(nRetStr);
//pMainWin->SendMessage(WM_LiveLogin,10,1);
//::SendMessage(pMainWin->m_hWnd,WM_LiveLogin,10,code);
//::PostMessage(pMainWin->m_hWnd,WM_LiveLogin,10,code);
}

*/


// CVirtyRoomApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CVirtyRoomApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CVirtyRoomApp �Զ������/���淽��

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

// CVirtyRoomApp ��Ϣ�������

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
		if(AfxMessageBox(_T("�Ƿ��˳�ʦ˵���ֿ���?"),MB_YESNO)==IDYES)
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
