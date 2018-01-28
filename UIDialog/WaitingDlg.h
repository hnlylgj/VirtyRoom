#pragma once


// WaitingDlg 对话框

class WaitingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WaitingDlg)

public:
	WaitingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WaitingDlg();

// 对话框数据
	enum { IDD = IDD_WaitingDlg_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CString mWaitingTextString;
};
