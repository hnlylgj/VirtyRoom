#pragma once


// InitianlizingText �Ի���

class InitianlizingText : public CDialogEx
{
	DECLARE_DYNAMIC(InitianlizingText)

public:
	InitianlizingText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InitianlizingText();

// �Ի�������
	enum { IDD = IDD_initializing_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
