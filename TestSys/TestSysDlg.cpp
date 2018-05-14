// TestSysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSys.h"
#include "TestSysDlg.h"
#include ".\testsysdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "SkinH.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestSysDlg 对话框



CTestSysDlg::CTestSysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSysDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTestSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_EDIT1, m_edtime);
}

BEGIN_MESSAGE_MAP(CTestSysDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTestSysDlg 消息处理程序

BOOL CTestSysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置皮肤
	//SkinH_Attach();
	//CString str;
	//str = theApp.GetApplicationPath()+_T("//Aero.she");
	//::SkinH_AttachEx(str, NULL);

	//SkinH_AdjustHSV(-100,50,-10);
	//SkinH_AdjustAero( 
	//	200,200,50,100,0, 0,100,10,180);


	/*m_ownwnd=new COwnWnd();

	CRect rect;
	GetClientRect(rect);
	rect.top=0;
	rect.bottom=80;
	rect.left=5;
	rect.right = 600;

	m_ownwnd->Create(rect,this,500);
	GetClientRect(rect);
	rect.top=0;
	rect.bottom=80;
	rect.left=600;
	rect.right = 1014;
	*/
	CRect rect;
	GetClientRect(rect);
	rect.top=0;
	rect.bottom=75;
	rect.left=0;
	rect.right = 1024;
//
	GetDlgItem(IDC_STATICNAME)->MoveWindow(rect,TRUE);
	GetDlgItem(IDC_STATICTIMER)->ShowWindow(SW_HIDE);
//	GetClientRect(rect);
//	rect.top=0;
//	rect.bottom=80;
//	rect.left=700;
//	rect.right = 1014;
//GetDlgItem(IDC_STATICTIMER)->MoveWindow(rect,TRUE);
	//m_ownwnd2=new COwnWnd2();

	//GetClientRect(rect);
	//rect.top=0;
	//rect.bottom=80;
	//rect.left=800;
	//rect.right = 800;

	//m_ownwnd2->Create(rect,this,1014);

	//////////////////////////////////////////////////////////////////////////
	

	this->MoveWindow(0,0,1024,768);
	m_Tab.InsertItem(0,"           实 时 监 测 数 据          ");
	m_Tab.InsertItem(1,"           实 时 监 测 曲 线          ");
	m_Tab.InsertItem(2,"            历  史  数  据            ");
	m_Tab.InsertItem(3,"             电  子  地  图            ");
	GetDlgItem(IDC_TAB1)->MoveWindow(10,80,1000,660);

	m_dlgcurve.Create(IDD_DLGCURVE,&m_Tab);
	m_dlgshow.Create(IDD_DLGSHOW,&m_Tab);
	m_dlghisdata.Create(IDD_DLGHISDATA,&m_Tab);
	m_dlgpic.Create(IDD_DLGPIC,&m_Tab);
	CRect rc;
	m_Tab.GetClientRect(rc);
	rc.top +=30;
	rc.left+=1;
	rc.right-=2;
	rc.bottom -=8;
	m_dlgshow.MoveWindow(&rc);
	m_dlgcurve.MoveWindow(&rc);

	m_dlghisdata.MoveWindow(&rc);
	m_dlgpic.MoveWindow(&rc);
	m_dlgcurve.ShowWindow(SW_HIDE);
	m_dlgshow.ShowWindow(SW_SHOW);
	m_dlghisdata.ShowWindow(SW_HIDE);
	m_dlgpic.ShowWindow(SW_HIDE);
	m_Tab.SetCurSel(0);
	SetTimer(0,1000,NULL);



	CWnd *pWnd = GetDlgItem(IDC_STATICTIMER);

	// 获取按钮的原来字体设置
	CDC* pDC = pWnd->GetDC();
	CPen* pen = new CPen(PS_SOLID, 1, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(pen);

	CFont *pFont = pWnd->GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);

	// 改变字体大小设置，并且创建新的字体对象
	lf.lfHeight = 25;    
	lf.lfUnderline = FALSE;
	strcpy_s(lf.lfFaceName, "黑体");
	pNewFont = new CFont; // 注意把CFont* pNewFont; 放在类成员中，在析构函数中delete
	pNewFont->CreateFontIndirect(&lf);
	// 通过句柄设置按钮的字体
	pWnd->SetFont(pNewFont);
	CTime cTime = CTime::GetCurrentTime();  
	CString strTime;  
	//字符串格式化时间   
	strTime = cTime.Format("%Y年%m月%d日 %H时%M分%S秒");  
	this->SetWindowText(strTime);
	//设置当前窗口标题   
	//GetDlgItem(IDC_STATICTIMER)->SetWindowText(strTime);

	CWnd *pWnd2 = GetDlgItem(IDC_STATICNAME);

	// 获取按钮的原来字体设置
	pDC = pWnd->GetDC();
	pen = new CPen(PS_SOLID, 1, RGB(0, 0, 255));
	pOldPen = pDC->SelectObject(pen);

	pFont = pWnd->GetFont();

	pFont->GetLogFont(&lf);

	// 改变字体大小设置，并且创建新的字体对象
	//lf.lfHeight = 55;    
	//lf.lfUnderline = FALSE;
	//strcpy(lf.lfFaceName, "黑体");
	//pNewFont = new CFont; // 注意把CFont* pNewFont; 放在类成员中，在析构函数中delete
	//pNewFont->CreateFontIndirect(&lf);
	//// 通过句柄设置按钮的字体
	//pWnd2->SetFont(pNewFont);
	//GetDlgItem(IDC_STATICNAME)->SetWindowText("              多功能气体检测系统");
	CString filename = theApp.GetApplicationPath()+"//title.JPG";

	image1 = cvLoadImage(filename,1);
	image2 = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,3);


	cvInitFont( &font, CV_FONT_HERSHEY_PLAIN ,1.4, 1.4, 0, 2, 1);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTestSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestSysDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTestSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestSysDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_Tab.GetCurSel())
	{
	case 0:	
		m_dlgcurve.ShowWindow(SW_HIDE);
		m_dlgshow.ShowWindow(SW_SHOW);
		m_dlghisdata.ShowWindow(SW_HIDE);
		m_dlgpic.ShowWindow(SW_HIDE);
		m_dlgpic.OnCloseTime();
		break;
	case 1:
		m_dlgcurve.ShowWindow(SW_SHOW);
		m_dlgshow.ShowWindow(SW_HIDE);
		m_dlghisdata.ShowWindow(SW_HIDE);
		m_dlgpic.ShowWindow(SW_HIDE);
		m_dlgcurve.SetOnInit();
		break;
	case 2:	
		m_dlgcurve.ShowWindow(SW_HIDE);
		m_dlgshow.ShowWindow(SW_HIDE);
		m_dlghisdata.ShowWindow(SW_SHOW);
		m_dlgpic.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_dlgcurve.ShowWindow(SW_HIDE);
		m_dlgshow.ShowWindow(SW_HIDE);
		m_dlghisdata.ShowWindow(SW_HIDE);
		m_dlgpic.ShowWindow(SW_SHOW);
		m_dlgpic.SetInitCtrl();
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CTestSysDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime cTime = CTime::GetCurrentTime();  
	CString strTime;  
	//字符串格式化时间   
	strTime = cTime.Format("%Y年%m月%d日 %H时%M分%S秒");  
	this->SetWindowText(strTime);
	////设置当前窗口标题   
	//GetDlgItem(IDC_STATICTIMER)->SetWindowText(strTime);

	CvScalar colors = {255,0,0};
	cvCopy(image1,image2);
	CString temp = "";
	//zuobao.y=60;
	//zuobao.x = 750;
	//char *p ;
	//p = (LPSTR)(LPCTSTR)strTime;
	//cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
	DrawPicToHdc(image2,IDC_STATICNAME);


	CDialog::OnTimer(nIDEvent);
}

