// DlgCurve.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgCurve.h"
#include ".\dlgcurve.h"


// CDlgCurve 对话框

IMPLEMENT_DYNAMIC(CDlgCurve, CDialog)
CDlgCurve::CDlgCurve(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCurve::IDD, pParent)
{
	btime = FALSE;
}

CDlgCurve::~CDlgCurve()
{
}

void CDlgCurve::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWGRAPH1, m_graph);
	DDX_Control(pDX, IDC_CMBSELDW, m_cmbseldw);
}


BEGIN_MESSAGE_MAP(CDlgCurve, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_DRAW,OnmyDraw)
	ON_CBN_SELCHANGE(IDC_CMBSELDW, OnCbnSelchangeCmbseldw)
END_MESSAGE_MAP()


// CDlgCurve 消息处理程序

BOOL CDlgCurve::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_graph.Axes.Item(1).SetMinMax(0,100);
	m_graph.Axes.Item(2).SetMinMax(0,10);
	m_num = 0;	
	m_sys = 0;
	readnum = 0;

	for (int i=0;i<96;i++)
	{
		m_graph.GetPlots().Item(i+1).SetVisible(0);
	}
	//m_graph.Annotations.Add();
	//m_graph.Annotations.Item(1).SnapMode = CNiAnnotation::SnapAnchoredToPoint;
	//m_graph.Annotations.Item(1).Shape.Type = CNiShape::Point;
	//m_graph.Annotations.Item(1).Caption.Color = RGB(255,0,0);
	//m_graph.Annotations.Item(1).Enabled = true;
	//m_graph.Annotations.Item(1).Visible = true;
	theApp.handcur = this->m_hWnd;

	return TRUE;

}


double randDbl(double a,double b)
{
	return a + static_cast<double>(rand())/RAND_MAX*(b-a);
}
void CDlgCurve::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent==0)
	{
		OnShowLine();
	}
	CDialog::OnTimer(nIDEvent);
}


void CDlgCurve::SetOnInit(void)
{
	CString m_strsel;
	char strBuff[20];
	CString strValue ;
	int state,m_sel;
	int j = 0;
	m_sel = m_cmbseldw.GetCount();
	for (int i =0;i<m_sel;i++)
	{
		m_cmbseldw.DeleteString(0);
	}
	for (int k=0;k<24;k++)
	{
		for(int i=0;i<4;i++)
		{
			if(theApp.i_state[k][i]!=0)//theApp.i_selport[i]!=0)// && 
			{
		
				m_strsel.Format("PORT%d",k*4+i+1);
				state = GetPrivateProfileInt(m_strsel,"show",0,theApp.m_readini);
				if (state == 1)
				{
					GetPrivateProfileString(m_strsel,"num",NULL,strBuff,20,theApp.m_readini); 
					strValue = strBuff;
					m_cmbseldw.InsertString(j,strValue);
					m_numw[j] = k*4+i;
					j++;
				}

				
			}
		}
	}


}
void CDlgCurve::OnCbnSelchangeCmbseldw()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = m_cmbseldw.GetCurSel();
	m_selline = m_numw[sel]+1;
	int m_cs = m_numw[sel]/4;
	int m_ys = m_numw[sel]%4;
	//if (m_numw[sel]==0 ||m_numw[sel]==4||m_numw[sel]==8 ||m_numw[sel]==12||m_numw[sel]==16 ||m_numw[sel]==20)
	if (m_ys == 0)
	{
		m_graph.Axes.Item(2).SetMinMax(0,30);
		m_graph.Axes.Item(3).SetMinMax(0,30);
	}
	//if (m_numw[sel]==1 ||m_numw[sel]==5||m_numw[sel]==9 ||m_numw[sel]==13||m_numw[sel]==17 ||m_numw[sel]==21)
	if (m_ys == 1)
	{
		m_graph.Axes.Item(2).SetMinMax(0,2000);
		m_graph.Axes.Item(3).SetMinMax(0,2000);
	}
	
	//if (m_numw[sel]==2 ||m_numw[sel]==6||m_numw[sel]==10 ||m_numw[sel]==14||m_numw[sel]==18 ||m_numw[sel]==22)
	if (m_ys == 2)
	{
		m_graph.Axes.Item(2).SetMinMax(0,100);
		m_graph.Axes.Item(3).SetMinMax(0,100);
	}
	//if (m_numw[sel]==3 ||m_numw[sel]==7||m_numw[sel]==11 ||m_numw[sel]==15||m_numw[sel]==19 ||m_numw[sel]==23)
	if (m_ys == 3)
	{
		m_graph.Axes.Item(2).SetMinMax(0,2000);
		m_graph.Axes.Item(3).SetMinMax(0,2000);
	}
}
LRESULT CDlgCurve::OnmyDraw(WPARAM wparam,LPARAM lParam)
{

	CString str;
	if (btime == FALSE)
	{
		btime = TRUE;
		CTime cTime = CTime::GetCurrentTime();  
		CString strTime;  
		//字符串格式化时间   
		//strTime.Format("开始时间 %d:%d:%d",cTime.GetHour(),cTime.GetMinute(),cTime.GetSecond()); 
		//strTime=cTime.Format("%H-%M-%S");
		strTime = cTime.Format("开始时间 %H时%M分%S秒"); 
		GetDlgItem(IDC_STATICTIME)->SetWindowText(strTime);
		SetTimer(0,theApp.timernum,NULL);
	} 
	return 0;
}


void CDlgCurve::OnShowLine()
{
	CString str;
	CNiReal64Vector plotData(96);
	for (int i=0;i<24;i++)
	{
		for (int j=0;j<4;j++)
		{
			plotData[i*4+j] = theApp.dread[i][j];
		}
	}

	//for (int i=0;i<24;i++)
	//{
	//	m_graph.GetPlots().Item(i+1).SetVisible(0);
	//	m_graph.GetPlots().Item(i+1).ChartY(plotData[i]);
	//}
	//plotData[2] = plotData[0];
	for (int i=0;i<96;i++)
	{
		m_graph.GetPlots().Item(i+1).SetVisible(0);
		m_graph.GetPlots().Item(i+1).ChartY(plotData[i]);
	}
	if (m_selline>0&&m_selline<=96)
	{
		
		m_graph.GetPlots().Item(m_selline).SetVisible(1);

	}
	//str.Format("%d",readnum);
	//GetDlgItem(IDC_STATICTIME)->SetWindowText(str);
	//readnum++;
}
