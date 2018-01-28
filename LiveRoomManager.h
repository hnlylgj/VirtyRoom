#pragma once
#include "restfulqtcomcore1.h"
//#include "restfulqtcomcore1.h"
//#include "restfulqtcomcore12.h"


// LiveRoomManager 对话框

class LiveRoomManager : public CDialogEx
{
	DECLARE_DYNAMIC(LiveRoomManager)

public:
	LiveRoomManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LiveRoomManager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIVEROOMMANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CRestfulqtcomcore1 mLiveRoomManager;
	//CRestfulqtcomcore1 mLiveRoomManager;
	//CRestfulqtcomcore1 mLiveRoomMananger;
	CRestfulqtcomcore1 mLiveRoomManager;
};
