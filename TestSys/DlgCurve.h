#pragma once
#include "afxwin.h"


// CDlgCurve 对话框

class CDlgCurve : public CDialog
{
	DECLARE_DYNAMIC(CDlgCurve)

public:
	CDlgCurve(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCurve();

// 对话框数据
	enum { IDD = IDD_DLGCURVE };

protected:
	virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
