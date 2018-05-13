#pragma once
#include "afxwin.h"


// CDlgParam 对话框

class CDlgParam : public CDialog
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParam();

// 对话框数据
	enum { IDD = IDD_DLGPARAM };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CmbSel;
	afx_msg void OnCbnSelchangeCmbsel();
	//CComboBox m_cmbtype;
	//CComboBox m_cmbrang;
	//CComboBox m_cmbunit;
	afx_msg void OnBnClickedBtnadd();	
	void GetParentHand(HWND  hwnd);	
	HWND m_pHwnd;
	CComboBox m_CmbCom;
	afx_msg void OnBnClickedBtndel();
};
