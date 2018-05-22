// DlgShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgShow.h"
#include ".\dlgshow.h"

//void OnReceiveData(LPVOID pSender,void* pBuf,DWORD InBufferCount);
/*Deal with the break of com /�������ж� 
*/
//void OnComBreak(LPVOID pSender,DWORD dwMask,COMSTAT stat);
// CDlgShow �Ի���
CDlgParam * CDlgShow::m_dlgparam = NULL;
IMPLEMENT_DYNAMIC(CDlgShow, CDialog)
CDlgShow::CDlgShow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShow::IDD, pParent)
{


}

CDlgShow::~CDlgShow()
{
}

void CDlgShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_CWBOOLEAN1, m_niBtnpar);
	DDX_Control(pDX, IDC_MSCOMM1, m_cComm);
}


BEGIN_MESSAGE_MAP(CDlgShow, CDialog)
	ON_MESSAGE(WM_MY_SETNAME,OnSetBtnName)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_BN_CLICKED(IDC_BTNXG, OnBnClickedBtnxg)
	//	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
END_MESSAGE_MAP()


// CDlgShow ��Ϣ�������

BOOL CDlgShow::OnInitDialog()
{
	CDialog::OnInitDialog();
	//m_insertnum = 0;
	UCHAR mu = 0x01;
	UCHAR mu2 = 0xd2;
	bStartRev =0;
	CString str,str2;
	for (int i=0;i<24;i++)
	{
		str.Format("6800%02x680100%02x16",mu*(i+1),mu2+mu*i);
		str_dw[i] = str;
	}

	//str_dw[0]="68000168C104000103774F16";//"680001680100d216";//68000168C104000003774F16
	//str_dw[1]="68000268C2062010022202224F16";
	//str_dw[2]="68000368C30830400111010202024F16";
	sendtotal=0;
	readtotal=0;
	bfirst = FALSE;
	GetDlgItem(IDC_LIST1)->MoveWindow(10,15,972,558);

	GetDlgItem(IDC_CWBOOLEAN1)->MoveWindow(10,580,100,30);
	//GetDlgItem(IDC_CWBOOLEAN2)->MoveWindow(200,580,100,30);
	GetDlgItem(IDC_CWBOOLEANRUN)->MoveWindow(150,580,100,30);


	GetDlgItem(IDC_STATICBZ)->MoveWindow(390,570,250,45);
	GetDlgItem(IDC_EDIT1)->MoveWindow(400,585,100,25);
	GetDlgItem(IDC_BTNXG)->MoveWindow(530,583,100,25);
	GetDlgItem(IDC_STATIC11)->MoveWindow(650,580,150,30);
	GetDlgItem(IDC_STATIC22)->MoveWindow(800,580,150,30);
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle	|=  LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_List.SetExtendedStyle(dwStyle);;
	m_List.InsertColumn(0, _T("ͨ��"), LVCFMT_CENTER, 40);
	m_List.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 90);	
	m_List.InsertColumn(2, _T("����λ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(3, _T("��������"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(4, _T("������Χ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(5, _T("Ũ��ֵ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(6, _T("��λ"), LVCFMT_CENTER, 60);
	m_List.InsertColumn(7, _T("һ������"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(8, _T("��������"), LVCFMT_CENTER, 90);	
	m_List.InsertColumn(9, _T("TWA"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(10, _T("STEL"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(11, _T("��ע"), LVCFMT_CENTER, 140);

	SetWindowLong(m_List.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES);                     //������չ���Ϊ����
	::SendMessage(m_List.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	//m_List.SetHeaderHeight(1.5);
	//m_List.SetRowHeigt(28); //18��

	//m_List.SetHeaderHeight(2);
	//m_List.SetRowHeigt(41); //12��
	m_List.SetHeaderHeight(1.5);
	m_List.SetRowHeigt(21); //24��

	m_List.SetHeaderBKColor(100,255,100,2); //����ͷ������ɫ
	m_List.SetHeaderFontHW(20,10);

	m_List.SetFontHW(15,9);
	//��ȡ��ʱ����
/*
		CFont* m_pFont;
	if(! m_List.GetItemCount())
	{
		m_pFont = m_List.GetFont();
		CRect Rect(CPoint(0,0),CSize(100,500));
		m_Edit.Create(WS_CHILD | WS_TABSTOP | WS_BORDER,Rect,this,IDC_EDIT);
		m_Edit.SetFont(m_pFont);
	}
	m_List.SetGridBehaviour();
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP );
	m_List.DeleteAllColumns();
	//m_List.SetExtendedStyle(dwStyle);;
	m_List.InsertColumn(0, _T("ͨ��"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, _T("״̬"), LVCFMT_CENTER, 90);	
	m_List.InsertColumn(2, _T("����λ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(3, _T("��������"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(4, _T("������Χ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(5, _T("Ũ��ֵ"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(6, _T("��λ"), LVCFMT_CENTER, 60);
	m_List.InsertColumn(7, _T("һ������"), LVCFMT_CENTER, 90);
	m_List.InsertColumn(8, _T("��������"), LVCFMT_CENTER, 90);	
	m_List.InsertColumn(9, _T("TWA"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(10, _T("STEL"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(11, _T("��ע"), LVCFMT_CENTER, 130);

*/
	theApp.timernum = GetPrivateProfileInt("TIMER","cyc",0,theApp.m_readini);

	CString m_strsel;
	char strBuff[20];
	CString strValue ;
	int state;	
	int m = 0;
	for (int i =0;i<24;i++)
	{
		m_dwstate[i]=0;
		m_strTXData[i] = "";
	}
	for (int k=0;k<24;k++)
	{
		for(int i=0;i<4;i++)
		{
			theApp.i_dwIndex[k][i]=100;
			theApp.i_state[k][i]=0;
			m_yj1[k][i] = 0;
			m_yj2[k][i]=0;
			m_TWA[k][i]=0;
			m_STEL[k][i]=0;
			//	theApp.i_selport[i]=0;
			/*
			str.Format("%d",k*4+i+1);
			m_List.InsertItem(k*4+i,str);*/
		}
	}
	for(int k =0;k<24;k++)
	{
		for(int i=0;i<4;i++)
		{

			theApp.i_state[k][i] =0;
			theApp.i_dwIndex[k][i] = 100;
			m_strsel.Format("PORT%d",k*4+i+1); 
			state = GetPrivateProfileInt(m_strsel,"show ",0,theApp.m_readini);
			if(state == 1)
			{	

				str.Format("%d",m+1);
				m_List.InsertItem(m,str);
				state = GetPrivateProfileInt(m_strsel,"state ",0,theApp.m_readini);
				//theApp.i_state[k][i] =state;
				theApp.i_dwIndex[k][i] = m;
				//if (state == 1)
				//{
				//	m_List.SetItemText(m,1,_T("����"));
				//}
				//else
				//{
				//	m_List.SetItemText(m,1,_T("������"));
				//}
				m_List.SetItemText(m,1,_T("������"));
				GetPrivateProfileString(m_strsel,"num",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,2,strValue);
				GetPrivateProfileString(m_strsel,"Type",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,3,strValue);

				GetPrivateProfileString(m_strsel,"rang",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,4,strValue);

				GetPrivateProfileString(m_strsel,"unit",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,6,strValue);

				state = GetPrivateProfileInt(m_strsel,"waring1",0,theApp.m_readini);
				m_yj1[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,7,strValue);

				state = GetPrivateProfileInt(m_strsel,"waring2",0,theApp.m_readini);
				m_yj2[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,8,strValue);

				state = GetPrivateProfileInt(m_strsel,"twa",0,theApp.m_readini);
				m_TWA[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,9,strValue);

				state = GetPrivateProfileInt(m_strsel,"stel",0,theApp.m_readini);
				m_STEL[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,10,strValue);
				m++;
				theApp.m_index = m;


	
			}
		}
	}


	for (int i=0;i<24;i++)
	{
		m_dwstate[i] =0;
		m_strTXData[i] = "";
	}
	for (int k=0;k<24;k++)
	{
		for (int i=0;i<4;i++)
		{
			m_strsel.Format("PORT%d",k*4+i+1); 
			state = GetPrivateProfileInt(m_strsel,"state",0,theApp.m_readini);
			//theApp.i_state[k][i] =state;
			//if (state == 1)
			{

				state = GetPrivateProfileInt(m_strsel,"show",0,theApp.m_readini);
				if (state == 1)
				{
					m_dwstate[k]++;
				}
			}

		}

	}
	m_dwnum = 0;
	for (int i=0;i<24;i++)
	{
		theApp.i_dwcunz[i] = m_dwstate[i]; 
		if (m_dwstate[i]!=0)
		{
			m_strTXData[m_dwnum] = str_dw[i];
			m_dwnum++;
		}
	}


	m_cycnum = 0;
	for(int i=0;i<24;i++)
		m_rw232[i] = 0;

	CDlgShow::m_dlgparam = new CDlgParam;
	CDlgShow::m_dlgparam->Create(IDD_DLGPARAM);
	CDlgShow::m_dlgparam->ShowWindow(SW_HIDE);
	CDlgShow::m_dlgparam->GetParentHand(this->m_hWnd);

	//////////////////////////////////////////////////////////////////////////

	//CTime time;
	//time = CTime::GetCurrentTime();
	//CString strname = "",strnamedes = "";
	//CString s ;//= time.Format("%Y��%m��%d��\\");
	//s = theApp.GetApplicationPath()+"\\savedata\\";
	//CreateDirectory(s,NULL);
	//s = time.Format("%Y��%m��%d��\\");
	//s = theApp.GetApplicationPath()+"\\savedata\\"+s;
	//CreateDirectory(s,NULL);


	//CString strdes;
	//strdes =s+time.Format("%H-%M-%S\\");;
	//CreateDirectory(strdes,NULL);
	//
	//p_File[0] = fopen(strdes+"dw1.dat","wb");
	//p_File[1] = fopen(strdes+"dw2.dat","wb");
	//p_File[2] = fopen(strdes+"dw3.dat","wb");
	//p_File[3] = fopen(strdes+"dw4.dat","wb");
	//p_File[4] = fopen(strdes+"dw5.dat","wb");
	//p_File[5] = fopen(strdes+"dw6.dat","wb");

	//Sleep(10);
	//m_cycnum = 0;//��ʼ��ʱ

	//OnBnClickedButton1();
	OnBnClickedButton4();//��ʼ������YY.
	return TRUE;

}
BEGIN_EVENTSINK_MAP(CDlgShow, CDialog)
	//ON_EVENT(CDlgShow, IDC_CWBOOLEAN1, 1, ValueChangedCwboolean1, VTS_BOOL)
	ON_EVENT(CDlgShow, IDC_CWBOOLEAN2, DISPID_CLICK, ClickCwboolean2, VTS_NONE)
	//	ON_EVENT(CDlgShow, IDC_MSCOMM1, 1, OnCommMscomm1, VTS_NONE)
	ON_EVENT(CDlgShow, IDC_CWBOOLEAN1, DISPID_CLICK, ClickCwboolean1, VTS_NONE)
	ON_EVENT(CDlgShow, IDC_CWBOOLEANRUN, 1, ValueChangedCwbooleanrun, VTS_BOOL)
	ON_EVENT(CDlgShow, IDC_MSCOMM1, 1, CDlgShow::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

/*
void CDlgShow::ValueChangedCwboolean1(BOOL Value)
{
	// TODO: �ڴ˴������Ϣ����������
	if (Value)
	{
		//ClickCwboolean2();
	}
	else
	{
		CDlgShow::m_dlgparam->ShowWindow(SW_HIDE);
	}
}*/
LRESULT CDlgShow::OnSetBtnName(WPARAM wparam,LPARAM lParam)
{
	CString str,m_strsel;
	char strBuff[20];
	CString strValue ;
	int state;
	int m = 0;
	//for(int j=0;j<96;j++)
	//{
	//	m_List.SetItemText(j,1,"");
	//	m_List.SetItemText(j,2,"");
	//	m_List.SetItemText(j,3,"");
	//	m_List.SetItemText(j,4,"");
	//	m_List.SetItemText(j,5,"");
	//	m_List.SetItemText(j,6,"");
	//	m_List.SetItemText(j,7,"");
	//	m_List.SetItemText(j,8,"");
	//	m_List.SetItemText(j,9,"");
	//	m_List.SetItemText(j,10,"");
	//}
	m_List.DeleteAllItems();
	for(int k =0;k<24;k++)
	{
		for(int i=0;i<4;i++)
		{
			m_yj1[k][i] = 0;
			m_yj2[k][i]=0;
			m_TWA[k][i]=0;
			m_STEL[k][i]=0;
			theApp.i_state[k][i] =0;
			theApp.i_dwIndex[k][i] = 100;
			m_strsel.Format("PORT%d",k*4+i+1); 
			state = GetPrivateProfileInt(m_strsel,"show ",0,theApp.m_readini);
			if(state == 1)
			{	
				str.Format("%d",m+1);
				m_List.InsertItem(m,str);
				state = GetPrivateProfileInt(m_strsel,"state ",0,theApp.m_readini);
				//theApp.i_state[k][i] =state;
				theApp.i_dwIndex[k][i] = m;

				GetPrivateProfileString(m_strsel,"num",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,2,strValue);
				GetPrivateProfileString(m_strsel,"Type",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,3,strValue);

				GetPrivateProfileString(m_strsel,"rang",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,4,strValue);

				GetPrivateProfileString(m_strsel,"unit",NULL,strBuff,20,theApp.m_readini); 
				strValue = strBuff;
				m_List.SetItemText(m,6,strValue);

				state = GetPrivateProfileInt(m_strsel,"waring1",0,theApp.m_readini);
				m_yj1[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,7,strValue);

				state = GetPrivateProfileInt(m_strsel,"waring2",0,theApp.m_readini);
				m_yj2[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,8,strValue);

				state = GetPrivateProfileInt(m_strsel,"twa",0,theApp.m_readini);
				m_TWA[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,9,strValue);

				state = GetPrivateProfileInt(m_strsel,"stel",0,theApp.m_readini);
				m_STEL[k][i] = state;
				strValue.Format("%d",state);
				m_List.SetItemText(m,10,strValue);
				m++;
				theApp.m_index = m;
			}
		}
	}


	for (int i=0;i<24;i++)
	{
		m_dwstate[i] =0;
		m_strTXData[i] = "";
	}
	for (int k=0;k<24;k++)
	{
		for (int i=0;i<4;i++)
		{
			m_strsel.Format("PORT%d",k*4+i+1); 
			state = GetPrivateProfileInt(m_strsel,"state",0,theApp.m_readini);
			//theApp.i_state[k][i] =state;
			//if (state == 1)
			{

				state = GetPrivateProfileInt(m_strsel,"show",0,theApp.m_readini);
				if (state == 1)
				{
					m_dwstate[k]++;
				}
			}

		}

	}
	m_dwnum = 0;
	for (int i=0;i<24;i++)
	{
		
		theApp.i_dwcunz[i] = m_dwstate[i]; 
		if (m_dwstate[i]!=0)
		{
			m_strTXData[m_dwnum] = str_dw[i];
			m_dwnum++;
		}
	}
	m_cycnum = 0;
	return 0;
}

void CDlgShow::ClickCwboolean2()
{
	// TODO: �ڴ˴������Ϣ����������
	for (int k=0;k<24;k++)
	{	
		for(int i=0;i<4;i++)
		{
			m_List.SetItemText(k*i,1,"");
			m_List.SetItemText(k*i,2,"");
			m_List.SetItemText(k*i,3,"");
			m_List.SetItemText(k*i,4,"");
			m_List.SetItemText(k*i,5,"");
			m_List.SetItemText(k*i,6,"");
			m_List.SetItemText(k*i,7,"");
			m_List.SetItemText(k*i,8,"");
			m_List.SetItemText(k*i,9,"");
			m_List.SetItemText(k*i,10,"");
			theApp.i_state[k][i]=0;
		//	theApp.i_selport[i]=0;

		}
	}

}
char HexChar(char c)//���һ���ַ��ǲ���ʮ�������ַ������Ƿ�����Ӧ��ֵ�����򷵻�0x10��
{	if((c>='0')&&(c<='9'))
return c-0x30;
else if((c>='A')&&(c<='F'))
return c-'A'+10;
else if((c>='a')&&(c<='f'))
return c-'a'+10;
else return 0x10;
}
int Str2Hex(CString str,CByteArray &data)
{//��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ�������ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
	int t,t1;
	int rlen=0,len=str.GetLength();
	data.SetSize(len/2);
	for(int i=0;i<len;)
	{char l,h=str[i];
	if(h==' ')
	{i++;
	continue;
	}
	i++;
	if(i>=len)break;
	l=str[i];
	t=HexChar(h);
	t1=HexChar(l);
	if((t==16)||(t1==16))
		break;
	else t=t*16+t1;
	i++;
	data[rlen]=(char)t;
	rlen++;
	}
	data.SetSize(rlen);
	return rlen;
}
void CDlgShow::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//68 00(addr) 68 C1 04(data1  data2  data3  data4) CS 16
	CString str;


	if (nIDEvent == 0)
	{

		//char hexdata[256];
		/*int len = theApp.Str2Hex(m_strTXData[m_cycnum],hexdata);

		serial.SendData(hexdata,12);*/
		//////////////////////////////////////////////////////////////////////////
		
		//CByteArray data;
		//int len=Str2Hex(m_strTXData[m_cycnum],data);
		//m_Comm.put_Output(COleVariant(data));//��������

		//////////////////////////////////////////////////////////////////////////
		CString str1,str2;
		UCHAR lpOutBuffer[8];

//
		CByteArray outbuf;
		outbuf.SetSize(8);

		int len = theApp.Str2Hex(m_strTXData[m_cycnum],lpOutBuffer);
		for (int i=0;i<8;i++) 
		{
			outbuf.SetAt(i,lpOutBuffer[i]);
		}

		m_cComm.put_Output(COleVariant(outbuf));
		//
		//////////////////////////////////////////////////////////////////////////
		for (int i=0;i<8;i++)
		{
			str1.Format("%02x",lpOutBuffer[i]);
			str2+=str1;
		}
		sendtotal++;
		str.Format("%d---",sendtotal);
	    str = str+str2;//m_strTXData[m_cycnum];
		GetDlgItem(IDC_STATIC11)->SetWindowText(str);
		printf("->send:{%s}\n", str);
		for(int i=0;i<24;i++) {
			printf("%d ", m_rw232[i]);
		}
		printf("\n");
		for(int i=0;i<24;i++) {
			if(m_rw232[i] > 3) {
				printf("set [%d] OFFLINE\n", i);
				m_List.SetItemText(theApp.i_dwIndex[i][0],1,"������");
				m_List.SetItemText(theApp.i_dwIndex[i][1],1,"������");
				m_List.SetItemText(theApp.i_dwIndex[i][2],1,"������");
				m_List.SetItemText(theApp.i_dwIndex[i][3],1,"������");
				m_rw232[i] = 0;
			}
		}

		m_rw232[m_cycnum] += 1; //��������״̬

		if(m_rw232[m_cycnum]>3) {
		}


		m_cycnum++;
		if (m_cycnum>=m_dwnum)
		{
			m_cycnum = 0;
		}
	}
	//else if (nIDEvent==1)
	//{
	//}
	CDialog::OnTimer(nIDEvent);
}
void CDlgShow::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nPort = GetPrivateProfileInt("COM","num2",0,theApp.m_readini);

	if(m_cComm.get_PortOpen()) //������ִ��ڱ����Ǵ򿪵ģ���رմ���
		m_cComm.put_PortOpen(FALSE);
	m_cComm.put_CommPort(nPort); //ѡ��COM1�˿�
	m_cComm.put_InputMode(1); //���뷽ʽΪ�����Ʒ�ʽ
	m_cComm.put_InBufferSize(2048); //�������뻺����
	m_cComm.put_OutBufferSize(2048); //�������������
	m_cComm.put_Settings(TEXT("9600,n,8,1"));//�����ʣ���У�飬������λ����ֹͣλ
	if(!m_cComm.get_PortOpen())
	{
		m_cComm.put_PortOpen(TRUE); //�򿪴���
		m_cComm.put_RThreshold(16); //ÿ�����ջ������и��ַ�����մ�������
		m_cComm.put_InputLen(0); //���õ�ǰ���������ݳ���Ϊ0����ʾȫ����ȡ
		m_cComm.get_Input(); //Ԥ���������������������
	}
}
void CDlgShow::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strpot;
	char strBuff[20];
	GetPrivateProfileString("COM","num",NULL,strBuff,20,theApp.m_readini);
	strpot = strBuff;
	int isel = atoi(strpot.Right(strpot.GetLength()-3));
	if (isel>9)
	{
		strpot = "\\\\.\\"+strpot;//��Ӧ�ľ���\\.\COM10

	}

	//////////////////////////////////////////////////////////////////////////
	hCom=CreateFile(strpot,//COM1��
		GENERIC_READ|GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		0, //ͬ����ʽ
		NULL);
	if(hCom==(HANDLE)-1)
	{
		KillTimer(0);

		//KillTimer(1);
		AfxMessageBox("��COMʧ��!");

	//	return FALSE;
	}

	SetupComm(hCom,100,100); //���뻺����������������Ĵ�С����100

	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���


	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=9600; //������Ϊ9600
	dcb.ByteSize=8; //ÿ���ֽ���8λ
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=ONESTOPBIT; //1��ֹͣλ
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
}

void CDlgShow::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//BOOL bRet=serial.Close();

	//if(bRet)
	//{
	//	AfxMessageBox("�ɹ��رմ��ڣ�");
	//}
	//else
	//{
	//	AfxMessageBox("�رմ���ʧ�ܣ�");
	//}
	//m_Comm.put_PortOpen(FALSE);
	//this->m_ComPort.Close();
	if(m_cComm.get_PortOpen()) //������ִ��ڱ����Ǵ򿪵ģ���رմ���
	m_cComm.put_PortOpen(FALSE);
	CDialog::OnClose();
}
void CDlgShow::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//
	//memset((char *)ucopydata,0,sizeof(char)*24*9);
	CString str,str1,str2;
	BOOL m_bdata=FALSE;//�ж��յ�����ͷ��У����Ƿ�ϸ�
	int MODE = 0;
	int DWSEL = 0;
	DWORD wCount=16;//��ȡ���ֽ���
	/*BOOL bReadStat;
	bReadStat=ReadFile(hCom,strbuf,wCount,&wCount,NULL);
	if(!bReadStat)
		AfxMessageBox("������ʧ��!");
	PurgeComm(hCom, PURGE_TXABORT|
	PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	memcpy(udata,strbuf,sizeof(char)*16);
	*/
	///


	////
	for (int i=0;i<16;i++)
	{
		str1.Format("%02x ",udata[i]);
		str2+=str1;
	}		
	if (udata[0]==0x68)
	{
		if (udata[4] == 0xc1)
		{
			MODE = 1;

		}
		else if (udata[4] == 0xc2)
		{
			MODE = 2;
		}
		else if (udata[4] == 0xc3)
		{
			MODE = 3;
		}

	} else {
		printf("        !!! !!! !!!data format ERROR, drop it\n");
		return;
	}
	DWSEL=udata[2];
	m_rw232[DWSEL-1] = 0;
	printf("clear %d flag\n",DWSEL-1);
	/*switch(udata[2])
	{
	case 0x01:
		DWSEL=1;
		//GetDlgItem(IDC_STATIC22)->SetWindowText("2222");
		break;
	case 0x02:
		DWSEL=2;
		break;
	case 0x03:
		DWSEL=3;
		break;
	case 0x04:
		DWSEL=4;
		break;
	case 0x05:
		DWSEL=5;
		break;
	case 0x06:
		DWSEL=6;
		break;
	default:
		DWSEL=0;
		break;
	}
*/
	if (MODE==1)
	{
		if(udata[10] == theApp.Verify_Add(udata,11,0,9))
		{
			m_bdata = TRUE;
		}
	}
	else if (MODE==2)
	{
		if(udata[12] == theApp.Verify_Add(udata,13,0,11))
		{
			m_bdata = TRUE;
		}
	}
	else if (MODE==3)
	{
		if(udata[14] == theApp.Verify_Add(udata,15,0,13))
		{
			m_bdata = TRUE;
		}
	}
	if (MODE==1)
	{
		ucopydata[DWSEL-1][8] = 0x01;
		theApp.i_dwmode[DWSEL-1] = 0x01;
	//	if (theApp.i_state[DWSEL-1][0] ==1)
		{
			if (theApp.i_dwIndex[DWSEL-1][0]!=100)
			{
				ucopydata[DWSEL-1][2]=udata[8];
				ucopydata[DWSEL-1][3]=udata[9];
				theApp.dread[DWSEL-1][0] = (udata[8]*256+udata[9])/100.00;//��2
				str.Format("%.2f",(udata[8]*256+udata[9])/100.00);
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],5,str);
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"����");
				theApp.i_state[DWSEL-1][0] =1;
			}
			else
			{
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"������");
				theApp.i_state[DWSEL-1][0] =0;
			}
			if (theApp.i_dwIndex[DWSEL-1][1]!=100)
			{
				ucopydata[DWSEL-1][0]=udata[6];
				ucopydata[DWSEL-1][1]=udata[7];
				theApp.dread[DWSEL-1][1] = (udata[6]*256+udata[7])/100.00;//��2
				str.Format("%d",(udata[6]*256+udata[7]));
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],5,str);
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"����");
				theApp.i_state[DWSEL-1][1] =1;
			}
			else
			{
				m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"������");
				theApp.i_state[DWSEL-1][1] =0;
			}
			theApp.i_state[DWSEL-1][2] =0;
			theApp.i_state[DWSEL-1][3] =0;
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"������");
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"������");
		}
	}
	else if ( MODE == 2)//m_bdata==TRUE &&
	{
		ucopydata[DWSEL-1][8] = 0x02;
		theApp.i_dwmode[DWSEL-1] = 0x02;
		if (theApp.i_dwIndex[DWSEL-1][0] !=100)
		{
			ucopydata[DWSEL-1][4]=udata[10];
			ucopydata[DWSEL-1][5]=udata[11];
			theApp.dread[DWSEL-1][0] = (udata[10]*256+udata[11])/100.00;
			str.Format("%.2f",(udata[10]*256+udata[11])/100.00);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"����");
			theApp.i_state[DWSEL-1][0] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"������");
			theApp.i_state[DWSEL-1][0] =0;
		}
		if (theApp.i_dwIndex[DWSEL-1][2] !=100)//lel
		{

			ucopydata[DWSEL-1][2]=udata[8];
			ucopydata[DWSEL-1][3]=udata[9];
			theApp.dread[DWSEL-1][2] = (udata[8]*256+udata[9])/100.00;
			str.Format("%.2f",(udata[8]*256+udata[9])/100.00);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"����");
			theApp.i_state[DWSEL-1][2] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"������");
			theApp.i_state[DWSEL-1][2] =0;
		}
		if (theApp.i_dwIndex[DWSEL-1][3] !=100)//UDMH
		{
			ucopydata[DWSEL-1][0]=udata[6];
			ucopydata[DWSEL-1][1]=udata[7];
			theApp.dread[DWSEL-1][3] = (udata[6]*256+udata[7]);
			str.Format("%d",(udata[6]*256+udata[7]));
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"����");
			theApp.i_state[DWSEL-1][3] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"������");
			theApp.i_state[DWSEL-1][3] =0;
		}

		theApp.i_state[DWSEL-1][1] =0;
		m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"������");
		
		
	}
	else if ( MODE == 3)//m_bdata==TRUE &&
	{
		ucopydata[DWSEL-1][8] = 0x03;
		theApp.i_dwmode[DWSEL-1] = 0x03;
		if (theApp.i_dwIndex[DWSEL-1][0] !=100)//��2
		{
			ucopydata[DWSEL-1][6]=udata[12];
			ucopydata[DWSEL-1][7]=udata[13];
			theApp.dread[DWSEL-1][0] = (udata[12]*256+udata[13])/100.00;
			str.Format("%.2f",(udata[12]*256+udata[13])/100.00);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"����");
			theApp.i_state[DWSEL-1][0] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"������");
			theApp.i_state[DWSEL-1][0] =0;
		}
		if (theApp.i_dwIndex[DWSEL-1][1] !=100)
		{

			ucopydata[DWSEL-1][4]=udata[10];
			ucopydata[DWSEL-1][5]=udata[11];
			theApp.dread[DWSEL-1][1] = (udata[10]*256+udata[11]);//NO2
			str.Format("%d",(udata[10]*256+udata[11]));
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"����");
			theApp.i_state[DWSEL-1][1] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"������");
			theApp.i_state[DWSEL-1][1] =0;
		}
		if (theApp.i_dwIndex[DWSEL-1][2] !=100)//lel
		{

			ucopydata[DWSEL-1][2]=udata[8];
			ucopydata[DWSEL-1][3]=udata[9];
			theApp.dread[DWSEL-1][2] = (udata[8]*256+udata[9])/100.00;
			str.Format("%.2f",(udata[8]*256+udata[9])/100.00);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"����");
			theApp.i_state[DWSEL-1][2] =1;
		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"������");
			theApp.i_state[DWSEL-1][2] =1;
		}
		if (theApp.i_dwIndex[DWSEL-1][3] !=100)//UDMN
		{
			ucopydata[DWSEL-1][0]=udata[6];
			ucopydata[DWSEL-1][1]=udata[7];
			theApp.dread[DWSEL-1][3] = (udata[6]*256+udata[7]);
			str.Format("%d",(udata[6]*256+udata[7]));
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],5,str);
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"����");
			theApp.i_state[DWSEL-1][3] =1;

		}
		else
		{
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"������");
			theApp.i_state[DWSEL-1][3] =0;
		}
			
	}
	else{

			theApp.i_state[DWSEL-1][0] =0;
			theApp.i_state[DWSEL-1][1] =0;
			theApp.i_state[DWSEL-1][2] =0;
			theApp.i_state[DWSEL-1][3] =0;
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][0],1,"������");
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][1],1,"������");
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][2],1,"������");
			m_List.SetItemText(theApp.i_dwIndex[DWSEL-1][3],1,"������");
	}
	readtotal++;
	str1.Format("%d --      ",sendtotal);
	str2 = str1 +str2;
	GetDlgItem(IDC_STATIC22)->SetWindowText(str2);
	if (bfirst == FALSE)
	{	
		bfirst = TRUE;
		::SendMessage(theApp.handcur,WM_MY_DRAW,0,0);
	}

	//////////////////////////////////////////////////////////////////////////
	int state=0;
	CString m_strsel;
	for (int k=0;k<24;k++)
	{
		theApp.i_dwcunz[k]=0;
		for (int i=0;i<4;i++)
		{

			m_strsel.Format("PORT%d",k*4+i+1); 
			if (theApp.i_state[k][i] == 1)
			{

				state = GetPrivateProfileInt(m_strsel,"show",0,theApp.m_readini);
				if (state == 1)
				{
					//m_dwstate[k]++;
					theApp.i_dwcunz[k]++;
				}
			}

		}

	}
	//////////////////////////////////////////////////////////////////////////
	

	if (bfirst == TRUE)
	{		//////////////////////////////////////////////////////////////////////////
		for (int i=0;i<24;i++)
		{
			if (m_dwstate[i]!=0)
			{
				//if (ucopydata[i][8]!=0X00)
				{
					fwrite((char *)&ucopydata[i],sizeof(char)*9,1,p_File[i]);
				}
			}
		}
	}
}

