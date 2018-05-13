// TestSysDlg.h : 头文件
//

#pragma once


#include "DlgCurve.h"
#include "DlgShow.h"
#include "afxcmn.h"
#include "OwnWnd.h""
#include "afxwin.h"
#include "DlgHisData.h"
#include "DlgPic.h"
#include "highgui.h"
// CTestSysDlg 对话框
class CTestSysDlg : public CDialog
{
// 构造
public:
	CTestSysDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTSYS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:

	CvFont font;
	IplImage * image1;
	IplImage * image2;
	CvPoint zuobao;
	CFont* pNewFont;
	HICON m_hIcon;
	void DrawPicToHdc(IplImage *img, UINT ID);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//COwnWnd *m_ownwnd;
	CDlgCurve m_dlgcurve;
	CDlgShow  m_dlgshow;
	CDlgHisData m_dlghisdata;
	CDlgPic m_dlgpic;
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CEdit m_edtime;
public:
	afx_msg void OnDestroy();
};
