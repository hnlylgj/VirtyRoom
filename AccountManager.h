#pragma once
#include "restfulqtcomcore1.h"
#include "afxwin.h"


// CAccountManager 对话框

class CAccountManager : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountManager)

public:
	CAccountManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountManager();

	
	void Login(CString UserID, CString PassWord);
	void Loginout();

	void DoLoginUpdateUI(CString STR, UINT FLAG);
	void SetParentWnd(CWnd* pParent);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_ACCOUNTMANAGER };
#endif

	enum { IDD = IDD_ACCOUNTMANAGER };

	CWnd* pParentWnd;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRestfulqtcomcore1 mRestfulQtCOMCtrl;
	DECLARE_EVENTSINK_MAP()
	void OnCompleteEventRestfulqtcomcore1(long p_EventCode, long p_EventValue, LPCTSTR p_EventInfo);
	afx_msg void OnBnClickedOk();
	//CButton m_YesNo;
	virtual BOOL OnInitDialog();
};
