// InitianlizingText.cpp : ʵ���ļ�
//

#include "..\stdafx.h"
#include "..\VirtyRoom.h"
#include "InitianlizingText.h"
#include "afxdialogex.h"


// InitianlizingText �Ի���

IMPLEMENT_DYNAMIC(InitianlizingText, CDialogEx)

InitianlizingText::InitianlizingText(CWnd* pParent /*=NULL*/)
	: CDialogEx(InitianlizingText::IDD, pParent)
{

}

InitianlizingText::~InitianlizingText()
{
}

void InitianlizingText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InitianlizingText, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// InitianlizingText ��Ϣ�������


void InitianlizingText::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//*
	CRect rect;    
    GetClientRect(&rect);    
	CDC   dcMem;    
    dcMem.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   bmpBackground;    
    bmpBackground.LoadBitmap(IDB_BITMAP2);  //��ʼ���Ի���ı���ͼƬ  
             
    BITMAP   mbitmapInfor;    
    bmpBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);    
    mCurrentDC.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,    
    mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	dcMem.DeleteDC(); 
	ReleaseDC(&mCurrentDC); 
	//*/


}
