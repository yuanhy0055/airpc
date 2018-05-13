// DlgParam.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgParam.h"
#include ".\dlgparam.h"


// CDlgParam 对话框

IMPLEMENT_DYNAMIC(CDlgParam, CDialog)
CDlgParam::CDlgParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParam::IDD, pParent)
{
}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSEL, m_CmbSel);
	//DDX_Control(pDX, IDC_CMBTYPE, m_cmbtype);
	//DDX_Control(pDX, IDC_CMBRANG, m_cmbrang);
	//DDX_Control(pDX, IDC_CMBUNIT, m_cmbunit);
//	DDX_Control(pDX, IDC_CMBPORT, m_CmbCom);
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBSEL, OnCbnSelchangeCmbsel)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)

	ON_BN_CLICKED(IDC_BTNDEL, OnBnClickedBtndel)
END_MESSAGE_MAP()


// CDlgParam 消息处理程序

BOOL CDlgParam::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(&wndTopMost,20,200,500,100,SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);
	m_CmbSel.InsertString(0,"点位1-O2");
	m_CmbSel.InsertString(1,"点位1-NO2");
	m_CmbSel.InsertString(2,"点位1-EX");
	m_CmbSel.InsertString(3,"点位1-UDMH");
	m_CmbSel.InsertString(4,"点位2-O2");
	m_CmbSel.InsertString(5,"点位2-NO2");
	m_CmbSel.InsertString(6,"点位2-EX");
	m_CmbSel.InsertString(7,"点位2-UDMH");

	m_CmbSel.InsertString(8,"点位3-O2");
	m_CmbSel.InsertString(9,"点位3-NO2");
	m_CmbSel.InsertString(10,"点位3-EX");
	m_CmbSel.InsertString(11,"点位3-UDMH");
	m_CmbSel.InsertString(12,"点位4-O2");
	m_CmbSel.InsertString(13,"点位4-NO2");
	m_CmbSel.InsertString(14,"点位4-EX");
	m_CmbSel.InsertString(15,"点位4-UDMH");

	m_CmbSel.InsertString(16,"点位5-O2");
	m_CmbSel.InsertString(17,"点位5-NO2");
	m_CmbSel.InsertString(18,"点位5-EX");
	m_CmbSel.InsertString(19,"点位5-UDMH");
	m_CmbSel.InsertString(20,"点位6-O2");
	m_CmbSel.InsertString(21,"点位6-NO2");
	m_CmbSel.InsertString(22,"点位6-EX");
	m_CmbSel.InsertString(23,"点位6-UDMH");

	m_CmbSel.InsertString(24,"点位7-O2");
	m_CmbSel.InsertString(25,"点位7-NO2");
	m_CmbSel.InsertString(26,"点位7-EX");
	m_CmbSel.InsertString(27,"点位7-UDMH");
	m_CmbSel.InsertString(28,"点位8-O2");
	m_CmbSel.InsertString(29,"点位8-NO2");
	m_CmbSel.InsertString(30,"点位8-EX");
	m_CmbSel.InsertString(31,"点位8-UDMH");
	m_CmbSel.InsertString(32,"点位9-O2");
	m_CmbSel.InsertString(33,"点位9-NO2");
	m_CmbSel.InsertString(34,"点位9-EX");
	m_CmbSel.InsertString(35,"点位9-UDMH");
	m_CmbSel.InsertString(36,"点位10-O2");
	m_CmbSel.InsertString(37,"点位10-NO2");
	m_CmbSel.InsertString(38,"点位10-EX");
	m_CmbSel.InsertString(39,"点位10-UDMH");
	m_CmbSel.InsertString(40,"点位11-O2");
	m_CmbSel.InsertString(41,"点位11-NO2");
	m_CmbSel.InsertString(42,"点位11-EX");
	m_CmbSel.InsertString(43,"点位11-UDMH");
	m_CmbSel.InsertString(44,"点位12-O2");
	m_CmbSel.InsertString(45,"点位12-NO2");
	m_CmbSel.InsertString(46,"点位12-EX");
	m_CmbSel.InsertString(47,"点位12-UDMH");

	m_CmbSel.InsertString(48,"点位13-O2");
	m_CmbSel.InsertString(49,"点位13-NO2");
	m_CmbSel.InsertString(50,"点位13-EX");
	m_CmbSel.InsertString(51,"点位13-UDMH");


	m_CmbSel.InsertString(52,"点位14-O2");
	m_CmbSel.InsertString(53,"点位14-NO2");
	m_CmbSel.InsertString(54,"点位14-EX");
	m_CmbSel.InsertString(55,"点位14-UDMH");

	m_CmbSel.InsertString(56,"点位15-O2");
	m_CmbSel.InsertString(57,"点位15-NO2");
	m_CmbSel.InsertString(58,"点位15-EX");
	m_CmbSel.InsertString(59,"点位15-UDMH");
	m_CmbSel.InsertString(60,"点位16-O2");
	m_CmbSel.InsertString(61,"点位16-NO2");
	m_CmbSel.InsertString(62,"点位16-EX");
	m_CmbSel.InsertString(63,"点位16-UDMH");

	m_CmbSel.InsertString(64,"点位17-O2");
	m_CmbSel.InsertString(65,"点位17-NO2");
	m_CmbSel.InsertString(66,"点位17-EX");
	m_CmbSel.InsertString(67,"点位17-UDMH");

	m_CmbSel.InsertString(68,"点位18-O2");
	m_CmbSel.InsertString(69,"点位18-NO2");
	m_CmbSel.InsertString(70,"点位18-EX");
	m_CmbSel.InsertString(71,"点位18-UDMH");

	m_CmbSel.InsertString(72,"点位19-O2");
	m_CmbSel.InsertString(73,"点位19-NO2");
	m_CmbSel.InsertString(74,"点位19-EX");
	m_CmbSel.InsertString(75,"点位19-UDMH");
	m_CmbSel.InsertString(76,"点位20-O2");
	m_CmbSel.InsertString(77,"点位20-NO2");
	m_CmbSel.InsertString(78,"点位20-EX");
	m_CmbSel.InsertString(79,"点位20-UDMH");

	m_CmbSel.InsertString(80,"点位21-O2");
	m_CmbSel.InsertString(81,"点位21-NO2");
	m_CmbSel.InsertString(82,"点位21-EX");
	m_CmbSel.InsertString(83,"点位21-UDMH");
	m_CmbSel.InsertString(84,"点位22-O2");
	m_CmbSel.InsertString(85,"点位22-NO2");
	m_CmbSel.InsertString(86,"点位22-EX");
	m_CmbSel.InsertString(87,"点位22-UDMH");

	m_CmbSel.InsertString(88,"点位23-O2");
	m_CmbSel.InsertString(89,"点位23-NO2");
	m_CmbSel.InsertString(90,"点位23-EX");
	m_CmbSel.InsertString(91,"点位23-UDMH");
	m_CmbSel.InsertString(92,"点位24-O2");
	m_CmbSel.InsertString(93,"点位24-NO2");
	m_CmbSel.InsertString(94,"点位24-EX");
	m_CmbSel.InsertString(95,"点位24-UDMH");
	return TRUE;
}


