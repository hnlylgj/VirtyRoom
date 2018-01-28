#pragma once
#include "afxwin.h"


// LoginManager 对话框

class LoginManager : public CDialogEx
{
	DECLARE_DYNAMIC(LoginManager)

public:
	LoginManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginManager();

protected:
	//变量定义
	COLORREF m_ViewBackgroundColor;

// 对话框数据
//#ifdef AFX_DESIGN_TIME

public:
	enum { IDD = IDD_LOGINMANAGER };
	CBrush m_brush; CFont m_Font;
	CEdit m_AccountID;
	CEdit m_PassWord;

	CWnd* pParentWnd;


//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
};
