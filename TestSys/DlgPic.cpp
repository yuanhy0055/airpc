// DlgPic.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSys.h"
#include "DlgPic.h"
#include ".\dlgpic.h"


// CDlgPic 对话框
CString str_SEC[6] = {"SECTION 1","SECTION 2","SECTION 3","SECTION 4","SECTION 5","SECTION 6"};
IMPLEMENT_DYNAMIC(CDlgPic, CDialog)
CDlgPic::CDlgPic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPic::IDD, pParent)
{
}

CDlgPic::~CDlgPic()
{
}

void CDlgPic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Cmbdw);
}


BEGIN_MESSAGE_MAP(CDlgPic, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_DESTROY()
//	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgPic 消息处理程序
BOOL CDlgPic::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	dwtotal = 0;

	GetDlgItem(IDC_STATICIMG)->MoveWindow(10,44,970,550);
	m_strini =theApp.GetApplicationPath() + _T("//ZB.ini");
	image1 = NULL;
	//image1 = cvLoadImage("12.jpg",1);
	
	//image2 = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,3);
	for (int i=0;i<24;i++)
	{
		center[i].x=0;//GetPrivateProfileInt(str_SEC[i],"X1",0,m_strini);
		center[i].y=0;//GetPrivateProfileInt(str_SEC[i],"Y1",0,m_strini);
	}
	
	//center.x =100;
	//center.y=100;

	
	cvInitFont( &font, CV_FONT_HERSHEY_PLAIN ,1, 1, 0, 1, 1);
	selp = 0;
	bset = FALSE;
	return TRUE;
}
void CDlgPic::SetInitCtrl()
{
	CString str;
	int m_sel = m_Cmbdw.GetCount();
	dwtotal = 0;
	for (int i =0;i<m_sel;i++)
	{
		m_Cmbdw.DeleteString(0);
	}
	for (int k=0;k<24;k++)
	{
		if(theApp.i_dwcunz[k]!=0)//theApp.i_selport[i]!=0)// && 
		{
			str.Format("Site%d",k+1);
			m_Cmbdw.InsertString(dwtotal,str);
			mpos[dwtotal] = k;
			dwtotal++;
		}
	}
}
void CDlgPic::DrawPicToHdc(IplImage *img, UINT ID)
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
void CDlgPic::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CvScalar colors = {255,0,0};
	CString temp = "";
	CvPoint zuobao1,zuobao2;
	CvPoint pp,pp2;
	pp.x=10;
	pp.y=40;
	CvRect roi;
	cvCopy(image1,image2);
	cvCopy(pic,pic2);
	char *p ;
	for (int i =0;i<dwtotal;i++)
	{
		p = (LPSTR)(LPCTSTR)temp;
//
		


		if ((selp-1)==i)
		{			
			roi.x = center[i].x;
			roi.y = center[i].y;

			if (center[i].x>(image1->width-100))
			{

				roi.x = center[i].x-pic2->width;
				roi.y = center[i].y-pic->height;
			}
			if (center[i].y>(image1->height-100))
			{
				roi.x = center[i].x-pic2->width;
				roi.y = center[i].y-pic->height;
			}
			//if (center[i].x>(image1->width-160)&&center[i].y<(image1->height-160))
			//{
			//	roi.x = center[i].x-pic->width;
			//	roi.y = center[i].y-pic->height;
			//}

			roi.width = pic2->width;
			roi.height = pic2->height;
			cvSetImageROI(image2, roi); 
			cvCopy(pic2, image2);
			cvResetImageROI(image2);
			//cvCircle( image2,center[i] , 5,CV_RGB(255,0,0), 3, 8, 0 );
		}
		else
		{
			roi.x = center[i].x;
			roi.y = center[i].y;

			roi.width = pic2->width;
			roi.height = pic2->height;
			if (center[i].x>(image1->width-100))
			{

				roi.x = center[i].x;
				roi.y = center[i].y-pic->height;

				roi.width = pic->width;
				roi.height = pic->height;
			}
			if (center[i].y>(image1->height-100))
			{
				roi.x = center[i].x;
				roi.y = center[i].y-pic->height;
			}
			//if (center[i].x>(image1->width-160)&&center[i].y<(image1->height-160))
			//{
			//	roi.x = center[i].x-pic->width;
			//	roi.y = center[i].y-pic->height;
			//}
			cvSetImageROI(image2, roi); 
			cvCopy(pic2, image2);
			cvResetImageROI(image2);
			//cvCircle( image2, center[i], 5,CV_RGB(0,255,0), 3, 8, 0 );
		}
		zuobao.x = center[i].x+pic->width+10;
		zuobao.y = center[i].y+13;
		pp2.x = center[i].x+pic->width;
		pp2.y = center[i].y;

		//if (center[i].y>(image1->height-160)&&center[i].x>(image1->width-160))
		//{
		//	zuobao.x = center[i].x-pic2->width-90;
		//	zuobao.y = center[i].y-pic2->height+10;
		//	pp2.x = center[i].x-pic2->width-170;
		//	pp2.y = center[i].y-pic2->height;

		//}
		if (center[i].y>(image1->height-100))
		{
			zuobao.x = center[i].x-pic2->width-100+10;
			zuobao.y = center[i].y-90+5;
			

			pp2.x = center[i].x-pic2->width-100;
			pp2.y = center[i].y-100;
		}
		if (center[i].x>(image1->width-100))
		{
			zuobao.x = center[i].x-pic2->width-100+10;
			zuobao.y = center[i].y-90+5;


			pp2.x = center[i].x-pic2->width-100;
			pp2.y = center[i].y-100;
		}



		zuobao1.x =pp2.x;
		zuobao1.y = pp2.y;
		zuobao2.x= pp2.x+100;
		if (theApp.i_dwmode[mpos[i]]==0x01)
		{	
			zuobao2.y= pp2.y+90;
			cvRectangle( image2, zuobao1,zuobao2,CV_RGB(0,0,0), -1, 8, 0 );
			temp.Format("Site%d:",mpos[i]+1);
			p = (LPSTR)(LPCTSTR)temp;
			cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			if (theApp.i_state[mpos[i]][0]==1)
			{
				temp.Format("O2-%.2f",theApp.dread[mpos[i]][0]);
				p = (LPSTR)(LPCTSTR)temp;
				zuobao.y = pp2.y+30;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
			if (theApp.i_state[mpos[i]][1]==1)
			{
				temp.Format("NO2-%.2f",theApp.dread[mpos[i]][1]);
				zuobao.y = pp2.y+50;
				p = (LPSTR)(LPCTSTR)temp;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
			//temp.Format("dw%d O2-%.2f,NO2-%.2f",mpos[i]+1,theApp.dread[mpos[i]][0],theApp.dread[mpos[i]][1]);
			//p = (LPSTR)(LPCTSTR)temp;
			//cvPutText(image2,p,zuobao,&font,cvScalar(255,0,0));
			
		}
		else if (theApp.i_dwmode[mpos[i]]==0x02)
		{	
			zuobao2.y= pp2.y+90;
			cvRectangle( image2, zuobao1,zuobao2,CV_RGB(0,0,0), -1, 8, 0 );

			temp.Format("Site%d:",mpos[i]+1);
			p = (LPSTR)(LPCTSTR)temp;
			cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			if (theApp.i_state[mpos[i]][0]==1)
			{   

				temp.Format("O2-%.2f",theApp.dread[mpos[i]][0]);
				p = (LPSTR)(LPCTSTR)temp;

				zuobao.y = pp2.y+30;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
			if (theApp.i_state[mpos[i]][2]==1)
			{
				temp.Format("EX-%.2f",theApp.dread[mpos[i]][2]);
				p = (LPSTR)(LPCTSTR)temp;
				zuobao.y = pp2.y+50;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}

			if (theApp.i_state[mpos[i]][3]==1)
			{
				temp.Format("UDMH-%.2f",theApp.dread[mpos[i]][3]);
				zuobao.y = pp2.y+70;
				p = (LPSTR)(LPCTSTR)temp;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
		}
		else if (theApp.i_dwmode[mpos[i]]==0x03)
		{	

			zuobao2.y= pp2.y+90;
			cvRectangle( image2, zuobao1,zuobao2,CV_RGB(0,0,0), -1, 8, 0 );
			temp.Format("Site%d:",mpos[i]+1);
			p = (LPSTR)(LPCTSTR)temp;
			cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			if (theApp.i_state[mpos[i]][0]==1)
			{
				temp.Format("O2-%.2f",theApp.dread[mpos[i]][0]);
				p = (LPSTR)(LPCTSTR)temp;
				zuobao.y = pp2.y+30;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
			if (theApp.i_state[mpos[i]][1]==1)
			{
				temp.Format("NO2-%.2f",mpos[i]+1,theApp.dread[mpos[i]][1]);
				zuobao.y = pp2.y+50;
				p = (LPSTR)(LPCTSTR)temp;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
			if (theApp.i_state[mpos[i]][2]==1)
			{
				temp.Format("EX-%.2f",theApp.dread[mpos[i]][2]);
				zuobao.y = pp2.y+70;
				p = (LPSTR)(LPCTSTR)temp;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}

			if (theApp.i_state[mpos[i]][3]==1)
			{
				temp.Format("UDMH-%.2f",theApp.dread[mpos[i]][3]);
				zuobao.y = pp2.y+90;
				p = (LPSTR)(LPCTSTR)temp;
				cvPutText(image2,p,zuobao,&font,cvScalar(0,255,0));
			}
		}
	}
	DrawPicToHdc(image2,IDC_STATICIMG);
}

void CDlgPic::OnDestroy()
{
	if (image1!=NULL)
	{
		cvReleaseImage(&image1);
		cvReleaseImage(&image2);
		cvReleaseImage(&pic);
		cvReleaseImage(&pic2);
	}

	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CDlgPic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (selp>0 && bset == TRUE)
	{
		center[selp-1].x=(int)(point.x*(image1->width)/970);
		center[selp-1].y=(int)(point.y*(image1->height)/550);
		if (center[selp-1].x>image1->width)
		{
			center[selp-1].x = image1->width-10;
		}
		if (center[selp-1].y>image1->height)
		{
			center[selp-1].y = image1->height-10;
		}

   }
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPic::OnCloseTime()
{
//	KillTimer(0);
}
void CDlgPic::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent==0)
	{
		OnBnClickedButton1();
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgPic::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (bset == FALSE)
	{
		bset = TRUE;
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CDlgPic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	bset = FALSE;
	//KillTimer(0);
	CDialog::OnRButtonUp(nFlags, point);
}

BOOL CDlgPic::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(pMsg->wParam)
	{
		case VK_LEFT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPic::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//KillTimer(0);
	int sel= m_Cmbdw.GetCurSel();
	selp = sel+1;
	
}

void CDlgPic::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sFileName;
		CFileDialog dlg(TRUE, "", sFileName,
			OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"文本文件(*)|*||", this);
		dlg.m_ofn.lpstrTitle = _T("导入数据");
		dlg.m_ofn.lpstrInitialDir= theApp.GetApplicationPath()+"\\SelPic"; //指定文件夹
		CString filename2 = theApp.GetApplicationPath()+"//icon.JPG";
		if (dlg.DoModal() == IDOK)
		{

			CString  filename;
			filename= dlg.GetPathName();
			image1 = cvLoadImage(filename,1);

			pic  =  cvLoadImage(filename2,1); 
			pic2 = cvCreateImage(cvGetSize(pic),IPL_DEPTH_8U,3);

			image2 = cvCreateImage(cvGetSize(image1),IPL_DEPTH_8U,3);
			OnBnClickedButton1();
			SetTimer(0,10,NULL);
		}
}

HBRUSH CDlgPic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (nCtlColor == CTLCOLOR_STATIC&& pWnd->GetDlgCtrlID() == IDC_STATICIMG)
	{
		COLORREF clr ;//= RGB(0,255,0);
		//pDC->SetTextColor(clr);   //设置红色的文本
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);     //设置黑色的背景
		hbr = ::CreateSolidBrush(clr);
		return hbr;  //作为约定，返回背景色对应的刷子句柄
	}
	else 
	return hbr;
}
