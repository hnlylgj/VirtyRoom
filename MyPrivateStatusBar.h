#pragma once


// CMyPrivateStatusBar

class CMyPrivateStatusBar : public CMFCRibbonStatusBar /*CStatusBar*/
{
	DECLARE_DYNAMIC(CMyPrivateStatusBar)

public:
	CMyPrivateStatusBar();
	virtual ~CMyPrivateStatusBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


