#pragma once
#include "restfulqtcomcore1.h"
//#include "restfulqtcomcore1.h"
//#include "restfulqtcomcore12.h"


// LiveRoomManager �Ի���

class LiveRoomManager : public CDialogEx
{
	DECLARE_DYNAMIC(LiveRoomManager)

public:
	LiveRoomManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LiveRoomManager();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIVEROOMMANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CRestfulqtcomcore1 mLiveRoomManager;
	//CRestfulqtcomcore1 mLiveRoomManager;
	//CRestfulqtcomcore1 mLiveRoomMananger;
	CRestfulqtcomcore1 mLiveRoomManager;
};
