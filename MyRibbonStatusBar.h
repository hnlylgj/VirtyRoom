#pragma once


// CMyRibbonStatusBar

class CMyRibbonStatusBar : public CMFCStatusBar
{
	DECLARE_DYNAMIC(CMyRibbonStatusBar)

public:
	CMyRibbonStatusBar();
	virtual ~CMyRibbonStatusBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


