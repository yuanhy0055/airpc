#pragma once
#include "highgui.h"
#include "afxwin.h"

// CDlgPic 对话框

class CDlgPic : public CDialog
{
	DECLARE_DYNAMIC(CDlgPic)

public:
	CDlgPic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPic();

// 对话框数据
	enum { IDD = IDD_DLGPIC };

protected:
	CvFont font;
	IplImage * image1;
	IplImage * image2;
	IplImage * pic ; 
	IplImage * pic2;
	CvPoint zuobao;
	int m_xScreen ;//= GetSystemMetrics(SM_CXSCREEN);
	int m_yScreen ;//= GetSystemMetrics(SM_CYSCREEN);


	CString m_strini ;//=GetApplicationPath() + _T("//ZB.ini");
	int dwtotal;
	int mpos[24];
	CvPoint center[24];
	int selp;
	BOOL bset;
	void DrawPicToHdc(IplImage *img, UINT ID);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnCloseTime();
	void SetInitCtrl();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_Cmbdw;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
