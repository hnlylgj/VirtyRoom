#pragma once
//#include <vfw.h>


// CMModeCtrlFormVIEW ������ͼ

class CMModeCtrlFormVIEW : public CFormView
{
	DECLARE_DYNCREATE(CMModeCtrlFormVIEW)

protected:
	CMModeCtrlFormVIEW();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMModeCtrlFormVIEW();


public:
	//HDRAWDIB m_hDrawDIB;

public:
	enum { IDD = IDD_MMODECTRLFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTestmmodectrlbutton();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
};


