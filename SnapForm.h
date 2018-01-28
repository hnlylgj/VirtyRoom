#pragma once


// SnapForm 对话框

class SnapForm : public CDialogEx
{
	DECLARE_DYNAMIC(SnapForm)

public:
	SnapForm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SnapForm();

	CBrush m_brush; CFont m_Font;
	LPCTSTR pOutSTR;
	virtual void OnDrawText(LPCTSTR pOutSTR, int mFontCout, CDC* pDC);  // 绘制视图文本

// 对话框数据
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_SNAPFORM };
#endif
	enum { IDD = IDD_SNAPFORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
