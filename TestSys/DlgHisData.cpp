// DlgHisData.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgHisData.h"
#include ".\dlghisdata.h"


// CDlgHisData 对话框

IMPLEMENT_DYNAMIC(CDlgHisData, CDialog)
CDlgHisData::CDlgHisData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHisData::IDD, pParent)
{
}

CDlgHisData::~CDlgHisData()
{
}

void CDlgHisData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTDATA, m_Listdata);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_TimeCtrl);
//	DDX_Control(pDX, IDC_CHECK1, m_chko2);
	DDX_Control(pDX, IDC_CWGRAPH2, m_Draw);
	DDX_Control(pDX, IDC_BTNLINE, m_BtnLine);
	DDX_Control(pDX, IDC_BTNDATA, m_BtnData);
	DDX_Control(pDX, IDC_BTNSAVE, m_BtnSave);
	DDX_Control(pDX, IDC_BTNDEL, m_BtnDel);
	DDX_Control(pDX, IDC_BTNNEXT, m_BtnNext);
	DDX_Control(pDX, IDC_BTNTRACE, m_BtnTrace);
	DDX_Control(pDX, IDC_BTNCLEAR, m_BtnClear);
}


BEGIN_MESSAGE_MAP(CDlgHisData, CDialog)
	ON_BN_CLICKED(IDC_BTNLINE, OnBnClickedBtnline)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BTNSAVE, OnBnClickedBtnsave)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnNMDblclkTree1)
	ON_BN_CLICKED(IDC_BTNDATA, OnBnClickedBtndata)
	ON_BN_CLICKED(IDC_BTNNEXT, OnBnClickedBtnnext)
	ON_BN_CLICKED(IDC_BTNDEL, OnBnClickedBtndel)
	ON_BN_CLICKED(IDC_BTNTRACE, OnBnClickedBtntrace)
	ON_BN_CLICKED(IDC_BTNCLEAR, OnBnClickedBtnclear)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
END_MESSAGE_MAP()


// CDlgHisData 消息处理程序
BOOL CDlgHisData::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_total = 0;
	nPos=0;
	m_num = 0;//下一页按钮次数
	GetDlgItem(IDC_LISTDATA)->MoveWindow(230,40,730,500);

	GetDlgItem(IDC_CWGRAPH2)->MoveWindow(230,40,730,500);

	//树形控件
	m_Tree.ModifyStyle(NULL, 
		TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	//HTREEITEM t_hRoot = m_TreeSelR.InsertItem("选择线缆通道");
	//HTREEITEM t_hSel;
	m_Tree.SetBkColor (RGB(200,200,200));//背景颜色
	//

	m_Draw.Axes.Item(1).SetMinMax(0,1000);
	m_Draw.Axes.Item(2).SetMinMax(0,10);

	DWORD dwStyle = m_Listdata.GetExtendedStyle();
	dwStyle	|=  LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_Listdata.SetExtendedStyle(dwStyle);;
	m_Listdata.InsertColumn(0, _T("时间"), LVCFMT_CENTER, 160);
	m_Listdata.InsertColumn(1, _T("氧气浓度值(%VOL)"), LVCFMT_CENTER, 140);	
	m_Listdata.InsertColumn(2, _T("二氧化氮浓度值(ppm)"), LVCFMT_CENTER, 140);
	m_Listdata.InsertColumn(3, _T("EX浓度值(%LEL)"), LVCFMT_CENTER, 140);
	m_Listdata.InsertColumn(4, _T("UDMH浓度值(ppm)"), LVCFMT_CENTER, 140);
	m_Listdata.SetRowHeigt(20);
	m_Listdata.SetFontHW(15,10);	
	m_Listdata.SetHeaderBKColor(100,255,100,2); //设置头部背景色
	//m_Listdata.de

	CString str;
	for (int i=0;i<30;i++)
	{
		//str.Format("%d",i);
		m_Listdata.InsertItem(i,"");
	}

	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO1);
	pBtn->SetCheck(1);
	m_bsel = 1;

	GetDlgItem(IDC_STATICSEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO4)->ShowWindow(SW_HIDE);	
	CTime cTime = CTime::GetCurrentTime();  
	CString strTime;  
	//字符串格式化时间   
	//strTime.Format("开始时间 %d:%d:%d",cTime.GetHour(),cTime.GetMinute(),cTime.GetSecond()); 
	//strTime=cTime.Format("%H-%M-%S");

	strTime = cTime.Format("%Y年%m月%d日"); 
	m_TimeCtrl.SetFormat(strTime);
	return TRUE;
}



