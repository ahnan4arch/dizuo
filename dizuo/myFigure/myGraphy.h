#ifndef MYGRAPHY_H
#define MYGRAPHY_H 


#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <GL/glut.h>

namespace Helper
{
	// ----------------------------------------------------------------
	//	Name��			DrawNet()
	//	Description:	������
	//					sizeΪ����
	//					LineXΪX�����ϵ�������
	//					LineZΪZ�����ϵ�������
	//	Return Value:	inline void
	// ----------------------------------------------------------------	
	inline void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
	{
		glPushMatrix();
		glBegin(GL_LINES);
		for (int xc = 0; xc < LinesX; xc++)
		{
			glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
				0.0,
				size / 2.0);
			glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
				0.0,
				size / -2.0);
		}
		for (int zc = 0; zc < LinesX; zc++)
		{
			glVertex3f(	size / 2.0,
				0.0,
				-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
			glVertex3f(	size / -2.0,
				0.0,
				-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		}
		glEnd();
		glPopMatrix();
	}


	// ----------------------------------------------------------------
	//	Name��			DrawAxis()
	//	Description:	��������ϵ
	//	Return Value:	inline void
	// ----------------------------------------------------------------	
	inline void DrawAxis()
	{
		glLineWidth(2.0);
		glBegin(GL_LINES);
		{
			glVertex3f(50, 0, 0); glVertex3f(-50, 0, 0);
			glVertex3f(0, 50, 0); glVertex3f(0, -50, 0);
			glVertex3f(0, 0, 50); glVertex3f(0, 0, -50);
		}
		glEnd();
	}

	// ----------------------------------------------------------------
	//	Name��			Float2Str()
	//	Description:	��floatת��Ϊstring
	//	Return Value:	inline std::string
	// ----------------------------------------------------------------	
	inline std::string Float2Str( float x )
	{
		std::ostringstream o;
		std::setprecision(4);
		o << x;
		return o.str();
	}

	// ----------------------------------------------------------------
	//	Name��			mySolidCylinder()
	//	Description:	��������׶
	//					����Ϊ����
	//					����Բ�뾶 0.3
	//	Return Value:	inline void
	// ----------------------------------------------------------------	
	inline void mySolidCylinder(GLdouble bone_length)
	{	
		GLdouble bone_radius= 0.3; 
		GLdouble slices = 8.0; 
		GLdouble stack = 3.0; 

		static GLUquadricObj *  quad_obj = NULL;
		if ( quad_obj == NULL )
			quad_obj = gluNewQuadric();
		gluQuadricDrawStyle( quad_obj, GLU_FILL );
		gluQuadricNormals( quad_obj, GLU_SMOOTH );

		gluCylinder( quad_obj, bone_radius, bone_radius, 
			bone_length, slices, stack ); 
	}

	// ----------------------------------------------------------------
	//	Name��			mySolidPyramid()
	//	Description:	��������׶
	//					����߶�7/10 ����λ��ԭ��
	//					����߶�3/10 �׵�λ��(0, 0, bone_length)λ��
	//					�м�߳�0.6  λ��z = bone_length*0.3 ƽ����
	//	Return Value:	inline void
	// ----------------------------------------------------------------	
	inline void mySolidPyramid(GLdouble bone_length)
	{
		GLfloat size = 0.6;
		GLfloat base_length = bone_length*0.1;
		GLfloat top_length = bone_length*0.9;
		glPushMatrix();
		{
			//top
			glBegin(GL_TRIANGLE_FAN);     	// draw triangle		
				glVertex3f( 0.0f, 0.0f, 0.0f);
				glVertex3f(-size, 0.0f, base_length);
				glVertex3f( 0.0f, size, base_length);
				glVertex3f( size, 0.0f, base_length);
				glVertex3f( 0.0f, -size, base_length);
				glVertex3f(-size, 0.0f, base_length);
			glEnd();
			glBegin(GL_QUADS);               // draw square
			glVertex3f(-size, 0.0f, base_length);
			glVertex3f( 0.0f, size, base_length);
			glVertex3f( size, 0.0f, base_length);
			glVertex3f( 0.0f, -size, base_length);
			glEnd();
			// base
			glBegin(GL_TRIANGLE_FAN);     	// draw triangle
				glVertex3f(0.0f, 0.0f, bone_length);
				glVertex3f(-size, 0.0f, base_length);
				glVertex3f( 0.0f, size, base_length);
				glVertex3f( size, 0.0f, base_length);
				glVertex3f( 0.0f, -size, base_length);
				glVertex3f(-size, 0.0f, base_length);
			glEnd();
		} glPopMatrix();
	}

	// ----------------------------------------------------------------
	//	Name��			myDrawNone()
	//	Description:	do nothing...
	//	Return Value:	inline void
	// ----------------------------------------------------------------	
	inline void myDrawNone(GLdouble bone_length)
	{
		//do nothing...
	}
}//namespace Helper
#endif