#pragma once


// RestfulQtCoreDlg �Ի���

class RestfulQtCoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RestfulQtCoreDlg)

public:
	RestfulQtCoreDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RestfulQtCoreDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESTFULQTCOREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
