#pragma once
#include "lgjrestfulaxqtstud1.h"


// AxStudMgrDlg �Ի���

class AxStudMgrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AxStudMgrDlg)

public:
	AxStudMgrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AxStudMgrDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_AXSTUDMGRDLG };
#endif

	enum { IDD = IDD_AXSTUDMGRDLG };
	CBrush m_brush;
	CFont m_Font;
	CWnd* pParentWnd;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CLgjrestfulaxqtstud1 mAxStudMgrDlg;
	DECLARE_EVENTSINK_MAP()
	void OnCompleteEventLgjrestfulaxqtstud1(long p_EventCode, long p_EventValue, LPCTSTR p_EventInfo);
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonCopyto();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
