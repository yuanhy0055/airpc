#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "ListCtrlCl.h"
#include "XPButton.h"

// CDlgHisData 对话框

class CDlgHisData : public CDialog
{
	DECLARE_DYNAMIC(CDlgHisData)

public:
	CDlgHisData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHisData();

// 对话框数据
	enum { IDD = IDD_DLGHISDATA };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrlCl m_Listdata;
	afx_msg void OnBnClickedBtnline();
	
	CTreeCtrl m_Tree;
protected:
	CString s_data;
	long nPos; // 当前位置
	int m_total;//统计数目
	int m_allnum;//记录的总数
	int m_num;
	CString filepath;//文件路径
	CString strpath;////文件夹得路径
	CString m_strname;//文件名
	HTREEITEM t_hSel;
    FILE *fpsel;
	//int m_bsel[4];//判断选择
	int m_bsel;
	void DeleteFolder(CString sPath) ;
	void AddFile(CString StrPath, HTREEITEM faItem );
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl m_TimeCtrl;
	afx_msg void OnBnClickedBtnsave();
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtndata();
	//CButton m_chko2;
protected:
	CNiGraph m_Draw;
public:
	afx_msg void OnBnClickedBtnnext();
	afx_msg void OnBnClickedBtndel();
	afx_msg void OnBnClickedBtntrace();
	afx_msg void OnBnClickedBtnclear();
protected:
	CButton m_BtnData;
	CButton m_BtnLine;
	CButton m_BtnSave;
	CButton m_BtnDel;
	CButton m_BtnNext;
	CButton m_BtnTrace;
	CButton m_BtnClear;
	CString strh;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	DECLARE_EVENTSINK_MAP()
	void ValueChangedCwboolean1(BOOL Value);
	void CursorChangeCwgraph2(long* CursorIndex, VARIANT* XPos, VARIANT* YPos, BOOL* bTracking);
};
