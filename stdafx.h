
// 版权所有(C) Maxenmed Corporation
// 保留所有权利。

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
//-------我的定义------------------------------------------------------


#define VersionStudX

#define RegistryManagerID 10000
#define LoginManagerID 10001
#define LogoutManagerID 10002

#define MasterCreateRoomID 10003
#define MasterReportRoomID 10004
#define MasterJoinRoomID 10005

#define MasterKeepLiveID 10006
#define MasterQuitRoomID 10007


#define SlaverGetRoomListID 10010
#define SlaverJoinRoomID 10011
#define SlaverQuitRoomID 10012
#define SlaverQuitRoomListID 10013

//---------------------------------------------

#define LoginLiveRoomID 1000
#define LogoutLiveRoomID 1001

#define MasterCreateLiveRoomID 1002
#define MasterCloseLiveRoomID 1003
#define MasterQuitLiveRoomID 1004


#define  SlaverJoinLiveRoomID 1005
#define  SlaverQuitLiveRoomID 1006


#define MasterCustIMID 1010 //1003
#define SlaverCustIMID 1011

#define RoomDisconnectID 2000
#define GropuMessageID 2001
#define C2CMessageID 2002
#define ForceOfflineID 2003

#define LocalVideoID 2004
#define RemoteVideoID 2005



#define RoomDynamicID 3001
#define SemiAutoRecvCameraVideoID 3002
#define SemiAutoRecvScreenVideoID 3003
#define SemiAutoRecvMediaFileVideoID 3004



struct QRect 
{
	int left;
	int top;
	int right;
	int bottom;
};
struct QSize 
{
	int width;
	int height;
};
struct QPoint
{
	int x;
	int y;
};


enum E_LoginState
{
	E_InvalidState = -1,
	E_Logout,
	E_Logining,
	E_Login,
};
//---------------------------------------------------------
#pragma comment(lib, "vfw32.lib")
/*
#include <ilivesdk/iLiveSDK.h>
#include <ilivesdk/iLiveLog.h>
#include <ilivesdk/iLiveLoginMgr.h>
#include <ilivesdk/iLiveRoomMgr.h>

//#include "MainFrm.h"

#pragma comment(lib, "ilivesdk.lib")

using namespace imcore;
using namespace tencent::av;
using namespace ilivesdk;
*/


#define WM_LiveLogin WM_USER+100
#define WM_LiveRoom  WM_USER+101
#define WM_MYMSG WM_USER+102
#define WM_SERVERDATACHANGE  WM_USER+999
#define WM_EXTRADATACHANGE  WM_USER+1000


#define LiveMaster	"LiveMaster" //主播
#define LiveGuest	"LiveGuest"  //连麦观众
#define Guest		"Guest"		 //观众

//-----------------------------------------------------

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