void CDlgHisData::OnBnClickedBtnline()
{
	// TODO: 在此添加控件通知处理程序代码

	m_num = 0;
	nPos = 0; // 当前位置
	m_total = 0;//统计数目
	//

	GetDlgItem(IDC_STATICSEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO4)->ShowWindow(SW_SHOW);
	//
	GetDlgItem(IDC_BTNNEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNTRACE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CWBOOLEAN1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNCLEAR)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_LISTDATA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CWGRAPH2)->ShowWindow(SW_SHOW);
	UCHAR Data[9] = {0};
	double m_do2 = 0.0;
	int index = 0;
	//CNiReal64Vector plotData(1);
	//CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	//int state = pBtn->GetCheck();
	//m_bsel[0] = state;
	BOOL bover = FALSE;

	if (filepath != "")
	{
		fpsel = fopen(filepath,"rb");	
		do {
			fread((UCHAR *)&Data,sizeof(Data[0]),sizeof(Data[0])*9,fpsel);
			if (feof(fpsel))
			{
				bover = TRUE;
			}
			if (bover==FALSE)
			{
				index++;
				m_allnum = index;
			}
			if (feof(fpsel))
			{
				bover = TRUE;
			}
		}while (bover != TRUE);

		//fclose(fpsel);
	}

}
void CDlgHisData::OnBnClickedBtndata()
{
	// TODO: 在此添加控件通知处理程序代码
OnBnClickedBtnline();
	for (int i=0;i<30;i++)
	{			
		m_Listdata.SetItemText(i,0,"");
		m_Listdata.SetItemText(i,1,"");
		m_Listdata.SetItemText(i,2,"");
		m_Listdata.SetItemText(i,3,"");
		m_Listdata.SetItemText(i,4,"");
	}
	m_Draw.ClearData();

	m_Draw.Axes.Item(1).SetMinMax(0,1000);
	m_Draw.Axes.Item(2).SetMinMax(0,10);

	m_num = 0;
	nPos = 0; // 当前位置
	m_total = 0;//统计数目


	int   m_h = atoi(strh.Left(2));
	int   m_m = atoi(strh.Mid(3,2));
	float m_s = atoi(strh.Right(2)) * 1.0f;
	//
	GetDlgItem(IDC_STATICSEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO4)->ShowWindow(SW_HIDE);
	//
	GetDlgItem(IDC_BTNNEXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CWBOOLEAN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNTRACE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNCLEAR)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTDATA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CWGRAPH2)->ShowWindow(SW_HIDE);
	int index = 0;
	int numshow = 0; //记录数据是否显示	
	BOOL b_init = FALSE;
	BOOL bover = FALSE;
	UCHAR Data[9] = {0};
	float m_dO2 = 0.0;
	float m_dNo2 = 0.0;
	float m_dEx = 0.0;
	float m_dUdmh = 0.0;
	CString str = "";
	for (int m=0;m<5;m++)
	{
		m_Listdata.DeleteColumn(0);
	}
	if (filepath.Right(4) == ".dat")
	{
		//m_Listdata.DeleteAllItems();
		fpsel = fopen(filepath,"rb");
		do {
			
			fread((UCHAR *)&Data,sizeof(Data[0]),sizeof(Data[0])*9,fpsel);
			if (b_init==FALSE)
			{
				//b_init=TRUE;

				if (Data[8]==0x01)
				{
					b_init=TRUE;
					m_Listdata.InsertColumn(0, _T("时间"), LVCFMT_CENTER, 160);
					m_Listdata.InsertColumn(1, _T("氧气浓度值(%VOL)"), LVCFMT_CENTER, 280);	
					m_Listdata.InsertColumn(2, _T("二氧化氮浓度值(ppm)"), LVCFMT_CENTER, 280);
					m_Listdata.InsertColumn(3, _T("EX浓度值(%LEL)"), LVCFMT_CENTER, 0);
					m_Listdata.InsertColumn(4, _T("UDMH浓度值(ppm)"), LVCFMT_CENTER, 0);
				}
				else if (Data[8]==0x02)
				{		
					b_init=TRUE;	
					m_Listdata.InsertColumn(0, _T("时间"), LVCFMT_CENTER, 160);
					m_Listdata.InsertColumn(1, _T("氧气浓度值(%VOL)"), LVCFMT_CENTER, 186);	
					m_Listdata.InsertColumn(2, _T("二氧化氮浓度值(ppm)"), LVCFMT_CENTER, 0);
					m_Listdata.InsertColumn(3, _T("EX浓度值(%LEL)"), LVCFMT_CENTER, 186);
					m_Listdata.InsertColumn(4, _T("UDMH浓度值(ppm)"), LVCFMT_CENTER, 186);
				}

				else if (Data[8]==0x03)
				{	
					b_init=TRUE;
					m_Listdata.InsertColumn(0, _T("时间"), LVCFMT_CENTER, 160);
					m_Listdata.InsertColumn(1, _T("氧气浓度值(%VOL)"), LVCFMT_CENTER, 140);	
					m_Listdata.InsertColumn(2, _T("二氧化氮浓度值(ppm)"), LVCFMT_CENTER, 140);
					m_Listdata.InsertColumn(3, _T("EX浓度值(%LEL)"), LVCFMT_CENTER, 140);
					m_Listdata.InsertColumn(4, _T("UDMH浓度值(ppm)"), LVCFMT_CENTER, 140);
				}	
				m_Listdata.SetRowHeigt(15);
				m_Listdata.SetFontHW(15,10);
				m_Listdata.SetRowHeigt(20);;



				//CString str;
				//for (int i=0;i<30;i++)
				//{
				//	//str.Format("%d",i);
				//	m_Listdata.InsertItem(i,"");
				//}

			}
			if (feof(fpsel))
			{
				bover = TRUE;
				nPos = 0;
			}
			if (bover ==FALSE)//&&Data[8]<=0x03&&Data[8]>0x00)
			{
				if (Data[8]==0x01)
				{
					m_dO2 = (Data[2]*256+Data[3])/100.0f;
					m_dNo2 = (Data[0]*256+Data[1])*1.0f;
					m_dEx = 0.0;
					m_dUdmh = 0.0;
				}
				else if (Data[8]==0x02)
				{
					m_dO2 = (Data[4]*256+Data[5])/100.0f;
					m_dNo2 =0.0;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1]*1.0f);
				}
				else if (Data[8]==0x03)
				{
					m_dO2 = (Data[6]*256+Data[7])/100.0f;
					m_dNo2 = (Data[4]*256+Data[5])*1.0f;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1]*1.0f);
				}
				if (numshow<30)
				{

					//str.Format("%d",m_total);
					if(Data[8]<=0x03&&Data[8]>0x00)
					{
						str.Format("%d点%d分%.0f秒",m_h,m_m,m_s);
						m_Listdata.SetItemText(numshow,0,str);
						
						if (Data[8]==0x01)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.0f",m_dNo2);
							m_Listdata.SetItemText(numshow,2,str);
						}
						else if (Data[8]==0x02)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.2f",m_dEx);
							m_Listdata.SetItemText(numshow,3,str);

							str.Format("%.0f",m_dUdmh);
							m_Listdata.SetItemText(numshow,4,str);
						}
						else if (Data[8]==0x03)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.0f",m_dNo2);
							m_Listdata.SetItemText(numshow,2,str);
							str.Format("%.2f",m_dEx);
							m_Listdata.SetItemText(numshow,3,str);
							str.Format("%.0f",m_dUdmh);
							m_Listdata.SetItemText(numshow,4,str);
						}
						numshow++;
					}
					m_total++;

					m_h = atoi(strh.Left(2));
					m_m = atoi(strh.Mid(3,2));
					m_s = atoi(strh.Right(2))*1.0f;
					for (int m=0;m<m_total;m++)
					{
						m_s=m_s+(theApp.timernum/1000.0f);
						if (m_s>59)
						{
							m_m++;
							if (m_m>59)
							{
								m_h++;
								if (m_h>23)
								{
									m_h = 0;
								}
								m_m=0;
							}
							m_s=0;
						}
					}
				}
				index++;
			}
		
			if (feof(fpsel))
			{
				bover = TRUE;
				nPos = 0;
			}
		}while (bover != TRUE);


	}

}


