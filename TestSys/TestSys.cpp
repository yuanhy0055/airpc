// TestSys.cpp : ����Ӧ�ó��������Ϊ��
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


// CTestSysApp ����

CTestSysApp::CTestSysApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
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
		i_dwcunz[i] = 0;//�жϵ�λ���Ƿ��д���
		i_dwmode[i] = 0;//��¼ÿһ����λ�ϵ�����ģʽ
	}
	namestr[0] = "��λ1-��2";
	namestr[1] = "��λ1-No2";
	namestr[2] = "��λ1-EX";
	namestr[3] = "��λ1-UDMH";
	namestr[4] = "��λ2-��2";
	namestr[5] = "��λ2-No2";
	namestr[6] = "��λ2-EX";
	namestr[7] = "��λ2-UDMH";
	namestr[8]  = "��λ3-��2";
	namestr[9]  = "��λ3-No2";
	namestr[10] = "��λ3-EX";
	namestr[11] = "��λ3-UDMH";
	namestr[12] = "��λ4-��2";
	namestr[13] = "��λ4-No2";
	namestr[14] = "��λ4-EX";
	namestr[15] = "��λ4-UDMH";
	namestr[16] = "��λ5-��2";
	namestr[17] = "��λ5-No2";
	namestr[18] = "��λ5-EX";
	namestr[19] = "��λ5-UDMH";
	namestr[20] = "��λ6-��2";
	namestr[21] = "��λ6-No2";
	namestr[22] = "��λ6-EX";
	namestr[23] = "��λ6-UDMH";
}


// Ψһ��һ�� CTestSysApp ����

CTestSysApp theApp;


// CTestSysApp ��ʼ��

BOOL CTestSysApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
//	SetDialogBkColor(RGB(0,0,255),RGB(255,0,0));
	
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	m_readini = GetApplicationPath()+_T("//list.ini");

	CString strocx = GetApplicationPath()+_T("//MSCOMM32.OCX");
	RegisterOcx(strocx);
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	CTestSysDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
CString CTestSysApp::GetApplicationPath(void)
{
	CString strRet="";
	char cExeFileName[512];
	memset(cExeFileName,0,512);
	if(::GetModuleFileName(NULL,cExeFileName,512)==0)//�������·���� EXE �ļ�����
		return strRet;
	///////ɾ���ļ����Ʋ���///////
	int len=lstrlen(cExeFileName);
	int nLastIndex=-1; //���һ����б�ܵ�λ�ã���λ�ú�Ϊ�ļ�����
	for(int ls=0;ls<len;ls++)
	{
		if(cExeFileName[ls]=='\\')
			nLastIndex=ls;
	}
	if(nLastIndex <= 0)
		return strRet;
	cExeFileName[nLastIndex]=0; //�ض��ַ���
	strRet=cExeFileName;//char����----->CString��
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

	LPCTSTR pszDllName = OcxFileName ;         //ActiveX�ؼ���·�����ļ���         

	HINSTANCE hLib = LoadLibrary(pszDllName); //װ��ActiveX�ؼ�

	if (hLib < (HINSTANCE)HINSTANCE_ERROR)

	{

		return FALSE ;

	}

	FARPROC lpDllEntryPoint; 

	lpDllEntryPoint = GetProcAddress(hLib,_T("DllRegisterServer"));   //��ȡע�ắ��DllRegisterServer��ַ



	if(lpDllEntryPoint!=NULL)   //����ע�ắ��DllRegisterServer

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