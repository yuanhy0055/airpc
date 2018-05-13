// TestSys.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "TestSys.h"
#include "TestSysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestSysApp

BEGIN_MESSAGE_MAP(CTestSysApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestSysApp 构造

CTestSysApp::CTestSysApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	handcur= NULL;
	for (int i=0;i<6;i++)
	{
		for (int j=0;j<4;j++)
		{

			dread[i][j] = 0.0;
		}
	}
	for(int i=0;i<24;i++)
	{
		i_dwcunz[i] = 0;//判断点位中是否有存在
		i_dwmode[i] = 0;//记录每一个点位上的数据模式
	}
	namestr[0] = "点位1-Ο2";
	namestr[1] = "点位1-No2";
	namestr[2] = "点位1-EX";
	namestr[3] = "点位1-UDMH";
	namestr[4] = "点位2-Ο2";
	namestr[5] = "点位2-No2";
	namestr[6] = "点位2-EX";
	namestr[7] = "点位2-UDMH";
	namestr[8]  = "点位3-Ο2";
	namestr[9]  = "点位3-No2";
	namestr[10] = "点位3-EX";
	namestr[11] = "点位3-UDMH";
	namestr[12] = "点位4-Ο2";
	namestr[13] = "点位4-No2";
	namestr[14] = "点位4-EX";
	namestr[15] = "点位4-UDMH";
	namestr[16] = "点位5-Ο2";
	namestr[17] = "点位5-No2";
	namestr[18] = "点位5-EX";
	namestr[19] = "点位5-UDMH";
	namestr[20] = "点位6-Ο2";
	namestr[21] = "点位6-No2";
	namestr[22] = "点位6-EX";
	namestr[23] = "点位6-UDMH";
}


// 唯一的一个 CTestSysApp 对象

CTestSysApp theApp;


// CTestSysApp 初始化

BOOL CTestSysApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();
//	SetDialogBkColor(RGB(0,0,255),RGB(255,0,0));
	
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	m_readini = GetApplicationPath()+_T("//list.ini");

	CString strocx = GetApplicationPath()+_T("//MSCOMM32.OCX");
	RegisterOcx(strocx);
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	CTestSysDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}
CString CTestSysApp::GetApplicationPath(void)
{
	CString strRet="";
	char cExeFileName[512];
	memset(cExeFileName,0,512);
	if(::GetModuleFileName(NULL,cExeFileName,512)==0)//结果包括路径及 EXE 文件名称
		return strRet;
	///////删除文件名称部份///////
	int len=lstrlen(cExeFileName);
	int nLastIndex=-1; //最后一个反斜杠的位置，该位置后即为文件名称
	for(int ls=0;ls<len;ls++)
	{
		if(cExeFileName[ls]=='\\')
			nLastIndex=ls;
	}
	if(nLastIndex <= 0)
		return strRet;
	cExeFileName[nLastIndex]=0; //截断字符串
	strRet=cExeFileName;//char数组----->CString型
	return strRet;
}
unsigned char CTestSysApp::Verify_Add(unsigned char *buffer, int len,int start,int end)
{
	int i = 0;
	unsigned char res = 0;
	for(i=start;i<end;i++)
		res += buffer[i];
	return res;
}

int CTestSysApp::Str2Hex(CString str, unsigned char* senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0; 
	int len=str.GetLength(); 
	//senddata.SetSize(len/2);
	for(int i=0;i<len;) 
	{   
		char lstr,hstr=str[i];  
		if(hstr==' ') 
		{      i++;  
		continue;  
		}    i++; 
		if(i>=len)  
			break;  
		lstr=str[i];    
		hexdata=ConvertHexChar(hstr);  
		lowhexdata=ConvertHexChar(lstr); 
		if((hexdata==16)||(lowhexdata==16))   
			break; 
		else     
			hexdata=hexdata*16+lowhexdata; 
		i++;   
		senddata[hexdatalen]=(UCHAR)hexdata; 
		hexdatalen++;
	}
	//senddata.SetSize(hexdatalen); 
	return hexdatalen;
}
char CTestSysApp::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9')) 
		return ch-0x30;  
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10; 
	else if((ch>='a')&&(ch<='f'))  
		return ch-'a'+10;
	else return (-1);
}
BOOL CTestSysApp::RegisterOcx(LPCTSTR OcxFileName)
{

	LPCTSTR pszDllName = OcxFileName ;         //ActiveX控件的路径及文件名         

	HINSTANCE hLib = LoadLibrary(pszDllName); //装载ActiveX控件

	if (hLib < (HINSTANCE)HINSTANCE_ERROR)

	{

		return FALSE ;

	}

	FARPROC lpDllEntryPoint; 

	lpDllEntryPoint = GetProcAddress(hLib,_T("DllRegisterServer"));   //获取注册函数DllRegisterServer地址



	if(lpDllEntryPoint!=NULL)   //调用注册函数DllRegisterServer

	{

		if(FAILED((*lpDllEntryPoint)()))

		{

			FreeLibrary(hLib);

			return FALSE ;

		}

		return TRUE ;

	}

	else

		return FALSE ;

}