void CDlgHisData::AddFile(CString StrPath, HTREEITEM faItem )
//StrPath为传递过来的目录层次，本次函数调用中搜索的文件都是它的下一层的。
//faItem为传递过来的Tree节点，本次函数调用中添加的Tree节点都是它的子节点。
{
	CFileFind OneFile;
	CString FName, DirName;
	BOOL BeWorking; 
	HTREEITEM NewItem;	

	DirName = StrPath+"\\*.*";
	BeWorking = OneFile.FindFile( DirName );
	while ( BeWorking ) {  		//BeWorking非零，指找了文件或目录

		//查找同级的目录
		BeWorking = OneFile.FindNextFile();

		if ( OneFile.IsDirectory() && !OneFile.IsDots() )        //如果查找的结果是目录又不是".."或"."
		{	
			//向Tree1中添加目录;
			DirName = OneFile.GetFilePath();
			FName = OneFile.GetFileTitle(); 
			//IDC_TREE1
			NewItem = m_Tree.InsertItem( FName, faItem );    //NewItem取得节点，其目的是为了下一层中
			//添加节点方便，递归时把它传过去。
			//进入下一层递归调用。
			AddFile(DirName, NewItem);
		}

		//退出递归时，到了这里！！！
		if ( !OneFile.IsDirectory() && !OneFile.IsDots() )       //如果查找结果是文件
		{
			//向Tree1中添加文件
			FName = OneFile.GetFileTitle();			 //注意这里用的是GetFileTitle,因为
			//这里是添加文件。
			m_Tree.InsertItem( FName, faItem );
		}


	}// end of while

	OneFile.Close();						//记着用完CFileFild实例要关闭
}
void CDlgHisData::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);


	
	m_Tree.DeleteAllItems();
	m_TimeCtrl.SetFormat(_T("yyyy'年'MM'月'dd日"));
	GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(s_data);
	t_hSel = m_Tree.InsertItem(s_data);

	s_data = theApp.GetApplicationPath()+"\\savedata\\"+s_data;
	AddFile(s_data,t_hSel);
	// TODO: 在此添加控件通知处理程序代码
	m_Tree.SetRedraw(TRUE);
	*pResult = 0;
}

