// AxStudMgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "AxStudMgrDlg.h"
#include "afxdialogex.h"


// AxStudMgrDlg 对话框

IMPLEMENT_DYNAMIC(AxStudMgrDlg, CDialogEx)

AxStudMgrDlg::AxStudMgrDlg(CWnd* pParent /*=NULL*/)	: CDialogEx(IDD_AXSTUDMGRDLG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	pParentWnd = pParent;

}

AxStudMgrDlg::~AxStudMgrDlg()
{
}

void AxStudMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LGJRESTFULAXQTSTUD1, mAxStudMgrDlg);
}


BEGIN_MESSAGE_MAP(AxStudMgrDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Login, &AxStudMgrDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CopyTo, &AxStudMgrDlg::OnBnClickedButtonCopyto)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// AxStudMgrDlg 消息处理程序
BEGIN_EVENTSINK_MAP(AxStudMgrDlg, CDialogEx)
	ON_EVENT(AxStudMgrDlg, IDC_LGJRESTFULAXQTSTUD1, 8, AxStudMgrDlg::OnCompleteEventLgjrestfulaxqtstud1, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()


void AxStudMgrDlg::OnCompleteEventLgjrestfulaxqtstud1(long p_EventCode, long p_EventValue, LPCTSTR p_EventInfo)
{
	// TODO: 
	if ((p_EventCode == LoginManagerID) && p_EventValue == 0)
	{

		CString AllStrMessage;
		AllStrMessage.Format(TEXT("%s"), p_EventInfo);
		//AllStrMessage.replace()
		//CString MyUserSig, UserToken;
		int nIndex = AllStrMessage.Find(_T("\n"), 0);
		CString m_szUserToken = AllStrMessage.Left(nIndex);
		CString m_szUserSig = AllStrMessage.Mid(nIndex + 1);

		CStatic* pUiCtrl;
		pUiCtrl = (CStatic*)GetDlgItem(IDC_STATIC_LoginingMessage);
		pUiCtrl->SetWindowText(m_szUserToken);
	}
	else
	{
		CString nRetStr;
		nRetStr.Format(TEXT("EventCode:%d;EventValue:%d;%s"), p_EventCode, p_EventValue, p_EventInfo);
		CStatic* pUiCtrl;
		pUiCtrl = (CStatic*)GetDlgItem(IDC_STATIC_LoginingMessage);
		pUiCtrl->SetWindowText(nRetStr);

	}

	if(pParentWnd!=NULL)
	pParentWnd->PostMessage(WM_LiveLogin, p_EventCode, p_EventValue);

	if ((p_EventCode == SlaverGetRoomListID) && p_EventValue ==2)
	{


		CString AllStrMessage;
		AllStrMessage.Format(TEXT("%s"), p_EventInfo);
		theApp.m_RoomID = AllStrMessage;

		CDialogEx::OnOK();

	}




	if ((p_EventCode == SlaverQuitRoomListID) && p_EventValue == 0)
	{


		//CDialogEx::OnOK();
		CDialogEx::OnCancel();

	}


}


void AxStudMgrDlg::OnBnClickedButtonLogin()
{
	// TODO: 
	CString userid = _T("lgj2");
	mAxStudMgrDlg.Login(_T("lgj2"), _T("123456"));


}


void AxStudMgrDlg::OnBnClickedButtonCopyto()
{
	// TODO: 
	mAxStudMgrDlg.CopyParaTo(theApp.m_szUserId, theApp.m_szUserSig, theApp.m_szUserToken);

}


BOOL AxStudMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 
	m_brush.CreateSolidBrush(RGB(49, 69, 100)); // 生成一刷子：RGB(49, 69, 100)0, 255, 0

	OnBnClickedButtonCopyto();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void AxStudMgrDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:
	mAxStudMgrDlg.GetRooomList(0, 0, 0);

}


HBRUSH AxStudMgrDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (nCtlColor == CTLCOLOR_DLG)//对话框颜色  
		return m_brush;//返会自定义刷子 


	if (nCtlColor == CTLCOLOR_STATIC)//静态文本颜色  
	{
		//pDC->SetTextColor(RGB(255, 0, 0));
		//->SetBkColor(RGB(191, 219, 255));//静态控件的背景颜色设置，这里设置于背景颜色一致，则可以免设置透明  
		pDC->SetBkMode(TRANSPARENT);//模式设置透明的话，则忽略静态控件的背景颜色设置，与对话框颜色融合  
		hbr = (HBRUSH)m_brush;
	}


	

	return hbr;
}
