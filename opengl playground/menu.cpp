#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <ctime>

//////////////////////////////////////////////////
//global
float g_fWidth = 500;
float g_fHeight = 500;
float g_fDepth = 100;
float g_fAngle = .0;

struct Button{
	float m_fPosX;		//��ʾ������ͶӰ����ϵ(���½�Ϊ����ԭ��)�����꣬
	float m_fPosY;
	float m_fWidth;		//��Ļ���ص�λ
	float m_fHeight;

	bool m_bPressed;
	void Render()
	{
		glPushMatrix();
		{
			//������λ��ԭ���cube�ƶ���ʹcube���½�����Ϊm_fPosX,m_fPosY��λ��
			//���뿼��cube��������
			glTranslatef(m_fPosX+m_fWidth/2, m_fPosY+m_fHeight/2, -2.0);		//-2.0ֻ��Ϊ�˰�ť�ɼ�
			if( m_bPressed )
			{
				//double scaleAmt = 10.0 * sin( (double)rand() );
				//double scaleAmt = sin( (double)rand() );
				glScalef(0.9, 0.9, 1.0);
			}
			//cube����λ��ԭ��
			glScalef (m_fWidth, m_fHeight, 5.0);      
			glutSolidCube(1.0);
		}
	}
	bool OnMouseDown(int mousex, int mousey)
	{
		//����λ�ã�mousex��mousey����ϵ��ԭ��λ�����Ͻ�
		//���뽫mousey�任��ԭ��λ�����½ǵ�����ϵ��
		mousey = g_fHeight-mousey;
		if( mousex > m_fPosX && mousex < m_fPosX+m_fWidth &&
			mousey > m_fPosY && mousey < m_fPosY+m_fHeight )
		{
			printf("button is pressed .... \n");
			m_bPressed = true;
			
			return true;
		}
		return false;
	}
	void OnMouseUp()
	{
		m_bPressed = false;
	}
};
Button* pBtn;

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	pBtn = new Button;
	pBtn->m_bPressed = false;
	pBtn->m_fPosX = 40;
	pBtn->m_fPosY = 480;
	pBtn->m_fWidth = 60;
	pBtn->m_fHeight = 20;
	printf("**********button pos: 40\t480\n");
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_fWidth, 0, g_fHeight, 0, g_fDepth);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pBtn->Render();

	// ����cube���壬
	glMatrixMode (GL_PROJECTION);		//�ظ�ԭ�е�����
	glLoadIdentity ();
	gluPerspective(60,1.0,1.5,20);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();           
	/* viewing transformation  */
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(g_fAngle, 0.0, 1.0, 0.0);
	glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
	glutWireCube (1.0);
	//glFlush();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60,1.0,1.5,20);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
case 27:
	exit(0);
	break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON)
		switch(state)
	{
		case GLUT_DOWN:
			//������£�
			printf("Mouse pos : %d\t%d\n", x, 500-y);
			if( pBtn->OnMouseDown(x, y) )
				g_fAngle += 2.0;
			break;

		case GLUT_UP:
			pBtn->OnMouseUp();
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc( mouse );
	glutMainLoop();
	return 0;
}