void CDlgHisData::OnBnClickedBtnsave()
{
	// TODO: 在此添加控件通知处理程序代码

	int index = 0;
	BOOL bover = FALSE;
	UCHAR Data[9] = {0};
	float m_dO2 = 0.0;
	float m_dNo2 = 0.0;
	float m_dEx = 0.0;
	float m_dUdmh = 0.0;
	CString str = "";
	//int i,j;
	CString temp;
	FILE* fpSaveTest;
	CString strSavePath;
	int m_h = atoi(strh.Left(2));
	int m_m = atoi(strh.Mid(3,2));
	float m_s = atoi(strh.Right(2)) * 1.0f;
	CFileDialog savedlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_NOCHANGEDIR,"*.xls|*.xls",NULL);
	if(savedlg.DoModal()==IDOK)
	{
		strSavePath = savedlg.GetPathName();	
		strSavePath += ".xls";

		fpSaveTest = fopen(strSavePath,"w+");

		if (filepath.Right(4) == ".dat")
		{
			fpsel = fopen(filepath,"rb");
			//str = filepath.Right(5);
			//str = str.Left(str.GetLength()-4);
			//fprintf(fpSaveTest,temp);
			//fprintf(fpSaveTest,"\n");
			temp = "时间\t点位"+m_strname;
			fprintf(fpSaveTest,temp);
			fprintf(fpSaveTest,"\n");
			do {
				fread((UCHAR *)&Data,sizeof(Data[0]),sizeof(Data[0])*9,fpsel);

				if (feof(fpsel))
				{
					bover = TRUE;
					nPos = 0;
				}
				if (bover==FALSE)
				{
				str.Format("%d点%d分%.0f秒",m_h,m_m,m_s);
				temp =str + "\t";
				if (Data[8]==0x01)
				{
					m_dO2 = (Data[2]*256+Data[3])/100.0f;
					m_dNo2 = (Data[0]*256+Data[1])*1.0f;
					m_dEx = 0.0;
					m_dUdmh = 0.0;
					str.Format("O2-%.2f",m_dO2);
					temp =temp + str + "\t";
					str.Format("NO2-%d",m_dNo2);
					temp = temp +str + "\t";
					fprintf(fpSaveTest,temp);
					fprintf(fpSaveTest,"\n");
				}
				else if (Data[8]==0x02)
				{
					m_dO2 = (Data[4]*256+Data[5])/100.0f;
					m_dNo2 =0.0;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1])*1.0f;
					str.Format("O2-%.2f",m_dO2);
					temp =temp + str + "\t";
					str.Format("Ex-%.2f",m_dEx);
					temp =temp +str + "\t";
					str.Format("Udmh-%d",m_dUdmh);
					temp =temp +str + "\t";
					fprintf(fpSaveTest,temp);
					fprintf(fpSaveTest,"\n");
				}
				else if (Data[8]==0x03)
				{
					m_dO2 = (Data[6]*256+Data[7])/100.0f;
					m_dNo2 = (Data[4]*256+Data[5])*1.0f;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1])*1.0f;
					str.Format("O2-%.2f",m_dO2);
					temp =temp + str + "\t";
					str.Format("NO2-%d",m_dNo2);
					temp = temp +str + "\t";
					str.Format("Ex-%.2f",m_dEx);
					temp =temp +str + "\t";
					str.Format("Udmh-%d",m_dUdmh);
					temp =temp +str + "\t";
					fprintf(fpSaveTest,temp);
					fprintf(fpSaveTest,"\n");
				}/*
				fprintf(fpSaveTest,temp);
				fprintf(fpSaveTest,"\n");*/
				index++;
				///////////////////
				m_s=m_s+theApp.timernum/1000.0f;
				if (m_s>59)
				{
					m_m++;
					if (m_m>59)
					{
						m_h++;
						if (m_h>23)
						{
							m_h = 0;
						}
						m_m=0;
					}
					m_s=0;
				}

				}
				/////
				if (feof(fpsel))
				{
					bover = TRUE;
					nPos = 0;
				}
			}while (bover != TRUE);

			fclose(fpsel);
			::MessageBox(NULL, "导出结束!", "", MB_OK);

		}

		else{
			::MessageBox(NULL, "正确选择需要导出的文件!", "?", MB_OK);
		}
		fclose(fpSaveTest);
	}
}
void CDlgHisData::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem,hItem2,hItem3;
	hItem = m_Tree.GetSelectedItem();
	CString strname;
	//以GetItemText()函数为例：
	CString S1 = m_Tree.GetItemText(hItem);
	if (S1.Left(4)=="Site")
	{
		hItem2 = m_Tree.GetParentItem(hItem);
		strname = m_Tree.GetItemText(hItem2);
		strh = strname;
		strname = strname+"//"+S1+".dat";
		m_strname = S1;

		hItem3 = m_Tree.GetParentItem(hItem2);
		S1 = m_Tree.GetItemText(hItem3);
		strname = S1+"//"+strname;
		filepath = theApp.GetApplicationPath()+"\\savedata\\"+strname;
		AfxMessageBox("已选择"+strname);

	}
	else if (S1.Right(2)=="日")
	{
		filepath = theApp.GetApplicationPath()+"\\savedata\\"+S1;
	}
	else
	{
		hItem2 = m_Tree.GetParentItem(hItem);
		strname = m_Tree.GetItemText(hItem2);
		strname = strname+"//"+S1;
		filepath = theApp.GetApplicationPath()+"\\savedata\\"+strname;
	}
	*pResult = 0;
}




