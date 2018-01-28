// AccountManager.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "AccountManager.h"
#include "afxdialogex.h"

//extern HomePageDlg* gpHomePageDlg;
// CAccountManager 对话框

IMPLEMENT_DYNAMIC(CAccountManager, CDialogEx)

CAccountManager::CAccountManager(CWnd* pParent ): CDialogEx(IDD_ACCOUNTMANAGER, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	pParentWnd = pParent;




}

CAccountManager::~CAccountManager()
{
}

void CAccountManager::Login(CString UserID, CString PassWord)
{

	mRestfulQtCOMCtrl.Login((LPCTSTR)UserID, (LPCTSTR)PassWord);


}

void CAccountManager::Loginout()
{

	mRestfulQtCOMCtrl.Loginout();

	//this->setp
	//mRestfulQtCOMCtrl.CRE

}

void CAccountManager::SetParentWnd(CWnd* pParent)
{

	pParentWnd = pParent;
}

void CAccountManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESTFULQTCOMCORE1, mRestfulQtCOMCtrl);
	//DDX_Control(pDX, IDOK, m_YesNo);
}


BEGIN_MESSAGE_MAP(CAccountManager, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAccountManager::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccountManager 消息处理程序
BEGIN_EVENTSINK_MAP(CAccountManager, CDialogEx)
	ON_EVENT(CAccountManager, IDC_RESTFULQTCOMCORE1, 8, CAccountManager::OnCompleteEventRestfulqtcomcore1, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()


void CAccountManager::OnCompleteEventRestfulqtcomcore1(long p_EventCode, long p_EventValue, LPCTSTR p_EventInfo)
{
	// TODO: pAccountManager->DoLoginUpdateUI(LoginStr,0);
	CString nRetStr;
	if(p_EventCode== LoginManagerID && p_EventValue == 0)
	nRetStr.Format(TEXT("%s"),  p_EventInfo);
	else
	nRetStr.Format(TEXT("EventCode:%d;EventValue:%d;%s"), p_EventCode, p_EventValue, p_EventInfo);

	CStatic* pUiCtrl;
	pUiCtrl = (CStatic*)GetDlgItem(IDC_STATIC_LoginingMessage);
	pUiCtrl->SetWindowText(nRetStr);

	CButton* pYesNo;
	pYesNo= (CButton*)GetDlgItem(IDOK);
	if ((p_EventCode == LoginManagerID) && p_EventValue == 0)
	{
		
		//pYesNo->ShowWindow(SW_NORMAL);
		//theApp.m_szUserToken
		//BSTR UserToken(_T(" "));
		//BSTR UserSig(_T(" "));
		//mRestfulQtCOMCtrl.getTokenID(&UserToken);
		//mRestfulQtCOMCtrl.getUserSig(&UserSig);
		CString AllStrMessage;
		AllStrMessage.Format(TEXT("%s"), p_EventInfo);
		//AllStrMessage.replace()
		//CString MyUserSig, UserToken;
		int nIndex = AllStrMessage.Find(_T("\n"), 0);		
		theApp.m_szUserToken = AllStrMessage.Left(nIndex);
		theApp.m_szUserSig = AllStrMessage.Mid(nIndex + 1);

		//OnBnClickedOk();
		//pParentWnd->PostMessage(WM_LiveLogin, 1000, 0);//成功；
	}
	if ((p_EventCode == MasterCreateRoomID) && p_EventValue == 0)
	{
		
		CString AllStrMessage;
		AllStrMessage.Format(TEXT("%s"), p_EventInfo);
		theApp.m_RoomID = AllStrMessage;
		

		//OnBnClickedOk();
		//pParentWnd->PostMessage(WM_LiveLogin, 1000, 0);//成功；
	}

	if ((p_EventCode == RegistryManagerID) && p_EventValue == 0)
	{
		



	}




	else
	{
		//theApp.m_szUserToken = _T("0000000000");
		//theApp.m_szUserSig = _T("000000000000000000000000");

		//BSTR UserToken(_T(" "));
		//BSTR UserSig(_T(" "));

		/*
		
		_bstr_t UserToken(""); // ::SysAllocString(L"lgj1lgj1lgj1lgj");
		_bstr_t UserSig("");//

		mRestfulQtCOMCtrl.getTokenID((BSTR*)&UserToken);
		mRestfulQtCOMCtrl.getUserSig((BSTR*)&UserSig);

		CString MyUserToken((BSTR)UserToken);
		CString MyUserSig((BSTR)UserSig);

		theApp.m_szUserToken = MyUserToken;
		theApp.m_szUserSig = MyUserSig;

		//pYesNo->ShowWindow(SW_NORMAL);
		//pYesNo->ShowWindow(SW_HIDE);
		//pParentWnd->PostMessage(WM_LiveLogin, 1000, 300);//失败；
		*/

	}

	
	pParentWnd->PostMessage(WM_LiveLogin, p_EventCode, p_EventValue);







}
void CAccountManager::DoLoginUpdateUI(CString STR, UINT FLAG)
{

	CStatic* pUiCtrl;
	pUiCtrl = (CStatic*)GetDlgItem(IDC_STATIC_LoginingMessage);
	pUiCtrl->SetWindowText(STR);

	//if (FLAG > 0)
		//m_YesNo.ShowWindow(SW_NORMAL);
	//else
		//m_YesNo.ShowWindow(SW_HIDE);//SW_HIDE



}

void CAccountManager::OnBnClickedOk(){
	// TODO: 
	pParentWnd->PostMessage(WM_LiveLogin, 10001, 0);//模拟成功；
	//CDialogEx::OnOK();
}


BOOL CAccountManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  
	//pParentWnd = this->GetParent();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