void CDlgShow::ClickCwboolean1()
{
	// TODO: �ڴ˴������Ϣ����������
	CDlgShow::m_dlgparam->ShowWindow(SW_SHOW);
}

void CDlgShow::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  bsel=0;
	CString sss;
	bsel = m_List.GetSelectionMark();
	sss=m_List.GetItemText(bsel,11);
	GetDlgItem(IDC_EDIT1)->SetWindowText(sss);


	*pResult = 0;
}

void CDlgShow::OnBnClickedBtnxg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int bsel=0;
	CString sss;
	bsel = m_List.GetSelectionMark();
	GetDlgItem(IDC_EDIT1)->GetWindowText(sss);
	m_List.SetItemText(bsel,11,sss);

}



void CDlgShow::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDCtl == 1000)
	{
		lpMeasureItemStruct->itemHeight = 100;
	}
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgShow::ValueChangedCwbooleanrun(BOOL Value)
{
	// TODO: �ڴ˴������Ϣ����������
	printf("on valuechgCwBLrun\n");
	if (!Value)
	{
		CDlgShow::m_dlgparam->ShowWindow(SW_HIDE);
		m_niBtnpar.SetEnabled(FALSE);
		memset((char *)ucopydata,0,sizeof(char)*24*9);
		CTime time;
		time = CTime::GetCurrentTime();
		CString strname = "",strnamedes = "";
		CString s ;//= time.Format("%Y��%m��%d��\\");
		s = theApp.GetApplicationPath()+"\\savedata\\";
		CreateDirectory(s,NULL);
		s = time.Format("%Y��%m��%d��\\");
		s = theApp.GetApplicationPath()+"\\savedata\\"+s;
		CreateDirectory(s,NULL);


		CString strdes;
		strdes =s+time.Format("%H-%M-%S\\");;
		CreateDirectory(strdes,NULL);
		int fnum = 0;
		for (int i=0;i<24;i++)
		{
			s.Format("Site%d.dat",i+1);
			if (m_dwstate[i]!=0)
			{
				p_File[i] = fopen(strdes+s,"wb");
			}
		}

		Sleep(10);
		m_cycnum = 0;//��ʼ��ʱ
		bStartRev =1;

		SetTimer(0,theApp.timernum,NULL);
	}
	else
	{
		bStartRev = 0;
		m_niBtnpar.SetEnabled(TRUE);
		KillTimer(0);
		for (int i=0;i<24;i++)
		{
			if (m_dwstate[i]!=0)
			{
				 fclose(p_File[i]);
			}
		}
	}
}
//void OnReceiveData(LPVOID pSender,void* pBuf,DWORD InBufferCount)
//{
//
//	byte a[100]="\0";
//	CDlgShow* pDlg = (CDlgShow*) pSender;
//	//UCHAR cget[16];
//	memcpy(a,pBuf,InBufferCount);
//	for(int i=0;i<(int)16;i++)
//	{
//		pDlg->udata[i] = a[i]; 
//	}
//
//	pDlg->OnBnClickedButton2();
//}
//void OnComBreak(LPVOID pSender,DWORD dwMask,COMSTAT stat)
//{
//	//deal with the break of com here
//	switch(dwMask)
//	{
//	case  EV_BREAK:
//		{
//
//			break;
//		}
//	case EV_CTS:
//		{
//			break;
//		}
//	case EV_DSR:
//		{
//			break;
//		}
//	case EV_ERR:
//		{
//			break;
//		}
//	case EV_RING:
//		{
//			break;
//		}
//	case EV_RLSD:
//		{
//			break;
//		}
//	case EV_RXCHAR:
//		{
//			break;
//		}
//	case EV_RXFLAG:
//		{
//			break;
//		}
//	case EV_TXEMPTY:
//		{
//			break;
//		}
//	default:
//		{
//
//		}
//	}
//}

void CDlgShow::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	// 
	unsigned char rxdata[50];//���ݳ��ȸ����Լ���ʵ��Ҫ������
	printf("on_mscomm1: %d......", m_cComm.get_CommEvent());
	//	if(bStartRev == 1)
	{

		if (m_cComm.get_CommEvent()==2)
		{
			variant_inp = m_cComm.get_Input(); //read data
			safearray_inp = variant_inp;
			len = safearray_inp.GetOneDimSize();//�õ���Ч���ݳ���
			printf("RECV %d:\n", len);
			for (k = 0; k < len; k++)
			{
				safearray_inp.GetElement(&k, rxdata+k);
			}
			//�������ݺ󣬸���ʵ�ʽ���rxdata
			for(int i=0;i<(int)len;i++)
			{
				udata[i] = rxdata[i];
				printf("%02x",rxdata[i]);
			}
			printf("\n");

			if((rxdata[0]==0x68) && (rxdata[1]==0x00) && (rxdata[3]==0x68)) {
				OnBnClickedButton2();
			} else {
				//��ƴDATA
				printf(".............header error");
			}

		}
	}
}