void CDlgHisData::OnBnClickedBtnnext()
{
	m_num++;
	nPos = m_total*9;//m_num*(30*9);
	// TODO: 在此添加控件通知处理程序代码

	int m_h = atoi(strh.Left(2));
	int m_m = atoi(strh.Mid(3,2));
	float m_s = atoi(strh.Right(2))*1.0f;
	int index = 0;
	int numshow = 0;
	BOOL bover = FALSE;
	UCHAR Data[9] = {0};
	float m_dO2 = 0.0;
	float m_dNo2 = 0.0;
	float m_dEx = 0.0;
	float m_dUdmh = 0.0;
	CString str = "";
	if (m_total>=m_allnum)
	{
		m_num = 0;
		nPos = 0; // 当前位置
		m_total = 0;//统计数目
	}
	if (filepath.Right(4) == ".dat" && m_total<=m_allnum)
	{
		for (int i=0;i<30;i++)
		{
			m_Listdata.SetItemText(i,0,"");
			m_Listdata.SetItemText(i,1,"");
			m_Listdata.SetItemText(i,2,"");
			m_Listdata.SetItemText(i,3,"");
			m_Listdata.SetItemText(i,4,"");
		}
		do {
//////////////////////////////////////////////////////////////////////////

			m_h = atoi(strh.Left(2));
			m_m = atoi(strh.Mid(3,2));
			m_s = atoi(strh.Right(2))*1.0f;
			for (int m=0;m<m_total;m++)
			{
				m_s=m_s+(theApp.timernum/1000.0f);
				if (m_s>59)
				{
					m_m++;
					if (m_m>59)
					{
						m_h++;
						if (m_h>23)
						{
							m_h = 0;
						}
						m_m=0;
					}
					m_s=0;
				}
			}
//////////////////////////////////////////////////////////////////////////
			

			fseek(fpsel, nPos, SEEK_SET);
			fread((UCHAR *)&Data,sizeof(Data[0]),sizeof(Data[0])*9,fpsel);
			if (feof(fpsel))
			{
				bover = TRUE;
				nPos = 0;
			}
			if (bover==FALSE)//&&Data[8]<=0x03&&Data[8]>0x00)
			{
				if (Data[8]==0x01)
				{
					m_dO2 = (Data[2]*256+Data[3])/100.0f;
					m_dNo2 = (Data[0]*256+Data[1])*1.0f;
					m_dEx = 0.0;
					m_dUdmh = 0.0;
				}
				else if (Data[8]==0x02)
				{
					m_dO2 = (Data[4]*256+Data[5])/100.0f;
					m_dNo2 =0.0;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1])*1.0f;
				}
				else if (Data[8]==0x03)
				{
					m_dO2 = (Data[6]*256+Data[7])/100.0f;
					m_dNo2 = (Data[4]*256+Data[5])*1.0f;
					m_dEx = (Data[2]*256+Data[3])/100.0f;
					m_dUdmh = (Data[0]*256+Data[1])*1.0f;
				}
				if (numshow<30)
				{
					if (Data[8]<=0x03&&Data[8]>0x00)
					{
						//str.Format("%d",m_total);
						str.Format("%d点%d分%.0f秒",m_h,m_m,m_s);
						m_Listdata.SetItemText(numshow,0,str);

						if (Data[8]==0x01)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.0f",m_dNo2);
							m_Listdata.SetItemText(numshow,2,str);
						}
						else if (Data[8]==0x02)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.2f",m_dEx);
							m_Listdata.SetItemText(numshow,3,str);

							str.Format("%.0f",m_dUdmh);
							m_Listdata.SetItemText(numshow,4,str);
						}
						else if (Data[8]==0x03)
						{
							str.Format("%.2f",m_dO2);
							m_Listdata.SetItemText(numshow,1,str);
							str.Format("%.0f",m_dNo2);
							m_Listdata.SetItemText(numshow,2,str);
							str.Format("%.2f",m_dEx);
							m_Listdata.SetItemText(numshow,3,str);
							str.Format("%.0f",m_dUdmh);
							m_Listdata.SetItemText(numshow,4,str);
						}
						numshow++;
					}
					m_total++;
					//////////////////////////////////////////////////////////////////////////时间
					

				}
				else{
					break;
				}
				index++;
				nPos+=9;

			}
			if (feof(fpsel))
			{
				bover = TRUE;
				nPos = 0;
			}
		}while (bover != TRUE);

	//	fclose(fpsel);

	}
}

