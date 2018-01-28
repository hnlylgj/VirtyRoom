#pragma once
#include "afxwin.h"


// LoginManager �Ի���

class LoginManager : public CDialogEx
{
	DECLARE_DYNAMIC(LoginManager)

public:
	LoginManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginManager();

protected:
	//��������
	COLORREF m_ViewBackgroundColor;

// �Ի�������
//#ifdef AFX_DESIGN_TIME

public:
	enum { IDD = IDD_LOGINMANAGER };
	CBrush m_brush; CFont m_Font;
	CEdit m_AccountID;
	CEdit m_PassWord;

	CWnd* pParentWnd;


//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
};
