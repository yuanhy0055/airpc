// TestSys.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号
//#include "cnComm.h"

// CTestSysApp:
// 有关此类的实现，请参阅 TestSys.cpp
//

class CTestSysApp : public CWinApp
{
public:
	CTestSysApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
public:


	BOOL RegisterOcx(LPCTSTR OcxFileName);
	CString GetApplicationPath(void);
	unsigned char Verify_Add(unsigned char *buffer, int len,int start,int end);
	CString m_readini;

	CString namestr[24];
	int i_dwcunz[24];//判断点位中是否有存在
	UCHAR i_dwmode[24];//记录每一个点位上的数据模式
	int i_state[24][4];//点位状态
	int i_dwIndex[24][4];//点位的索引
	int timernum;//定时周期
	int m_index;
	char ConvertHexChar(char ch);
	int Str2Hex(CString str, unsigned char* senddata);
	HWND handcur;
	double dread[24][4];

};

extern CTestSysApp theApp;
