// TestSys.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������
//#include "cnComm.h"

// CTestSysApp:
// �йش����ʵ�֣������ TestSys.cpp
//

class CTestSysApp : public CWinApp
{
public:
	CTestSysApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:


	BOOL RegisterOcx(LPCTSTR OcxFileName);
	CString GetApplicationPath(void);
	unsigned char Verify_Add(unsigned char *buffer, int len,int start,int end);
	CString m_readini;

	CString namestr[24];
	int i_dwcunz[24];//�жϵ�λ���Ƿ��д���
	UCHAR i_dwmode[24];//��¼ÿһ����λ�ϵ�����ģʽ
	int i_state[24][4];//��λ״̬
	int i_dwIndex[24][4];//��λ������
	int timernum;//��ʱ����
	int m_index;
	char ConvertHexChar(char ch);
	int Str2Hex(CString str, unsigned char* senddata);
	HWND handcur;
	double dread[24][4];

};

extern CTestSysApp theApp;
