// RestfulQtCoreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "RestfulQtCoreDlg.h"
#include "afxdialogex.h"


// RestfulQtCoreDlg �Ի���

IMPLEMENT_DYNAMIC(RestfulQtCoreDlg, CDialogEx)

RestfulQtCoreDlg::RestfulQtCoreDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RESTFULQTCOREDLG, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

RestfulQtCoreDlg::~RestfulQtCoreDlg()
{
}

void RestfulQtCoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RestfulQtCoreDlg, CDialogEx)
END_MESSAGE_MAP()


// RestfulQtCoreDlg ��Ϣ�������
