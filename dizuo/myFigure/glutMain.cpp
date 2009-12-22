//History:
//	[3/11/2009 RenYaFei]
//		������������ʾ
//		��ɫ���ã��͵ƹ��ںϡ�����
//  [3/14/2009 RenYaFei]
//		main������ѹ������
//  [3/15/2009 RenYaFei]
//		ʹ�ö��ӿڣ�û������ĸ��ӡ�����
//  [3/16/2009 RenYaFei]
//		������ѡȡ����

#include "util/Helper.h"
#include "Share.h"

#include "util/CTexture.h"
#include <gl/freeglut.h>

void		Init();
void		Display();
void		Reshape(int w, int h);
void		MotionCB(int x, int y);
void		MouseCB(int button, int state, int x, int y);
void		KeyBoardCB(unsigned char key, int x, int y);

void		SetOrthoProjectionViewportMain();		//App
void		SetOrthoProjectionViewportRight();		//App
void		ResetPerspectiveProjectionViewport();	//App

int main(int argc, char* argv[])
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (Share::getWindowWid(), Share::getWindowHeight());
	glutInitWindowPosition (100, 100);
	int window = glutCreateWindow ("Bvh Backer");
	
	Init();
	glutReshapeFunc ( Reshape );
	glutMouseFunc( MouseCB );
	glutMotionFunc( MotionCB );
	glutKeyboardFunc( KeyBoardCB );

	//glutMainLoop ();
	while ( Share::getRunFalg() )
	{
		glutMainLoopEvent();
		Display();
	}

	glutDestroyWindow(window);
	//����Ĳ����������ù�....
	//MainLoop���Ѿ�exit�ˣ�ʹ������һ������
	KeyboardManger::FreeInstance();
	MouseManger::FreeInstance();
	GUISystem::FreeInstance();
	CTimer::FreeInstance();
	CTextureManager::FreeInstance();
	Share::destroy();

	return 0;
} 

void Init()
{
	GLfloat light_position[] = {100.0f, 100.0f, 100.0f, 0.0f};
	GLfloat white_light[] = {253.0f/255.0f, 208.0f/255.0f, 1.0f, 1.0f};
	GLfloat yellow_light[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat lmodel_ambient[] = {0.0f, 0.7f, 0.5f, 1.0f};
	glClearColor(84/255.0f, 25.0f/255.0f, 125.0f/255.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_light);//�������ɫ
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);//�߹����ɫ
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

 	glEnable(GL_CULL_FACE);
 	glPolygonMode(GL_FRONT, GL_FILL);
 	glPolygonMode(GL_BACK, GL_FILL);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);							// ���÷�����
	
	//��ʼ����������	....
	GUISystem::GetInstance()->SetUp();

	//Figure��һϵ�г�ʼ��		....1
	Share::setFigure ( new Figure("data/KICK R.bvh") );
	Share::getFigure()->set_font_pos( GUISystem::GetInstance()->m_pInterface->GetRight().m_Left,
						   GUISystem::GetInstance()->m_pInterface->GetRight().m_Top + 35 );
	//g_Figure.process_file();	....2
	Share::getFigure()->recurs_read();
	Share::getFigure()->pre_recurs_print( Share::getFigure()->get_root(), 1 );
	Share::getFigure()->process_font( Share::getFigure()->get_root(), 1);
	Share::setFrameTimeMs( Share::getFigure()->get_frame_time()*1000 );

	//����Figure��frame number�������ý������Ĳ���		....3
	GUISystem::GetInstance()->m_pBar->setStepSize( 1024.0f/Share::getFigure()->get_frame_num() );

	//����ȫ�ֹ������	....
	Share::setTrack( new TrackUI );
	Share::getTrack()->SetWnd( Share::getWindowWid(), Share::getWindowHeight() );
	Share::setCamera( new DragCamera );
	Share::setHelpInfo( new TipsBoard(Share::getWindowWid(), Share::getWindowHeight()) );
}