void CDlgHisData::OnBnClickedBtndel()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDYES == MessageBox( "是否确认删除？" , "Warning!!",MB_YESNO|MB_ICONWARNING))
	{
		DeleteFolder(filepath);
//////////////////////////////////////////////////////////////////////////

		m_Tree.DeleteAllItems();
		m_TimeCtrl.SetFormat(_T("yyyy'年'MM'月'dd日"));
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowText(s_data);
		t_hSel = m_Tree.InsertItem(s_data);

		s_data = theApp.GetApplicationPath()+"\\savedata\\"+s_data;
		AddFile(s_data,t_hSel);
		// TODO: 在此添加控件通知处理程序代码
		m_Tree.SetRedraw(TRUE);
	}
	else{
	}


}

void CDlgHisData::DeleteFolder(CString sPath) 
{ 
	CFileFind ff; 
	BOOL bFound; 
	bFound = ff.FindFile(sPath + "\\*.*"); 
	if (!bFound)
	{
		DeleteFile(sPath); 
	}
	while(bFound) 
	{ 
		bFound = ff.FindNextFile(); 
		CString sFilePath = ff.GetFilePath(); 

		if(ff.IsDirectory()) 
		{ 
			if(!ff.IsDots()) 
			{ 
				DeleteFolder(sFilePath); 
			} 
		} 
		else 
		{ 
			if(ff.IsReadOnly()) 
			{ 
				SetFileAttributes(sFilePath, FILE_ATTRIBUTE_NORMAL); 
			} 
			DeleteFile(sFilePath); 
		} 
	} 
	ff.Close(); 
	//上面已经把文件夹下面的文件全部删除了，如果需要把文件夹也删除掉则加上以下代码 
	    SetFileAttributes(sPath, FILE_ATTRIBUTE_NORMAL);  //设置文件夹的属性 
	    RemoveDirectory(sPath);  //删除文件夹 
}
void CDlgHisData::OnBnClickedBtntrace()
{
	// TODO: 在此添加控件通知处理程序代码

	nPos = m_num*(1000*9);

	m_Draw.GetCursors().Item(1).SetXPosition(m_num*1000+10);

	m_num++;
	// TODO: 在此添加控件通知处理程序代码
	int index = 0;
	BOOL bover = FALSE;
	UCHAR Data[9] = {0};
	float m_dO2 = 0.0;
	float m_dNo2 = 0.0;
	float m_dEx = 0.0;
	float m_dUdmh = 0.0;
	CNiReal64Vector plotData(1000);
	CString str = "";
	if (m_total>=m_allnum)
	{
		//m_num = 0;
		//nPos = 0; // 当前位置
		//m_total = 0;//统计数目
	}
	if (filepath.Right(4) == ".dat" && m_total<=m_allnum)
	{

		do {
			fseek(fpsel, nPos, SEEK_SET);
			fread((UCHAR *)&Data,sizeof(Data[0]),sizeof(Data[0])*9,fpsel);

			if (Data[8]==0x01)
			{
				m_dO2 = (Data[2]*256+Data[3])/100.0f;
				m_dNo2 = (Data[0]*256+Data[1])*1.0f;
				m_dEx = 0.0;
				m_dUdmh = 0.0;
			}
			else if (Data[8]==0x02)
			{
				m_dO2 = (Data[4]*256+Data[5])/100.0f;
				m_dNo2 =0.0;
				m_dEx = (Data[2]*256+Data[3])/100.0f;
				m_dUdmh = (Data[0]*256+Data[1])*1.0f;
			}
			else if (Data[8]==0x03)
			{
				m_dO2 = (Data[6]*256+Data[7])/100.0f;
				m_dNo2 = (Data[4]*256+Data[5])*1.0f;
				m_dEx = (Data[2]*256+Data[3])/100.0f;
				m_dUdmh = (Data[0]*256+Data[1])*1.0f;
			}
			if (index<1000)
			{
				if (m_bsel==1)
				{
					plotData[index] =  m_dO2;
				}
				else if (m_bsel==2)
				{
					plotData[index] =  m_dNo2;
				}
				else if (m_bsel==3)
				{
					plotData[index] =  m_dEx;
				}
				else if (m_bsel==4)
				{
					plotData[index] =  m_dUdmh;
				}
				m_total++;
			}
			else
			{
				break;
			}

			index++;
			nPos+=9;
	
			if (feof(fpsel))
			{
				bover = TRUE;
				nPos = 0;
			}
		}while (bover != TRUE);
		m_Draw.GetPlots().Item("Plot-1").ChartY(plotData);

	}

}
void CDlgHisData::OnBnClickedBtnclear()
{
	// TODO: 在此添加控件通知处理程序代码

	m_Draw.ClearData();

	m_Draw.Axes.Item(1).SetMinMax(0,1000);
	m_Draw.Axes.Item(2).SetMinMax(0,10);

	m_num = 0;
	nPos = 0; // 当前位置
	m_total = 0;//统计数目
}

