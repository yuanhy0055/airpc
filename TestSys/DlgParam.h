#pragma once
#include "afxwin.h"


// CDlgParam �Ի���

class CDlgParam : public CDialog
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParam();

// �Ի�������
	enum { IDD = IDD_DLGPARAM };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
