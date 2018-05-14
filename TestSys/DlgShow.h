#pragma once
#include "afxcmn.h"

#include "ListCtrlCl.h"
//#include "SortListCtrl.h"
#include "DlgParam.h"
#include "mscomm1.h"

//#include "ComPort.h"
//#include "Serial.h"
#include "afxwin.h"
#define	WM_COMM_MESSAGE WM_USER+1

#define MSG_READ	0
#define MSG_WRITE	1
// CDlgShow 对话框

#include "ListCtrlExt.h"
class CDlgShow : public CDialog
{
	DECLARE_DYNAMIC(CDlgShow)

public:

	char SendBuf[8];
	char ReadBuf[16];
	CDlgShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShow();

// 对话框数据
	enum { IDD = IDD_DLGSHOW };

protected:
	//LsComm::CComPort m_ComPort;
	FILE *p_File[24];
	BOOL bStartRev;//开始接收 


	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	CListCtrlCl m_List;
	//CListCtrlExt m_List;
	//CListCtrlCl m_List;
	char hexdata[256];
	UCHAR data[16];
	static CDlgParam * m_dlgparam;
	DECLARE_EVENTSINK_MAP()
	//void ValueChangedCwboolean1(BOOL Value);
	afx_msg LRESULT OnSetBtnName(WPARAM wparam,LPARAM lParam);
	//int m_insertnum;

	void ClickCwboolean2();
	afx_msg void OnTimer(UINT nIDEvent);
	int m_dwstate[24];//点位状态//判断点位是否存在在线
	int m_dwnum;
	int ComNum;
	CString str_dw[24];
	CString m_strTXData[24];
	double m_yj1[24][4];
	double m_yj2[24][4];
	double m_TWA[24][4];
	double m_STEL[24][4];
	UCHAR ucopydata[24][9];

	CString m_strRXData;
	int m_cycnum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	//afx_msg LRESULT OnCommMessage(WPARAM wParam,LPARAM lParam);
	//BYTE m_Type[1024]; 
private:
	char strbuf[16];
	//CSerial serial;
	int sendtotal;
	int readtotal;
public:
	UCHAR udata[16];
	BOOL bfirst;
	//void OnCommMscomm1();
	CButton m_btn;
	HANDLE hCom;
	afx_msg void OnBnClickedButton2();
	void ClickCwboolean1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnxg();
//	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void ValueChangedCwbooleanrun(BOOL Value);
	CNiButton m_niBtnpar;
	afx_msg void OnBnClickedButton4();
	CMscomm1 m_cComm;
	void OnCommMscomm1();
};
