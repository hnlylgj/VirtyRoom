// WaitingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\VirtyRoom.h"
#include "WaitingDlg.h"
#include "afxdialogex.h"


// WaitingDlg �Ի���

IMPLEMENT_DYNAMIC(WaitingDlg, CDialogEx)

WaitingDlg::WaitingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WaitingDlg::IDD, pParent)
	, mWaitingTextString(_T(""))
{

}

WaitingDlg::~WaitingDlg()
{
}

void WaitingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WaitingText_STATIC, mWaitingTextString);
}


BEGIN_MESSAGE_MAP(WaitingDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// WaitingDlg ��Ϣ�������


void WaitingDlg::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect mClientRect;    
    GetClientRect(&mClientRect);    
	CDC   mMemDC;    
    mMemDC.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   mWaitingDlgBackground;    
    mWaitingDlgBackground.LoadBitmap(IDB_BITMAP2);  //�ȴ��Ի���ı���ͼƬ  
                        
    BITMAP   mbitmapInfor;    
    mWaitingDlgBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=mMemDC.SelectObject(&mWaitingDlgBackground);    
    mCurrentDC.StretchBlt(0,0,mClientRect.Width(),mClientRect.Height(),&mMemDC,0,0,    
    mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	mMemDC.DeleteDC();
	ReleaseDC(&mCurrentDC);

}
