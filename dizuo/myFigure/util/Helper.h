#ifndef HELPER_H_
#define HELPER_H_

#include "Rectangle.hpp"
#include "Color.h"

#include<cmath>
#include<vector>
#include <string>
#include <iostream>
#include <sstream>
#include <gl/freeglut.h>


class Helper
{
public:
	template<class T> static void myAddRange(std::vector<T>& whole, const std::vector<T>& part);
	template<typename T> static int getBufferSize(T& buffer);

	//wstring to string 
	static std::string ws2s(const std::wstring& ws);
	//string to wstring
	static std::wstring s2ws(const std::string& s);
	

	static void renderBitmapString2D( float x, float y, void *font, char *string );
	static void renderBitmapString3D( float x, float y, float z, void* font, std::string str );
	static void renderRectangle( const TRectanglef& rect, Color4 color=Color4(0xFF0000), bool isEmpty = true );
	static void renderElipse( const TRectanglef& rect, Color4 color=Color4(0xFF0000), bool isEmpty = true );
	
	static void DrawAxis();
	template<class T>
	static std::string Value2Str(T value);
	static std::string Float2Str( float x );
	static void myDrawNone(GLdouble bone_length);
	static void mySolidPyramid(GLdouble bone_length);
	static void myWirePyramid(GLdouble bone_length);
	static void mySolidCylinder(GLdouble bone_length);
	static void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ);
	
	// ----------------------------------------------------------------
	//	Name��			ColorStable
	//	Description:	ѡ����ɫ
	// ----------------------------------------------------------------
	static GLuint ColorStable[24];		//�Ӹ�24��getSize�Ϳ��Ե�
};

// ----------------------------------------------------------------
//	Name��			myAddRange
//	Description:	��part������Ԫ����ӵ�whole��ȥ
//	Return Value:	void
// ----------------------------------------------------------------
template<class T>
void Helper::myAddRange(std::vector<T>& whole, const std::vector<T>& part)
{
	for (size_t i(0); i< part.size(); i++)
	{	whole.push_back( part[i] ); }
}

// ----------------------------------------------------------------
//	Name��			getBufferSize
//	Description:	ͨ��ģ��������Ԫ�ظ���
//	Return Value:	int
// ----------------------------------------------------------------
template<typename T>
int Helper::getBufferSize(T& buffer)    
{    
	int n;  
	n=sizeof(buffer)/sizeof(*buffer); 
	return n;  
}

// ----------------------------------------------------------------
//	Name��			Value2Str()
//	Description:	������ת��Ϊstring
//	Return Value:	static std::string
// ----------------------------------------------------------------	
template<class T>
std::string Helper::Value2Str( T value )
{
	std::ostringstream o;
	o << value;
	return o.str();
}

#endif

//////////////////////////////////////////////////////////////////////////
// ģ�岻֧�ַ���ģ��
// ��̬��Ա���� ��������