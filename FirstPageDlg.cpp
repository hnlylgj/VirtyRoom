// FirstPageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "FirstPageDlg.h"
#include "afxdialogex.h"


// FirstPageDlg �Ի���

IMPLEMENT_DYNAMIC(FirstPageDlg, CDialogEx)

FirstPageDlg::FirstPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIRSTPAGEDLG, pParent)
{

}

FirstPageDlg::~FirstPageDlg()
{
}

void FirstPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FirstPageDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL FirstPageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect mRect;
	GetClientRect(&mRect);

	ShowWindow(SW_SHOWMAXIMIZED); //ȫ����ʾ

	return TRUE;


}


// FirstPageDlg ��Ϣ�������


void FirstPageDlg::OnPaint()
{
	CPaintDC mCurrentDC(this);  
					   // TODO: �ڴ˴������Ϣ����������
					   // ����ͼ��Ϣ���� CDialogEx::OnPaint()

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
	//�¼ӵ����
	this->ReleaseDC(&mCurrentDC);

}
