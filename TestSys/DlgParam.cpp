// DlgParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgParam.h"
#include ".\dlgparam.h"


// CDlgParam �Ի���

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


// CDlgParam ��Ϣ�������

BOOL CDlgParam::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(&wndTopMost,20,200,500,100,SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);
	m_CmbSel.InsertString(0,"��λ1-O2");
	m_CmbSel.InsertString(1,"��λ1-NO2");
	m_CmbSel.InsertString(2,"��λ1-EX");
	m_CmbSel.InsertString(3,"��λ1-UDMH");
	m_CmbSel.InsertString(4,"��λ2-O2");
	m_CmbSel.InsertString(5,"��λ2-NO2");
	m_CmbSel.InsertString(6,"��λ2-EX");
	m_CmbSel.InsertString(7,"��λ2-UDMH");

	m_CmbSel.InsertString(8,"��λ3-O2");
	m_CmbSel.InsertString(9,"��λ3-NO2");
	m_CmbSel.InsertString(10,"��λ3-EX");
	m_CmbSel.InsertString(11,"��λ3-UDMH");
	m_CmbSel.InsertString(12,"��λ4-O2");
	m_CmbSel.InsertString(13,"��λ4-NO2");
	m_CmbSel.InsertString(14,"��λ4-EX");
	m_CmbSel.InsertString(15,"��λ4-UDMH");

	m_CmbSel.InsertString(16,"��λ5-O2");
	m_CmbSel.InsertString(17,"��λ5-NO2");
	m_CmbSel.InsertString(18,"��λ5-EX");
	m_CmbSel.InsertString(19,"��λ5-UDMH");
	m_CmbSel.InsertString(20,"��λ6-O2");
	m_CmbSel.InsertString(21,"��λ6-NO2");
	m_CmbSel.InsertString(22,"��λ6-EX");
	m_CmbSel.InsertString(23,"��λ6-UDMH");

	m_CmbSel.InsertString(24,"��λ7-O2");
	m_CmbSel.InsertString(25,"��λ7-NO2");
	m_CmbSel.InsertString(26,"��λ7-EX");
	m_CmbSel.InsertString(27,"��λ7-UDMH");
	m_CmbSel.InsertString(28,"��λ8-O2");
	m_CmbSel.InsertString(29,"��λ8-NO2");
	m_CmbSel.InsertString(30,"��λ8-EX");
	m_CmbSel.InsertString(31,"��λ8-UDMH");
	m_CmbSel.InsertString(32,"��λ9-O2");
	m_CmbSel.InsertString(33,"��λ9-NO2");
	m_CmbSel.InsertString(34,"��λ9-EX");
	m_CmbSel.InsertString(35,"��λ9-UDMH");
	m_CmbSel.InsertString(36,"��λ10-O2");
	m_CmbSel.InsertString(37,"��λ10-NO2");
	m_CmbSel.InsertString(38,"��λ10-EX");
	m_CmbSel.InsertString(39,"��λ10-UDMH");
	m_CmbSel.InsertString(40,"��λ11-O2");
	m_CmbSel.InsertString(41,"��λ11-NO2");
	m_CmbSel.InsertString(42,"��λ11-EX");
	m_CmbSel.InsertString(43,"��λ11-UDMH");
	m_CmbSel.InsertString(44,"��λ12-O2");
	m_CmbSel.InsertString(45,"��λ12-NO2");
	m_CmbSel.InsertString(46,"��λ12-EX");
	m_CmbSel.InsertString(47,"��λ12-UDMH");

	m_CmbSel.InsertString(48,"��λ13-O2");
	m_CmbSel.InsertString(49,"��λ13-NO2");
	m_CmbSel.InsertString(50,"��λ13-EX");
	m_CmbSel.InsertString(51,"��λ13-UDMH");


	m_CmbSel.InsertString(52,"��λ14-O2");
	m_CmbSel.InsertString(53,"��λ14-NO2");
	m_CmbSel.InsertString(54,"��λ14-EX");
	m_CmbSel.InsertString(55,"��λ14-UDMH");

	m_CmbSel.InsertString(56,"��λ15-O2");
	m_CmbSel.InsertString(57,"��λ15-NO2");
	m_CmbSel.InsertString(58,"��λ15-EX");
	m_CmbSel.InsertString(59,"��λ15-UDMH");
	m_CmbSel.InsertString(60,"��λ16-O2");
	m_CmbSel.InsertString(61,"��λ16-NO2");
	m_CmbSel.InsertString(62,"��λ16-EX");
	m_CmbSel.InsertString(63,"��λ16-UDMH");

	m_CmbSel.InsertString(64,"��λ17-O2");
	m_CmbSel.InsertString(65,"��λ17-NO2");
	m_CmbSel.InsertString(66,"��λ17-EX");
	m_CmbSel.InsertString(67,"��λ17-UDMH");

	m_CmbSel.InsertString(68,"��λ18-O2");
	m_CmbSel.InsertString(69,"��λ18-NO2");
	m_CmbSel.InsertString(70,"��λ18-EX");
	m_CmbSel.InsertString(71,"��λ18-UDMH");

	m_CmbSel.InsertString(72,"��λ19-O2");
	m_CmbSel.InsertString(73,"��λ19-NO2");
	m_CmbSel.InsertString(74,"��λ19-EX");
	m_CmbSel.InsertString(75,"��λ19-UDMH");
	m_CmbSel.InsertString(76,"��λ20-O2");
	m_CmbSel.InsertString(77,"��λ20-NO2");
	m_CmbSel.InsertString(78,"��λ20-EX");
	m_CmbSel.InsertString(79,"��λ20-UDMH");

	m_CmbSel.InsertString(80,"��λ21-O2");
	m_CmbSel.InsertString(81,"��λ21-NO2");
	m_CmbSel.InsertString(82,"��λ21-EX");
	m_CmbSel.InsertString(83,"��λ21-UDMH");
	m_CmbSel.InsertString(84,"��λ22-O2");
	m_CmbSel.InsertString(85,"��λ22-NO2");
	m_CmbSel.InsertString(86,"��λ22-EX");
	m_CmbSel.InsertString(87,"��λ22-UDMH");

	m_CmbSel.InsertString(88,"��λ23-O2");
	m_CmbSel.InsertString(89,"��λ23-NO2");
	m_CmbSel.InsertString(90,"��λ23-EX");
	m_CmbSel.InsertString(91,"��λ23-UDMH");
	m_CmbSel.InsertString(92,"��λ24-O2");
	m_CmbSel.InsertString(93,"��λ24-NO2");
	m_CmbSel.InsertString(94,"��λ24-EX");
	m_CmbSel.InsertString(95,"��λ24-UDMH");
	return TRUE;
}


void CDlgParam::OnCbnSelchangeCmbsel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int m_sel = m_CmbSel.GetCurSel();

	//m_cmbtype.SetCurSel(0);
	//m_cmbrang.SetCurSel(0);
	//m_cmbunit.SetCurSel(0);



}

void CDlgParam::OnBnClickedBtnadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
