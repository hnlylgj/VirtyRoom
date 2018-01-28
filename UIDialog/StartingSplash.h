#pragma once
#include "MemBitmap.h"
//#include "..\UltrasoundBiopsy.h"
// StartingSplash �Ի���
#define IDD_Splash_DIALOG               316
class StartingSplash : public CDialogEx
{
	DECLARE_DYNAMIC(StartingSplash)

public:
	StartingSplash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~StartingSplash();

// �Ի�������
	enum { IDD = IDD_Splash_DIALOG };

protected:
	//--------------
	//CBitmap MyCBitmap;
	 int y;
	 CHAR * pFlagChar;
     LPCSTR pUserName;
	 LPCSTR pAppName;
	 LPCSTR pDeveloperName;
	 LPCSTR pCoprRightName;
	 LPCSTR pUsableName;

	 int mUserNameFontCout;
	 int mAppNameFontCout;
	 int mDeveloperNameFontCout;
	 int mCoprRightNameFontCout;
	 int mUsableNameFontCout;
	 int mFlagCharFontCout;

	 CSize mUserNameSize;
	 CSize mAppNameSize;
	 CSize mDeveloperNameSize;
	 CSize mCoprRightNameSize;
	 CSize mUsableNameSize;
	 CSize mFlagCharSize;




	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
    CMemBitmap m_MemBitmap;
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