void CDlgParam::OnCbnSelchangeCmbsel()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_sel = m_CmbSel.GetCurSel();

	//m_cmbtype.SetCurSel(0);
	//m_cmbrang.SetCurSel(0);
	//m_cmbunit.SetCurSel(0);



}

void CDlgParam::OnBnClickedBtnadd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,m_strsel;
	int m_sel = m_CmbSel.GetCurSel();
	int m_s = 0;// /4
	int m_y = 0;// %4 

	m_s = m_sel/4;
	m_y = m_sel%4;

	m_strsel.Format("PORT%d",m_sel+1); 
	//GetDlgItem(IDC_CMBSEL)->GetWindowText(str);
	//WritePrivateProfileString(m_strsel,"num",str,theApp.m_readini); 
	//GetDlgItem(IDC_CMBPORT)->GetWindowText(str);
	//WritePrivateProfileString(m_strsel,"com",str,theApp.m_readini); 
	//GetDlgItem(IDC_CMBTYPE)->GetWindowText(str);
	//WritePrivateProfileString(m_strsel,"Type",str,theApp.m_readini); 
	/*GetDlgItem(IDC_CMBRANG)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"rang",str,theApp.m_readini); 
	GetDlgItem(IDC_CMBUNIT)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"unit",str,theApp.m_readini); */


	GetDlgItem(IDC_EDW1)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"waring1",str,theApp.m_readini); 

	GetDlgItem(IDC_EDW2)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"waring2",str,theApp.m_readini); 

	GetDlgItem(IDC_EDTWA)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"twa",str,theApp.m_readini); 
	GetDlgItem(IDC_EDSTEL)->GetWindowText(str);
	WritePrivateProfileString(m_strsel,"stel",str,theApp.m_readini); 

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	int state = pBtn->GetCheck();

	//str.Format("%d",state);
	//WritePrivateProfileString(m_strsel,"state ",str,theApp.m_readini); 
	WritePrivateProfileString(m_strsel,"show ","1",theApp.m_readini); 
	::SendMessage(m_pHwnd,WM_MY_SETNAME,m_s,m_y);

}
void CDlgParam::GetParentHand(HWND hwnd)
{
	m_pHwnd = hwnd;
}
void CDlgParam::OnBnClickedBtndel()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str,m_strsel;
	int m_sel = m_CmbSel.GetCurSel();
	int m_s = 0;// /4
	int m_y = 0;// %4 

	m_s = m_sel/4;
	m_y = m_sel%4;

	m_strsel.Format("PORT%d",m_sel+1); 
	WritePrivateProfileString(m_strsel,"show ","0",theApp.m_readini); 
	::SendMessage(m_pHwnd,WM_MY_SETNAME,m_s,m_y);
}
