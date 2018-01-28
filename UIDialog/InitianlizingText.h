#pragma once


// InitianlizingText 对话框

class InitianlizingText : public CDialogEx
{
	DECLARE_DYNAMIC(InitianlizingText)

public:
	InitianlizingText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InitianlizingText();

// 对话框数据
	enum { IDD = IDD_initializing_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
