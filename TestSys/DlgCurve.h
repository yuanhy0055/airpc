#pragma once
#include "afxwin.h"


// CDlgCurve �Ի���

class CDlgCurve : public CDialog
{
	DECLARE_DYNAMIC(CDlgCurve)

public:
	CDlgCurve(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCurve();

// �Ի�������
	enum { IDD = IDD_DLGCURVE };

protected:
	virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg LRESULT OnmyDraw(WPARAM wparam,LPARAM lParam);
	int m_num;
	int m_sys;
	double datavalue[1][2000];
	CNiGraph m_graph;
	afx_msg void OnTimer(UINT nIDEvent);
	CComboBox m_cmbseldw;
	void SetOnInit(void);
protected:
	int m_numw[96];
	//double dlbnum;
	int m_selline;
	BOOL btime;

public:
	afx_msg void OnCbnSelchangeCmbseldw();
protected:
	void OnShowLine();
	int readnum;
};