void Display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//////////////////////////////////////////////////////////////////////////
	//					viewport 1: top, bottom, right						//
	SetOrthoProjectionViewportMain();
	glPushMatrix();
	{	
		GUISystem::GetInstance()->Render();
	}glPopMatrix();

	glPushMatrix();
	{
		Share::getHelpInfo()->showInfo();
	} glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//							viewport 2: right							//
	SetOrthoProjectionViewportRight();
	glPushMatrix();
	{
		//glColor4f(1.0, 1.0, 1.0, 1.0);	//set font color
		Share::getFigure()->font_container->Render();
	}glPopMatrix();
	
	//////////////////////////////////////////////////////////////////////////
	//							viewport 3: client							//
	ResetPerspectiveProjectionViewport();
	//glGetIntegerv (GL_VIEWPORT, g_iViewport);
	glPushMatrix();
	{	
		//��������ԭ�㻹��λ�ڴ�������
		//Camera->Apply()
		Share::getCamera()->apply();

		//Ground
		glPushMatrix();
		{
			glTranslatef(0.0, -30.0, 0.0);
			glColor4f(1.0f, 1.0f, 1.0f, 0.75);	//set ground color
			Helper::DrawNet(100, 20, 20);
		}glPopMatrix();	
		//Figure
		glPushMatrix();	
		{
			//ȫ��ת��
			// TrackBall->Apply();
			Share::getTrack()->Apply();
			//����...
			glColor4f(1.0f, 0.0f, 0.0f, 0.75f);		//set Figure��ɫ
			Share::getFigure()->render_figure(0.8f);
			glDisable(GL_CULL_FACE);	
		}glPopMatrix();
	}glPopMatrix();

	// ȡ��idle����
	Share::getFigure()->update();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport (0, 0, w, h);//viewport����ϵ�����½�

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(80.0, (float)w/h, 0.0001, 200.0);	

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void KeyBoardCB(unsigned char key, int x, int y)
{
	KeyboardManger::GetInstance()->OnKeyHandle(key, x, y);
	glutPostRedisplay();
}

void MouseCB(int button, int state, int x, int y)
{
	MouseManger::GetInstance()->OnMouseHandle(button, state, x, y);
	
	//�����ѡȡ�ڵ�,ע��Y����ת��
	if( cRECT.Intersect(x, y) )
		MouseManger::GetInstance()->PickJointByMouse(button, state, x, Share::getWindowHeight()-y);
	
	//�ұ߽ṹ��ѡȡ
	if( rRECT.Intersect(x, y) )
		MouseManger::GetInstance()->SelectJointByName(button, state, x, y);
}

void MotionCB(int x, int y)
{
	//��TrackBall������Client����
	if( cRECT.Intersect(x, y) )
		MouseManger::GetInstance()->OnMotionHandle(x, y);
}

void SetOrthoProjectionViewportMain()
{
	//���½�Ϊ(0,0)
	glViewport(0, 0, Share::getWindowWid(), Share::getWindowHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		//���Ͻ�Ϊ(0,0)
	glOrtho(0, Share::getWindowWid(), 0, Share::getWindowHeight(), -1.0, 1.0);	
		glScalef(1, -1, 1);						// ת��y���꣬����Ϊ��
		glTranslatef(0, -Share::getWindowHeight(), 0);	//������ԭ���Ƶ����Ͻ�
	glMatrixMode(GL_MODELVIEW);
}

//������ʾ�ұ����ṹ
void SetOrthoProjectionViewportRight()
{
	int view_x = rRECT.m_Left;
	int view_y = bRECT.GetHeight();
	int view_w = rRECT.GetWidth();
	int view_h = rRECT.GetHeight();
	glViewport(view_x, view_y, view_w, view_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		glOrtho(rRECT.m_Left, rRECT.m_Right, 
				rRECT.m_Bottom, rRECT.m_Top, -1.0, 1.0);	
		//glScalef(1, -1, 1);						// ת��y���꣬����Ϊ��
		//glTranslatef(0, - g_iWindowHeigh, 0);	//������ԭ���Ƶ����Ͻ�
	glMatrixMode(GL_MODELVIEW);
}

void ResetPerspectiveProjectionViewport()
{
	int view_x = cRECT.m_Left;
	int view_y = cRECT.m_Top;
	int view_w = cRECT.GetWidth();
	int view_h = cRECT.GetHeight();

	glViewport(view_x, view_y, view_w, view_h);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(80.0, view_w/view_h, 0.001, 500);
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}
//////////////////////////////////////////////////////////////////////////
//ʹ����freeglut��glutMainLoopEvent����
//////////////////////////////////////////////////////////////////////////
//Config��������:
//	ͶӰ��ʽ
//	camera��������
//	ͼƬ��Դ
//	bvh�ļ�

//  ��ʾ�ڵ�����