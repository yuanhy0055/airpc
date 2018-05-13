// HzGL.cpp: implementation of the CHzGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HzGL.h"
#include <gl\gl.h>
#include <gl\glu.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHzGL::CHzGL()
{
	m_iDisplayListStart1=1000;
	m_iDisplayListStart2=2000;
	m_angle.cx = 0 ;//������ת�Ƕȳ�ֵ
	m_angle.cy = 0 ;//������ת�Ƕȳ�ֵ 
	m_theString =  " �๦��������ϵͳ ";
	m_String="";
}

bool CHzGL::Create(CWnd* pWnd)
{
		int iPixelType=	PFD_TYPE_RGBA;
		DWORD dwFlags=	PFD_DOUBLEBUFFER   | // ʹ��˫������
						PFD_SUPPORT_OPENGL | // ʹ�� OpenGL
						PFD_DRAW_TO_WINDOW;  // ����������ʽ
	
	//����ͼ�α���������ʽ�ṹ
	PIXELFORMATDESCRIPTOR pfd ;
	memset(&pfd,0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  
	pfd.nVersion = 1 ;                           // �汾��
	pfd.dwFlags =  dwFlags ;					//��������������
	pfd.iPixelType = iPixelType ;
	pfd.cColorBits = 24 ;						// 24 λ��ɫ
	pfd.cDepthBits = 32 ;						// 32-bit ��ɫŨ�Ȼ�����
	pfd.iLayerType = PFD_MAIN_PLANE ;           // Layer type
	
	m_pdc = new CClientDC(pWnd);
	//����TrueType���壬����ʵ����Ҫ�����ÿ��塢���������
	LOGFONT lf;
	m_pdc->GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet=134;
	strcpy(lf.lfFaceName, "����") ;  
	fontOpenGL1.CreateFontIndirect(&lf);
	strcpy(lf.lfFaceName, "����") ;  
	fontOpenGL2.CreateFontIndirect(&lf);
	
	//ѡ�����豸��������DC���ӽ������ظ�ʽ
	int nPixelFormat = ChoosePixelFormat(m_pdc->m_hDC, &pfd);
	if (nPixelFormat == 0)
	{
		AfxMessageBox("ChoosePixelFormat Failed %d\r\n",GetLastError()) ;
		return false;
	}
	
	// �������豸��������DC���ӽ������ظ�ʽ
	BOOL bResult = SetPixelFormat(m_pdc->m_hDC, nPixelFormat, &pfd);
	if (!bResult)
	{
		AfxMessageBox("SetPixelFormat Failed %d\r\n",GetLastError()) ;
		return false;
	}
	
	
	//
	// ����OpenGL��ͼ������-ͼ�β���������(rendering context)
	//
	m_hrc = wglCreateContext(m_pdc->m_hDC);
	if (!m_hrc)
	{
		AfxMessageBox("wglCreateContext Failed %x\r\n", GetLastError()) ;
		return false;
	}
	
	//ָ��rendering context
   	if(!wglMakeCurrent(m_pdc->m_hDC, m_hrc))
	{
		AfxMessageBox("wglMakeCurrent Failed %x\r\n", GetLastError()) ;
		return false;
	}
	//���ó�Ա˽�к���-OpenGL��ʼ��
	if(OnInit()) return true;
	else return false;
}

bool CHzGL::OnInit()
{
	// ������ɫŨ��
	glEnable(GL_DEPTH_TEST);  	
	
	// ����ǰ��ɫΪ������ɫ
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;
	
	// ���ù���λ��
	float fLightPosition[3] = {-1.0f, -1.0f, 1.0f} ;
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition) ;
	
	// ��������Դ
	glEnable(GL_LIGHTING) ; 		
	glEnable(GL_LIGHT0) ;			
	
	// ������Ļ��ɫ
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;//���õ�ɫΪ��ɫ
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f) ;//���õ�ɫΪ��ɫ
	//float customColor=127/255;
	glClearColor(0.0f,0.5f,0.5f,0.0f);
	Create3DFont(); 
	return true ;
}


