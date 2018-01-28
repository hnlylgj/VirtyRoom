// HomePageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "HomePageDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
// HomePageDlg �Ի���

//HomePageDlg* gpHomePageDlg;
//extern CMainFrame* gpMainFrame;

IMPLEMENT_DYNAMIC(HomePageDlg, CDialogEx)

HomePageDlg::HomePageDlg(CWnd* pParent /*=NULL*/): CDialogEx(IDD_HOMEPAGEDLG, pParent)
{
	//gpHomePageDlg = this;
	mFlag=0;
	m_LoginState= E_InvalidState;
	CountWait=0;

	pAccountManager = NULL;
}

HomePageDlg::~HomePageDlg()
{
	pAccountManager = NULL;

}

void HomePageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HomePageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_MESSAGE(WM_LiveLogin, &HomePageDlg::LiveLoginHandler)
	ON_WM_TIMER()
END_MESSAGE_MAP()



void HomePageDlg::DoneClose()
{

	CDialogEx::OnOK();

}
/*


void HomePageDlg::OniLiveLoginSuccess(void* data)
{
	HomePageDlg *pHomePageDlg =reinterpret_cast<HomePageDlg *>(data);
	pHomePageDlg->DoneClose();




}
 void HomePageDlg::OniLiveLoginError(int code, const std::string& desc, void* data)
 {
	 HomePageDlg *pHomePageDlg =reinterpret_cast<HomePageDlg *>(data);

	 pHomePageDlg->PostMessage(WM_LiveLogin, 200,  code);//�ʼĵ�¼����ʧ����Ϣ


 }
 
 void HomePageDlg::InitiLiveSDK()
 {
	
	theApp.m_nAppId = 1400019352;
	theApp.m_nAccountType = 8970;

	theApp.m_szUserId = "lgj1";
	//m_szUserToken = "bGdqMTE0OTExMzQ3MTIK";
	//m_szUserSig="eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//m_szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";
		
	theApp.piLiveLoginMgr = iLiveLoginMgr::getInstance();
	theApp.piLiveLoginMgr->setForceOfflineCallback(ilivemainwin::onForceOffline);

	

	theApp.piLiveRoomMgr = iLiveRoomMgr::getInstance();
	theApp.piLiveRoomMgr->setGroupMessageCallBack(ilivemainwin::OnGropuMessage);
	theApp.piLiveRoomMgr->setC2CMessageCallBack(ilivemainwin::OnC2CMessage);	

	theApp.piLiveRoomMgr->setLocalVideoCallBack(ilivemainwin::OnLocalVideo, this);
	theApp.piLiveRoomMgr->setRemoteVideoCallBack(ilivemainwin::OnRemoteVideo, this);
	
	theApp.piLiveSDK = iLiveSDK::getInstance();
	
	//lenght++;
	//CTime time; 
	//time= CTime::GetCurrentTime();
	theApp.m_RoomID=1000000+8888;

	int nRet = theApp.piLiveSDK->initSdk(theApp.m_nAppId, theApp.m_nAccountType);

 }
 */
 void HomePageDlg::LoginLiveRoom()
 {
	// theApp.m_szUserId = "lgj1";
	 //std::string szUserId=CT2A(theApp.m_szUserId);
	//std::string szUserId = "lgj1";
	//std::string szUserId = "lgj2";
	// std::string  szUserSig = "eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//std::string  szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";
		
	//theApp.piLiveLoginMgr->iLiveLogin(szUserId, szUserSig, OniLiveLoginSuccess, OniLiveLoginError, this);



 }

// HomePageDlg ��Ϣ�������


void HomePageDlg::OnPaint()
{
	//CPaintDC mCurrentDC(this); 
	 // TODO: 
	/*
	CRect mClientRect;
	GetClientRect(&mClientRect);
	CDC   mMemDC;
	mMemDC.CreateCompatibleDC(&mCurrentDC);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP4);  //�Ի���ı���ͼƬ  

	BITMAP   mbitmapInfor;
	bmpBackground.GetBitmap(&mbitmapInfor);
	CBitmap   *pbmpOld = mMemDC.SelectObject(&bmpBackground);
	mCurrentDC.StretchBlt(0, 0, mClientRect.Width(), mClientRect.Height(), &mMemDC, 0, 0, mbitmapInfor.bmWidth, mbitmapInfor.bmHeight, SRCCOPY);
	
	mMemDC.DeleteDC();	
	this->ReleaseDC(&mCurrentDC);
	*/
	 //����ͼ��Ϣ���� 
	CDialogEx::OnPaint();
}