HBRUSH CTestSysDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	 HBRUSH   hbr   =   CDialog::OnCtlColor(pDC,   pWnd,   nCtlColor);
	if (((pWnd->GetDlgCtrlID() == IDC_STATICTIMER)) && (nCtlColor == CTLCOLOR_STATIC))
	{
		COLORREF clr = RGB(0,150,0);
		pDC->SetTextColor(clr);   //设置红色的文本
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);     //设置黑色的背景
		hbr = ::CreateSolidBrush(clr);
		return hbr;  //作为约定，返回背景色对应的刷子句柄
	}
	else if ((pWnd->GetDlgCtrlID() == IDC_STATICNAME)&& (nCtlColor == CTLCOLOR_STATIC))
	{

		COLORREF clr = RGB(0,0,200);
		pDC->SetTextColor(clr);   //设置红色的文本
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);     //设置黑色的背景
		hbr = ::CreateSolidBrush(clr);
		return hbr;  //作为约定，返回背景色对应的刷子句柄
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
void CTestSysDlg::DrawPicToHdc(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img,1);
	cimg.DrawToHDC(hDC,&rect);
	cimg.Destroy();
	ReleaseDC(pDC);
}
void CTestSysDlg::OnDestroy()
{
	if (image1!=NULL)
	{
		cvReleaseImage(&image1);
		cvReleaseImage(&image2);
	}
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
