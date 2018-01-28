#pragma once


// FirstPageDlg 对话框

class FirstPageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FirstPageDlg)

public:
	FirstPageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FirstPageDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTPAGEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
