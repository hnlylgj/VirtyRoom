// LiveRoomManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "LiveRoomManager.h"
#include "afxdialogex.h"


// LiveRoomManager �Ի���

IMPLEMENT_DYNAMIC(LiveRoomManager, CDialogEx)

LiveRoomManager::LiveRoomManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIVEROOMMANAGER, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

LiveRoomManager::~LiveRoomManager()
{
}

void LiveRoomManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_RESTFULQTCOMCORE1, mLiveRoomManager);
	//DDX_Control(pDX, IDC_RESTFULQTCOMCORE1, mLiveRoomManager);
	//DDX_Control(pDX, IDC_RESTFULQTCOMCORE1, mLiveRoomMananger);
	DDX_Control(pDX, IDC_RESTFULQTCOMCORE1, mLiveRoomManager);
}


BEGIN_MESSAGE_MAP(LiveRoomManager, CDialogEx)
END_MESSAGE_MAP()


// LiveRoomManager ��Ϣ�������
