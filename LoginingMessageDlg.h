#pragma once
#include "afxwin.h"


// LoginingMessageDlg 对话框

class LoginingMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginingMessageDlg)

public:
	LoginingMessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginingMessageDlg();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LoginWaiting };
//#endif

	CBrush m_brush; CFont m_Font;

	CWnd* pParentWnd;

	void DoLoginUpdateUI(CString STR,UINT FLAG);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//CButton m_YesNo;
};
