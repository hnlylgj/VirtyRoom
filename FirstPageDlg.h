#pragma once


// FirstPageDlg �Ի���

class FirstPageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FirstPageDlg)

public:
	FirstPageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FirstPageDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTPAGEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
