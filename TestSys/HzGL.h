// HzGL.h: interface for the CHzGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_)
#define AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHzGL  
{
public:
	CHzGL();
	~CHzGL();
	bool Render() ;
	bool Create(CWnd* pWnd); 
	int OnResize(int cx, int cy);//���ڴ�С�����仯ʱ����

private:
	
	int spin();//��ת����
	bool OnInit() ;
	CString m_theString ;
	CString m_String;
	BYTE FTextList[128]; 
	void Create3DFont() ;
	CDC* m_pdc;
	// �����������Ե�λ�úͷ���...
	GLYPHMETRICSFLOAT m_agmf1[128]; 
	GLYPHMETRICSFLOAT m_agmf2[40] ;
	//����OPenGL��ʾ������
	CFont fontOpenGL1,fontOpenGL2;
	CSize m_angle;//��ת�Ƕ�0-360
	HGLRC m_hrc ; //OpenGL Rendering Context
	int m_iDisplayListStart1;
	int m_iDisplayListStart2;
};

#endif // !defined(AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_)
