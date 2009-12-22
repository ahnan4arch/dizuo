#include "FontContainer.h"

#include "util/global.h"


// ----------------------------------------------------------------
//	Name��			FontContainer::FontContainer
//	Description:	���캯����ʼ��...
//	Return Value:	
// ----------------------------------------------------------------
FontContainer::FontContainer()
	: m_bIsSkip(true)
	, m_sSelectName("")
	, m_iLast(-1)
	, m_bIsShow(false)
{
	FontTypeMap[std::string("8 by 13")] = (int)(GLUT_BITMAP_8_BY_13);
	FontTypeMap[std::string("9 by 15")] = (int)(GLUT_BITMAP_9_BY_15);
	FontTypeMap[std::string("Times Roman 10")]	= (int)(GLUT_BITMAP_TIMES_ROMAN_10);
	FontTypeMap[std::string("Times Roman 24")]	= (int)(GLUT_BITMAP_TIMES_ROMAN_24);
	FontTypeMap[std::string("Helvetica 10")] = (int)(GLUT_BITMAP_HELVETICA_10);
	FontTypeMap[std::string("Helvetica 12")] = (int)(GLUT_BITMAP_HELVETICA_12);
	FontTypeMap[std::string("Helvetica 18")] = (int)(GLUT_BITMAP_HELVETICA_18);
}

// ----------------------------------------------------------------
//	Name��			FontContainer::~FontContainer
//	Description:	��������
//	Return Value:	
// ----------------------------------------------------------------
FontContainer::~FontContainer()
{
	FontTypeMap.clear();

	for (size_t i=0; i<m_vFontVec.size(); i++)
		SAFE_DELETE(m_vFontVec[i]);
	
	m_vFontVec.clear();
}

// ----------------------------------------------------------------
//	Name��			FontContainer::AddFontElem
//	Description:	λ��x,y,z; ��������string; ����str
//	Return Value:	void
// ----------------------------------------------------------------
void FontContainer::AddFontElem( int x, int y, int z, 
								 std::string FontType, const char *str )
{
	Font*  pTem = new Font(x, y, z, FontTypeMap[FontType], str);
	m_vFontVec.push_back( pTem );	
}

// ----------------------------------------------------------------
//	Name��			FontContainer::Render
//	Description:	��һ��Ⱦ����
//	Return Value:	void
// ----------------------------------------------------------------
void FontContainer::Render()
{
	if( m_bIsShow==false )
		return;

	glColor4f(1.0, 1.0, 1.0, 1.0);
	for (size_t i=0; i<m_vFontVec.size(); i++)
	{
		m_vFontVec[i]->Render3();
	}
}

// ----------------------------------------------------------------
//	Name��			FontContainer::OnMouseDown
//	Description:	���λ��x,y���������Ƿ�ѡ����ĳ��font��
//					��ѡ�е��������͸���Ϊ:Times Roman 24
//					Font��λ��Pos�����½ǣ�������ϵ�����Ͻǣ�y������
//	Return Value:	bool
// ----------------------------------------------------------------
bool FontContainer::OnMouseDown(int mousex, int mousey)
{
	for (size_t i=0; i<m_vFontVec.size(); i++)
	{
		if( m_vFontVec[i]->Check(mousex, mousey) )
		{
			if( m_sSelectName != "" 
				&& i != m_iLast)
				m_bIsSkip = true;

			if( m_bIsSkip )
			{
				if(m_iLast != -1)	//���ǵ�һ��
					m_vFontVec[m_iLast]->DeActive();
				m_vFontVec[i]->Active();
				m_sSelectName = std::string( m_vFontVec[i]->GetStr() );
				m_iLast = i;
				
				m_bIsSkip = false;
			}
			else
			{
				m_vFontVec[i]->DeActive();
				m_sSelectName = "";
				m_bIsSkip = true;
				return false;
			}
			return true;
		}
	}
	return false;
}

// ----------------------------------------------------------------
//	Name��			FontContainer::OnMouseUp
//	Description:	�ڰ�����ʱ�������Ƿ���font��ѡ�У�
//					�����ǰû��font��ѡ�񣬱���ȷ�������������Ͷ���
//					��ʼ���ͣ��ر���֮ǰ��ѡ�е�font
//	Return Value:	
// ----------------------------------------------------------------
void FontContainer::OnMouseUp()
{
	//ÿ��up��ʱ����
}

//��Ҫ���߼����......
//  [3/17/2009 RenYaFei]
//		fontѡ���߼�����OK��...
//		������ɫ��
