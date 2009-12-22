#include "MainFrame.h"
#include <gl/glut.h>

// ----------------------------------------------------------------
//  Name:           Mainframe::Init
//  Description:    ����������ܣ��Լ������ֵ�����
//					����ϵԭ��λ�����Ͻ�
//  Return Value:   bool
// ----------------------------------------------------------------
bool Mainframe::Init()
{
	//void SetRect(const T& l, const T& b, const T& r, const T& t )
	m_top.SetRect(0, 75, 1024, 0);
	m_bottom.SetRect(0, 768, 1024, 630);
	m_right.SetRect(682, 630, 1024, 75);
	m_mainframe.SetRect(0, 768, 1024, 0);
	m_client.SetRect( m_bottom.m_Left, m_bottom.m_Top, 
		m_right.m_Left, m_top.m_Bottom );
	return true;
}
//mainframe:
/*
(0.0)---------------------------------------------------------->X
//| 75						(Top)1024							|
//|---------------------------------|---------------------------|
//|					682				|		1024-682			|
//|									|							|
//|									|							|
//|				����ģ����			|							|
//|555								|555		(Right)			|
//|									|							|
//|									|							|
//|									|							|
//|									|							|
//|---------------------------------|---------------------------|
//|768-555-75=138				(Bottom)						|
//|-------------------------------------------------------------|
//|
//Y
*/

// ----------------------------------------------------------------
//  Name:           Mainframe::Render
//  Description:    �����趨��texid����
//  Return Value:   void
// ----------------------------------------------------------------
void Mainframe::Render()
{
	glBindTexture(GL_TEXTURE_2D, m_iTexid);
	//top
	glPushMatrix();
	{
		float m_iWidth = static_cast<float>(m_top.GetWidth());
		float m_iHeight = static_cast<float>(m_top.GetHeight());
		glTranslatef((float)m_top.m_Left + m_iWidth/2.0f,  m_top.m_Top + m_iHeight/2.0f, -0.1f);	
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		{
			// ��ʱ��quad������λ��ԭ��
			glTexCoord2f(1.0f, 1.0f);		glVertex2f(-m_iWidth/2.0f, -m_iHeight/2.0f);
			glTexCoord2f(0.0f, 1.0f);		glVertex2f(m_iWidth/2.0f,  -m_iHeight/2.0f);
			glTexCoord2f(0.0f, 693.0f/768.0f);		glVertex2f(m_iWidth/2.0f,  m_iHeight/2.0f);
			glTexCoord2f(1.0f, 693.0f/768.0f);		glVertex2f(-m_iWidth/2.0f, m_iHeight/2.0f);
		}
		glEnd();
	}glPopMatrix();

	//bottom
	glPushMatrix();
	{
		float m_iWidth = static_cast<float>(m_bottom.GetWidth());
		float m_iHeight = static_cast<float>(m_bottom.GetHeight());
		glTranslatef((float)m_bottom.m_Left + m_iWidth/2, m_bottom.m_Top + m_iHeight/2.0f, -0.1f);	
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		{
			// ��ʱ��quad������λ��ԭ��
			glTexCoord2f(1.0f, 138.0f/768.0f);		glVertex2f(-m_iWidth/2.0f, -m_iHeight/2.0f);
			glTexCoord2f(0.0f, 138.0f/768.0f);		glVertex2f(m_iWidth/2.0f,  -m_iHeight/2.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex2f(m_iWidth/2.0f,  m_iHeight/2.0f);
			glTexCoord2f(1.0f, 0.0f);		glVertex2f(-m_iWidth/2.0f, m_iHeight/2.0f);
		}
		glEnd();
	}glPopMatrix();

	//right
	glPushMatrix();
	{

		float m_iWidth = static_cast<float>(m_right.GetWidth());
		float m_iHeight = static_cast<float>(m_right.GetHeight());
		glTranslatef((float)m_right.m_Left + m_iWidth/2, m_right.m_Top + m_iHeight/2.0f, -0.1f);	
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		{
			// ��ʱ��quad������λ��ԭ��
			glTexCoord2f(1.0f, 693.0f/768.0f);		glVertex2f(-m_iWidth/2.0f, -m_iHeight/2.0f);
			glTexCoord2f(682.0f/1024.0f, 693.0f/768.0f);		glVertex2f(m_iWidth/2.0f,  -m_iHeight/2.0f);
			glTexCoord2f(682.0f/1024.0f, 138.0f/768.0f);		glVertex2f(m_iWidth/2.0f,  m_iHeight/2.0f);
			glTexCoord2f(1.0f, 138.0f/768.0f);		glVertex2f(-m_iWidth/2.0f, m_iHeight/2.0f);
		}
		glEnd();
	}glPopMatrix();
}