BOOL HomePageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//InitiLiveSDK();
	theApp.pUnkSinkLiveRoomHelper->SetHandleWindow(this->GetSafeHwnd());
	//pAccountManager = theApp.pAccountManager;
	//pAccountManager->SetParent(this);

	CRect mRect;
	GetClientRect(&mRect);
	StartY = mRect.Height()+500;
	CountFlag = StartY;
	int CharCount = 86;
	pFlagChar = new CHAR[CharCount];//�ָ��ַ���
	for (int i = 0; i<CharCount; i++)
	{
		pFlagChar[i] = '=';
	}
	pFlagChar[CharCount - 1] = '\0';
	//----------------------------------------------------------------
	pUserName = "�Ŵ��ɡ�ʦ˵���ֿ��á���������";
	pAppName = "||����||��ҵ||���|| ";
	pDeveloperName = "ʦ˵���ֿ��ÿƼ����޹�˾";
	pCoprRightName = "Version 1.0 Copyright@2017";
	pUsableName = "K12���ͽ�ѧϵͳ ������Դ��Զ����";
	//---------------------------------------------------------------
	mUserNameFontCout = 200;
	mAppNameFontCout = 250;
	mDeveloperNameFontCout = 180;
	mCoprRightNameFontCout = 120;
	mUsableNameFontCout = 180;
	mFlagCharFontCout = 80;
	//----------------------------------------------------------------

	CDC*  pDC = GetDC();
	CFont  NewOutTextFont;//�ı����������       
	CFont  *pOldFont;   //������ǰ������ָ�� 

	NewOutTextFont.CreatePointFont(mUserNameFontCout, _T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mUserNameSize = pDC->GetTextExtent((CString)pUserName);//����ַ�������


	NewOutTextFont.DeleteObject();
	NewOutTextFont.CreatePointFont(mAppNameFontCout, _T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mAppNameSize = pDC->GetTextExtent((CString)pAppName);//����ַ�������

	NewOutTextFont.DeleteObject();
	NewOutTextFont.CreatePointFont(mFlagCharFontCout, _T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mFlagCharSize = pDC->GetTextExtent((CString)pFlagChar);//����ַ�������


	NewOutTextFont.DeleteObject();
	NewOutTextFont.CreatePointFont(mDeveloperNameFontCout, _T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mDeveloperNameSize = pDC->GetTextExtent((CString)pDeveloperName);//����ַ�������

	NewOutTextFont.DeleteObject();
	NewOutTextFont.CreatePointFont(mCoprRightNameFontCout,_T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mCoprRightNameSize = pDC->GetTextExtent((CString)pCoprRightName);//����ַ�������

	NewOutTextFont.DeleteObject();
	NewOutTextFont.CreatePointFont(mUsableNameFontCout, _T("����"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//ѡ������Ҫ������ 
	mUsableNameSize = pDC->GetTextExtent((CString)pUsableName);//����ַ�������


	ShowWindow(SW_SHOWMAXIMIZED); //ȫ����ʾ
	m_MemBitmap.init(this);
	SetTimer(1, 20, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void HomePageDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	// TODO: �ڴ˴������Ϣ����������


}


void HomePageDlg::OnClose()
{
	// TODO: 

	//--Clear Resource--------------------------
	pLoginManager->DestroyWindow(); //CANCEL START SREEN;
	pLoginingMessageDlg->DestroyWindow();
	delete pLoginManager;
	delete pLoginingMessageDlg;

	pAccountManager->DestroyWindow();
	delete pAccountManager;

	KillTimer(1);

	CDialogEx::OnClose();
}


int HomePageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	pLoginManager = new LoginManager(this);
	pLoginManager->Create(LoginManager::IDD, this);
	CRect mLoginRect;
	pLoginManager->GetClientRect(&mLoginRect);
	
	int  nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int  nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	int XPostion = nFullWidth - mLoginRect.Width();
	int YPostion = 0;
	pLoginManager->SetWindowPos(NULL, XPostion, YPostion, mLoginRect.Width(), nFullHeight, SWP_NOZORDER);
	pLoginManager->ShowWindow(SW_SHOW);	
	pLoginManager->UpdateWindow();

	//-------------------------------------------------------------------------------pAccountManager
	pLoginingMessageDlg=new LoginingMessageDlg(this);
	pLoginingMessageDlg->Create(LoginingMessageDlg::IDD, this);
	CRect mLoginMessRect;
	pLoginingMessageDlg->GetClientRect(&mLoginMessRect);

	XPostion = 0;
	YPostion = nFullHeight - mLoginMessRect.Height();

	int cx = nFullWidth - mLoginRect.Width();
	int cy = mLoginMessRect.Height();
	//pLoginingMessageDlg->SetWindowPos(NULL, XPostion, YPostion, cx, cy, SWP_NOZORDER);

	//--------�ڳ�ʼ��-------------------------------------
	pAccountManager = new CAccountManager(this);
	pAccountManager->Create(CAccountManager::IDD, this);		
	
	CRect mzRect;
	pAccountManager->GetClientRect(&mzRect);

	XPostion = 0;
	YPostion = nFullHeight - mzRect.Height();

	cx = nFullWidth - mLoginRect.Width();
	cy = mzRect.Height();
	pAccountManager->SetWindowPos(NULL, XPostion, YPostion, cx, cy, SWP_NOZORDER);



	//pLoginingMessageDlg->ShowWindow(SW_SHOW);
	//pLoginingMessageDlg->UpdateWindow();

	return 0;
}


LRESULT HomePageDlg::LiveLoginHandler(WPARAM W, LPARAM L)
{
	//AfxMessageBox("Hello,World!");
	//CString nRetStr;
	//nRetStr.Format(TEXT("Login Status:%d,Code:%d"), W, L);
	//m_wndOutput.PrintMessage(nRetStr);

	if (W == RegistryManagerID)
	{


	}

	if (W == LoginManagerID)
	{
		if (L == 0)
		{
			//��¼�ɹ�
			theApp.mFlag = 100;//�˳�ϵͳ
			mFlag = 100;
			pAccountManager->ShowWindow(SW_HIDE);//SW_SHOW SW_HIDE
			pAccountManager->UpdateWindow();
			//this->SendMessage(WM_CLOSE);
			CDialogEx::OnOK();
		}
		if (L == 1)
		{
			//������¼�����ȴ�����
			CountWait = 0;
			m_LoginState = E_Logining;
			CString LoginStr;
			LoginStr.Format(TEXT("���ڵ�¼......�����ȣ�"));

			//pLoginingMessageDlg->DoLoginUpdateUI(LoginStr,0);
			//pLoginingMessageDlg->ShowWindow(SW_SHOW);
			//pLoginingMessageDlg->UpdateWindow();			
			
		
			pAccountManager->DoLoginUpdateUI(LoginStr, 0);
			pAccountManager->ShowWindow(SW_SHOW);//SW_SHOW SW_HIDE
			pAccountManager->UpdateWindow();
			pAccountManager->Login(theApp.m_szUserId, theApp.m_szPassWord);


		}

		if (L >1)
		{

			//��¼����ʧ����Ϣ
			m_LoginState = E_Logout;
			CountWait = 0;
			//CString nRetStr;
			//nRetStr.Format(TEXT("Login Error:%d"), L);
			//pLoginingMessageDlg->DoLoginUpdateUI(nRetStr,L);
			//pLoginingMessageDlg->ShowWindow(SW_SHOW);
			//pLoginingMessageDlg->UpdateWindow();

			//pAccountManager->DoLoginUpdateUI(nRetStr, L);
			//pAccountManager->ShowWindow(SW_SHOW);
			//pAccountManager->UpdateWindow();

		}
	}


	  if (W == LogoutManagerID)
		{
		  if (L == 0)
		  {
			  theApp.mFlag = 1;//ֱ���˳�ϵͳ
			  mFlag = 1;
			  CDialogEx::OnOK();
		  }
		  else
		  {



		  }
			
		
		

		}
	  

	
		

	return 0;
}

void HomePageDlg::AllShowFalg(int flag)
{
	if (flag == 0)
	{


		pLoginManager->ShowWindow(SW_SHOW);
		pLoginManager->UpdateWindow();
		pLoginingMessageDlg->ShowWindow(SW_SHOW);
		pLoginingMessageDlg->UpdateWindow();
		this->ShowWindow(SW_SHOW);
		this->UpdateWindow();
	
	}
	else
	{

		
		pLoginManager->ShowWindow(SW_HIDE);
		pLoginManager->UpdateWindow();
		pLoginingMessageDlg->ShowWindow(SW_HIDE);
		pLoginingMessageDlg->UpdateWindow();
		this->ShowWindow(SW_HIDE);
		this->UpdateWindow();

	}


}

void HomePageDlg::FinallyFree()
{

	this->SendMessage(WM_CLOSE);

}


void HomePageDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 
	CRect   mRect;
	CDC*    pDC = GetDC();
	CDC     mDC;
	this->GetClientRect(&mRect);
	LONG mOutTextPointX;
	//mOutTextPointX=(int)(mRect.Width()/2);
	mOutTextPointX = mRect.Width();
	
	StartY--;
	m_MemBitmap.Clear(mRect.left, mRect.top, mRect.right, mRect.bottom, RGB(00, 00, 00)); //��׼��:00, 00, 00�����128,138,135--������41,36,33-�غ�ɫ��RGBֵ94 38 18--69, 33,21

	LONG OutTextPosionX, OutTextPosionY, mDistanceValue;
	OutTextPosionX = (mOutTextPointX - mUserNameSize.cx) / 2;
	mDistanceValue = 0;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y*/, mUserNameFontCout, pUserName, RGB(0, 250, 0)); //1

	OutTextPosionX = (mOutTextPointX - mAppNameSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy - 20;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+60*/, mAppNameFontCout, pAppName, RGB(0, 250, 0)); //2

	OutTextPosionX = (mOutTextPointX - mFlagCharSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy + mFlagCharSize.cy + 30;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+130*/, mFlagCharFontCout, pFlagChar, RGB(0, 250, 0));//3

	OutTextPosionX = (mOutTextPointX - mDeveloperNameSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy + mFlagCharSize.cy + mDeveloperNameSize.cy + 30;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+180*/, mDeveloperNameFontCout, pDeveloperName, RGB(255, 0, 0)); //4

	OutTextPosionX = (mOutTextPointX - mCoprRightNameSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy + mFlagCharSize.cy + mDeveloperNameSize.cy + mCoprRightNameSize.cy + 50;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+240*/, mCoprRightNameFontCout, pCoprRightName, RGB(255, 0, 0)); //5

	OutTextPosionX = (mOutTextPointX - mFlagCharSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy + mFlagCharSize.cy + mDeveloperNameSize.cy + mCoprRightNameSize.cy + mFlagCharSize.cy + 70;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+300*/, mFlagCharFontCout, pFlagChar, RGB(0, 250, 0));//6

	OutTextPosionX = (mOutTextPointX - mUsableNameSize.cx) / 2;
	mDistanceValue = mUserNameSize.cy + mAppNameSize.cy + mFlagCharSize.cy + mDeveloperNameSize.cy + mCoprRightNameSize.cy + mFlagCharSize.cy + mUsableNameSize.cy + 70;
	OutTextPosionY = (LONG)StartY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY/*y+340*/, mUsableNameFontCout, pUsableName, RGB(0, 250, 0));//7
													
																															 
																															 
	mDC.CreateCompatibleDC(pDC);
	mDC.SelectObject(&m_MemBitmap);  //�ڴ��豸������λͼ����ѡ�� 
	pDC->BitBlt(0, 0, mRect.Width(), mRect.Height(), &mDC, 0, 0, SRCCOPY); //��λ���亯����ʾ����
	mDC.DeleteDC();
	ReleaseDC(pDC); //��ǰ����-�ͷ��豸����


	if (StartY <= -280)//-180
	{
		//KillTimer(1);
		//CDialogEx::OnCancel(); //������ʾ����˳���
		StartY=CountFlag;//ѭ����ʾ
	}

	//-----���� 1---------------------
	if(m_LoginState==E_Logout)
	{
			CountWait++;
			if(	CountWait>200)
			{
			// pLoginingMessageDlg->ShowWindow(SW_HIDE);
	        // pLoginingMessageDlg->UpdateWindow();


			 pAccountManager->ShowWindow(SW_HIDE); //SW_HIDE SW_SHOW
			 pAccountManager->UpdateWindow();

			}


	}
	//------Test 2-------------------------------
	if (m_LoginState == E_Logining)
	{
		//CountWait++;
		//if (CountWait>100)
		//{
			//pLoginManager->ShowWindow(SW_HIDE);
			//pAccountManager->ShowWindow(SW_HIDE);
			//pAccountManager->UpdateWindow();

			//pLoginingMessageDlg->UpdateWindow();
			//this->SendMessage(WM_CLOSE);
			//theApp.mFlag = 100;//ģ��ɹ���¼״̬����ϵͳ
			//CDialogEx::OnOK();
		//}


	}



	CDialogEx::OnTimer(nIDEvent);
}
