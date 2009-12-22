#ifndef __CBUTTON_H_
#define __CBUTTON_H_

#include "CTexture.h"
#include "global.h"
#include <vector>
#include <fstream>

class CButton
{
public:
	CButton(){};
	CButton(int x, int y, int Width, int Height);
	~CButton();
	
	//�麯�� ��������ģ�庯��
	void Render();
	virtual bool OnMouseDown(LPARAM lParam);
	virtual void OnMouseUp(LPARAM lParam);
	
	virtual bool OnMouseDown(int MouseX, int MouseY);
	virtual void OnMouseUp();
	
	void	SetTexId(int id){ m_iTexID = id; }
	GLuint	GetTexId()const { return m_iTexID; };
	void	SetVisible(){ m_bVisible = true;};
	void	SetInVislble(){m_bVisible = false;}

	void	SetPos(int x, int y){ m_ix=x, m_iy=y; };
protected:
	bool m_bVisible;
	float m_iZOrder;
	float m_fAlpha;
	bool m_bPressed;

	GLuint m_iTexID;
	int m_ix;
	int m_iy;
	int m_iWidth;
	int m_iHeight;
};

//Just like "PAUSE" button: Firstly you hit it, it means pause the play,
//but when you hit it secondly it means continue the play.
class CButtonTwoHit : public CButton
{
public:
	CButtonTwoHit(int x, int y, int width, int height)
		:CButton(x, y, width, height)
		, m_bIsFirst(true)
	{
	}

	void Active(){ m_fAlpha = 0.3f; };
	void DeActive(){ m_fAlpha = 1.0f; };

	bool IsDown() {return m_bIsFirst;}
	bool OnMouseDown(LPARAM lParam)
	{
 		if ( CButton::OnMouseDown(lParam) )
		{
			if( m_bIsFirst )	//��һ�ΰ���:͸���Ƚ�Ϊ0.3
				Active();
			else
				DeActive();		//�ڶ��ΰ��£��ظ�Ϊ1.0
			
			m_bIsFirst = !m_bIsFirst;
			
			return true;
		}
		return false;
	}
private:
	bool m_bIsFirst;
};


//This Button is movable 
class CButtonMovable : public CButton
{
public:
	CButtonMovable(int x, int y, int width, int height)
		: CButton(x, y, width, height)
		, m_bIsDragging(false)
	{
		m_vOffset.x = 0;  m_vOffset.y = 0;
	}
	~CButtonMovable(){};

	// �����Ҫ�ƶ� �ͻ����OnMouseMove����
	void OnMouseMove(int x, int y)
	{
		if( m_bIsDragging )
		{
			// m_vStartPosΪ�ƶ������е����λ������ڰ�ť���½ǵ�ƫ����,�������ֵΪ��...
			m_ix = m_vOffset.x + x;
			m_iy = m_vOffset.y + y;
		}
	}
	bool OnMouseDown(int x, int y)
	{
		if ( CButton::OnMouseDown(x, y) )
		{
			m_bIsDragging = true;
			// ��¼��������ʼλ��
			m_vOffset.x = m_ix - x;
			m_vOffset.y = m_iy - y;
			return true;
		}
		return false;
	}

	void OnMouseUp()
	{
		CButton::OnMouseUp();
		m_bIsDragging = false;
	}
private:
	//�Ƿ��ƶ���ť
	bool m_bIsDragging;
	struct Vec2{int x, y;};

	//��OnMouseDownʱ���������Ͱ�ť��ƫ����(m_vMousePos��m_ix,m_iy)
	Vec2 m_vOffset;
};


//////////////////////////////////////////////////////////////////////////
// �ҵĳ��ԣ�
//		һ����ť��Ӧһ��ͼƬ��ͼ����ʽTGA��32λ.
//		ÿ����ť�����꣬�ߴ�.
//		������¼�������Ӧ.			
// [3/3/2009 RenYaFei]
//		ʵ�������ֲ�ͬ�İ�ť����.
// [3/3/2009 RenYaFei]
//		ʵ���˿����ƶ��İ�ť�����Ǽ���λ�ò������е��Σ�
//////////////////////////////////////////////////////////////////////////
//Button������Ҫ����һ�����ڸ߶�
//	960��������
//  ��Ϊ����button���������궼����������ϵ��
//							ԭ��λ�����½�
//							Y�����ϣ�X������
//	����Ϊ������ǰ�ᣬ�����Ĵ�����CAPP��CButton���涼��Ҫ����һ�����ڸ߶�

//has-a �Ĺ�ϵ
// �鿴����ƶ���λ��
// 			_LOG( std::string("Mouse Down at [") +  toStr<int>(m_vStartPos.x) + std::string(" ")
// 				+ toStr<int>(m_vStartPos.y) + std::string("]") );
// 		_LOG( std::string("Mouse Move by the point: [") +  toStr<int>(m_vMouseMove.x) + std::string(" ")
// 			+ toStr<int>(m_vMouseMove.y) + std::string("]") );
//////////////////////////////////////////////////////////////////////////
//[3/14/2009 RenYaFei]
//	glut�е�MouseMove������win32�е�MouseMove��һ����
//	ǰ��ֻ����갴�µ�ʱ���move��Ӧ��
//	��win32�е����move��һֱ������Ӧ״̬.
//	��ǰ�汾Ϊglut�汾:CButtonMovable�е�OnMouseDown��OnMouseMove�����޸�
#endif

