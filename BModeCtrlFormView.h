#pragma once
//#include <vfw.h>


// CBModeCtrlFormView ������ͼ

class CBModeCtrlFormView : public CFormView
{
	DECLARE_DYNCREATE(CBModeCtrlFormView)

protected:
	CBModeCtrlFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBModeCtrlFormView();

public:
	enum { IDD = IDD_BMODECTRLFORMVIEW };
	//enum { IDD = IDD_BModeAdjust_DIALOG};
	//---------------------------------------------------------------------------------
	
public:
	//HDRAWDIB m_hDrawDIB;

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
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedTestButton();
	afx_msg void OnBnClickedTestformviewbutton();
	afx_msg void OnPaint();
	afx_msg void OnClose();
};