void CDlgHisData::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnclear();
	m_bsel=1;
	m_Draw.Axes.Item(2).SetMinMax(-1,30);
	m_Draw.Axes.Item(3).SetMinMax(-1,30);
}

void CDlgHisData::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnclear();
	m_bsel=2;
	m_Draw.Axes.Item(2).SetMinMax(-1,2000);
	m_Draw.Axes.Item(3).SetMinMax(-1,2000);
}

void CDlgHisData::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnclear();
	m_bsel=3;
	m_Draw.Axes.Item(2).SetMinMax(-1,100);
	m_Draw.Axes.Item(3).SetMinMax(-1,100);
}

void CDlgHisData::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnclear();
	m_bsel=4;
	m_Draw.Axes.Item(2).SetMinMax(-1,2000);
	m_Draw.Axes.Item(3).SetMinMax(-1,2000);
}
BEGIN_EVENTSINK_MAP(CDlgHisData, CDialog)
	ON_EVENT(CDlgHisData, IDC_CWBOOLEAN1, 1, ValueChangedCwboolean1, VTS_BOOL)
	ON_EVENT(CDlgHisData, IDC_CWGRAPH2, 1, CursorChangeCwgraph2, VTS_PI4 VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()

void CDlgHisData::ValueChangedCwboolean1(BOOL Value)
{
	// TODO: 在此处添加消息处理程序代码
	if(Value)
		m_Draw.SetTrackMode(CNiGraph::TrackZoomRectXYWithUndo);
	else
	{
		m_Draw.SetTrackMode(CNiGraph::TrackDragCursor);
		m_Draw.Axes.Item(1).SetMinMax(m_num*1000,(m_num+1)*1000);
		if (m_bsel==1)
		{
			m_Draw.Axes.Item(2).SetMinMax(-1,30);
			m_Draw.Axes.Item(3).SetMinMax(-1,30);
		}
		else if (m_bsel==3)
		{
			m_Draw.Axes.Item(2).SetMinMax(-1,100);
			m_Draw.Axes.Item(3).SetMinMax(-1,100);
		}
		else if (m_bsel==2 || m_bsel==4)
		{
			m_Draw.Axes.Item(2).SetMinMax(-1,2000);
			m_Draw.Axes.Item(3).SetMinMax(-1,2000);
		}
	}
}

void CDlgHisData::CursorChangeCwgraph2(long* CursorIndex, VARIANT* XPos, VARIANT* YPos, BOOL* bTracking)
{
	// TODO: 在此处添加消息处理程序代码

	double XPos1;
	double YPos1;
	double XPos2;
	double YPos2;

	if (*CursorIndex ==1)
	{
		//m_xPos1.SetValue(XPos->dblVal);
	//	m_yPos1.SetValue(YPos->dblVal);
		XPos1=XPos->dblVal;
		YPos1=YPos->dblVal;
		XPos2 = m_Draw.GetCursors().Item(1).GetXPosition();
		YPos2 = m_Draw.GetCursors().Item(1).GetYPosition();
	}


	CString str;
	str.Format("       x:%0.2f  y:%0.2f",XPos1,YPos1);
	m_Draw.Annotations.Item(1).Caption.Text =str;

	m_Draw.Annotations.Item(1).Caption.Color = RGB(0,255,0);
	m_Draw.Annotations.Item(1).Caption.SetCoordinates(XPos1,YPos1);
}