void CHzGL::Create3DFont()
{
	int i=0; 
	CFont* pOldFont=(CFont*)m_pdc->SelectObject(&fontOpenGL1);
	
	// ������ʾ�б�.
	unsigned int j=0; 
	i=0; 
	j=0; 
	while(i< m_theString.GetLength())
	{
		if (IsDBCSLeadByte(m_theString[i])){ //�� �� �� �� Ϊ ˫ �� �� 
			wglUseFontOutlines(m_pdc->m_hDC, // ��ѡ������豸������
				(256+m_theString[i])*256+(256+m_theString[i+1]),// Ҫת��Ϊ��ʾ�б�ĵ�һ���ַ� 
				1, //  ת��Ϊ��ʾ�б���ַ�����
				m_iDisplayListStart1+j, // ָ������ʾ�б���� 
				0.0,// ָ�������ƫ��ֵ��һ��Ϊ0 
				0.15f, // �����������������֣�Z�ᣨ����򣩷����ֵ
				WGL_FONT_POLYGONS,// ��ʾ�����������߸�ʽ�������-ʵ�� 
				&m_agmf1[j]); // �����ַ�����
			FTextList[j]=j; 
			j++; 
			i++;i++; 
		} 
		else{ 
			wglUseFontOutlines(m_pdc->m_hDC, // ��ѡ������豸������
				m_theString[i], // Ҫת��Ϊ��ʾ�б�ĵ�һ���ַ� 
				1, //  ת��Ϊ��ʾ�б���ַ�����
				m_iDisplayListStart1+j, // ָ������ʾ�б���� 
				0.0,// ָ�������ƫ��ֵ��һ��Ϊ0 
				0.15f, // �����������������֣�Z�ᣨ����򣩷����ֵ
				WGL_FONT_POLYGONS,// ��ʾ�����������߸�ʽ�������-ʵ�� 
				&m_agmf1[j]); // �����ַ�����
			FTextList[j]=j; 
			i++; 
			j++; 
		} 
	} 
	
	m_pdc->SelectObject(&fontOpenGL2);	
	i=0; 
	j=0; 
    while(i<m_String.GetLength())
	{
		if (IsDBCSLeadByte(m_String[i])){ ///�� �� �� �� Ϊ ˫ �� �� 
			wglUseFontOutlines(m_pdc->m_hDC,// ��ѡ������豸������ 
				(256+m_theString[i])*256+(256+m_theString[i+1]),// Ҫת��Ϊ��ʾ�б�ĵ�һ���ַ� 
				1, //  ת��Ϊ��ʾ�б���ַ�����
				m_iDisplayListStart2+j, // ָ������ʾ�б���� 
				0.0,// ָ�������ƫ��ֵ��һ��Ϊ0 
				0.15f, // �����������������֣�Z�ᣨ����򣩷����ֵ
				WGL_FONT_POLYGONS,// ��ʾ�����������߸�ʽ�������-ʵ�� 
				&m_agmf2[j]); // �����ַ�����
			FTextList[j]=j; 
			j++; 
			i++;i++; 
		} 
		else{ 
			wglUseFontOutlines(m_pdc->m_hDC, // ��ѡ������豸������
				m_theString[i], // Ҫת��Ϊ��ʾ�б�ĵ�һ���ַ� 
				1, //  ת��Ϊ��ʾ�б���ַ�����
				m_iDisplayListStart2+j, // ָ������ʾ�б���� 
				0.0,// ָ�������ƫ��ֵ��һ��Ϊ0 
				0.15f, // �����������������֣�Z�ᣨ����򣩷����ֵ
				WGL_FONT_POLYGONS,// ��ʾ�����������߸�ʽ�������-ʵ�� 
				&m_agmf2[j]); // �����ַ�����
			FTextList[j]=j; 
			i++; 
			j++; 
		} 
	} 
	
	
	
	if (pOldFont) m_pdc->SelectObject(pOldFont) ;
	
}

CHzGL::~CHzGL()
{
	if (m_hrc) 
	{
		// ɾ��ͼ�β���������
		if (m_hrc == wglGetCurrentContext())
			wglMakeCurrent(NULL,NULL) ; 
		wglDeleteContext(m_hrc) ;
		m_hrc = NULL ;
	}
	
	delete m_pdc;
	
}

bool CHzGL::Render()
{
	// Make the HGLRC current
	wglMakeCurrent(m_pdc->m_hDC, m_hrc);
	//��һ���ַ�����ɫ
	static GLdouble purple[3] = {3, 3, 3} ; 
	
	//�ڶ����ַ����ĸ����岻ͬ��ɫ
	static GLubyte byPink[3] = {196, 0, 196} ;
	static GLubyte byTeal[3] = {0, 153, 168} ;
	static GLubyte byBlue[3] = {42, 38, 215} ;
	static GLubyte byGreen[3] = {0, 171, 82} ;
	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//��ʾ��һ�к���
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glTranslated(-2.10,-0.1,-5.0 );//����λ��X,Y,�����С
	//glRotated(m_angle.cy, 0.0, 1.0, 0.0);
	//glRotated(m_angle.cx, 0, 0, 0);//  ��ת�Ƕ�X��Y��Z
	
	glColor3dv(purple) ;
	glListBase(m_iDisplayListStart1); 
	glCallLists(m_theString.GetLength(),GL_UNSIGNED_BYTE,&FTextList); 
	
	//��ʾ�ڶ��к���
	double widthMN = (m_agmf2[0].gmfCellIncX + m_agmf2[3].gmfCellIncX) * 0.5 ;
	
	glLoadIdentity();
	glTranslated(0.0, -0.0, -0.0 );
	glRotated(m_angle.cy, 0.0, 0.0, 0.0);
	glTranslated(-widthMN, 0.0, 0.0) ;
	
	glScaled(0.0, 0.0, 0) ;
	glColor3ubv(byPink) ;
	glCallList(m_iDisplayListStart2) ;
	glColor3ubv(byTeal) ;
	glCallList(m_iDisplayListStart2+1) ;
	glColor3ubv(byBlue) ;			   
	glCallList(m_iDisplayListStart2+2) ;
	glColor3ubv(byGreen) ;
	glCallList(m_iDisplayListStart2+3) ;
	glFlush() ;
	GdiFlush() ;
	SwapBuffers(m_pdc->m_hDC) ;
	GdiFlush() ;
	spin();//���ó�Ա˽�к�������ת����
	return true;
}
BOOL CHzGL::OnResize(int cx, int cy)
{
	GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//����͸�ӷ������
	gluPerspective(30.0, gldAspect, 1.0, 10.0);
	glViewport(0, 0, cx, cy);
	
	return TRUE ;
}

BOOL CHzGL::spin()//��ת����
{
	m_angle.cx += 10 ;
	m_angle.cy += 10 ;
	if (m_angle.cx >= 360) m_angle.cx = 0 ;
	if (m_angle.cy >= 360) m_angle.cy = 0 ;
	return 0;
}

