#pragma once


// WaitingDlg �Ի���

class WaitingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WaitingDlg)

public:
	WaitingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WaitingDlg();

// �Ի�������
	enum { IDD = IDD_WaitingDlg_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CString mWaitingTextString;
};
