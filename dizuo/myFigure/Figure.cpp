#include "Figure.h"
#include <cmath>

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

//#include "myGraphy.h"
#include "util/Helper.h"

using namespace std;

// ----------------------------------------------------------------
//	Name��			Figure::Figure()
//	Description:	Ĭ�Ϲ��캯��
//	Return Value:	
// ----------------------------------------------------------------
Figure::Figure()
{
	init();
}

// ----------------------------------------------------------------
//	Name��			Figure::Figure()
//	Description:	���ع��캯��, ����Ϊ�ļ���
//	Return Value:	
// ----------------------------------------------------------------
Figure::Figure(std::string _name)
	: BvhEditer(_name)
{
	init();
}

Figure::Figure(const char * _name)
	: BvhEditer( std::string(_name) )
{
	init();
}
// ----------------------------------------------------------------
//	Name��			Figure::~Figure()
//	Description:	��������
//	Return Value:	
// ----------------------------------------------------------------
Figure::~Figure()
{
	cout << "delete the figure" << endl;
	init();
	SAFE_DELETE(font_container);
}

// ----------------------------------------------------------------
//	Name��			Figure::render_figure
//	Description:	���ƽ�ɫ
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::render_figure(float scale, GLenum mode)
{
	render(root, frame_control, scale, mode);
}

// ----------------------------------------------------------------
//	Name��			Figure::update
//	Description:	������ţ���ǰ��һ֡
//	Return Value:	bool
// ----------------------------------------------------------------
bool Figure::update()
{
	if(is_play)
		forward();
	return true;
}

// ----------------------------------------------------------------
//	Name��			Figure::play
//	Description:	��is_play������Ϊtrue
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::play()
{
	is_play = true;
}

// ----------------------------------------------------------------
//	Name��			Figure::pause
//	Description:	��is_playΪfalse
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::pause()
{
	is_play = false;
}

// ----------------------------------------------------------------
//	Name��			Figure::forward
//	Description:	��������ǰ��һ֡
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::forward()
{
	if( frame_control >= (frames_num-1) ) 
		frame_control = 0;
	frame_control++;
}

// ----------------------------------------------------------------
//	Name��			Figure::backward
//	Description:	������������һ֡
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::backward()
{
	if( frame_control <= 0 )
		frame_control = frames_num-1;
	frame_control--;
}

// ----------------------------------------------------------------
//	Name��			Figure::render
//	Description:	�ݹ�ػ���Figure�����ṹ
//					First:	Translate()
//					Second: Rotate()
//					Third:	Render()
//					Last:	Recurs_render()	
//					frame:��0��ʼ��
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::render(part *some, size_t frame, float scale, GLenum mode)
{	
	glPushMatrix();
	{
		//////////////////////////////////////////////////////////////////////////
		//Translate()
		glTranslated( some->offset[0] * scale, 
					  some->offset[1] * scale, 
					  some->offset[2] * scale );
		some->render(mode);	//��ʾ�ؽڵ�
	
		//////////////////////////////////////////////////////////////////////////
		//Rotate()
		for ( size_t i=0; i<some->channels.size(); i++ )
		{
 			Joint::Channel *channel = some->channels[i];
 			float rot_data = get_motion(frame, channel->index);
 
 			//motion_data��������Ӧ����frame_count��motion_data����ʹ��
 			if ( channel->type == part::Xrot )
 				glRotatef( rot_data, 1.0f, 0.0f, 0.0f );
 			else if ( channel->type == part::Yrot )
 				glRotatef( rot_data, 0.0f, 1.0f, 0.0f );
 			else if ( channel->type == part::Zrot )
 				glRotatef( rot_data, 0.0f, 0.0f, 1.0f );
		}
		//////////////////////////////////////////////////////////////////////////
		//Render()
		// һ���������:
		if ( some->children.size() == 1 )
		{
			Joint *  child = some->children[0];
			render_bone( 0.0f, 0.0f, 0.0f, 
						 child->offset[0] * scale, 
						 child->offset[1] * scale, 
						 child->offset[2] * scale );
		}
		// ��������������Ȩƽ�����������center
		if ( some->children.size() > 1 )
		{
			double center[3] = { 0.0f, 0.0f, 0.0f };
			for (size_t i=0; i<some->children.size(); i++ )
			{
				part *child = some->children[i];
				center[0] += child->offset[0];
				center[1] += child->offset[1];
				center[2] += child->offset[2];
			}
			//��Ȩƽ��
			center[0] /= some->children.size() + 1;
			center[1] /= some->children.size() + 1;
			center[2] /= some->children.size() + 1;

			render_bone( 0.0f, 0.0f, 0.0f, 
						 center[0] * scale, 
						 center[1] * scale, 
						 center[2] * scale );

			for (size_t i=0; i<some->children.size(); i++ )
			{
				part *child = some->children[i];
				render_bone( center[0] * scale, center[1] * scale, 
							 center[2] * scale, child->offset[0] * scale, 
							 child->offset[1] * scale, child->offset[2] * scale );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Recurs_render()
		//��someΪҶ�ӽڵ�ʱ�򣬲�������ݹ�
		for (size_t i=0; i<some->children.size(); i++)
		{
			render(some->children[i], frame, scale, mode);
		}
	}
	glPopMatrix();
}

// ----------------------------------------------------------------
//  Name:           Figure::render_bone
//  Description:    ��������������ȷʵ���Ƴ�bone��Ҫ���еı任
//  Return Value:   void
// ----------------------------------------------------------------
// void  Figure::render_bone( float x0, float y0, float z0, 
// 						   float x1, float y1, float z1 )
void Figure::render_bone( double x0, double y0, double z0, 
						  double x1, double y1, double z1 )
{
	glColor4f(1.0, 0.0, 0.0, 4.0);
	//�����bone�ĳ���
	GLdouble  dir_x = x1 - x0;
	GLdouble  dir_y = y1 - y0;
	GLdouble  dir_z = z1 - z0;
	GLdouble  bone_length = 
		sqrt( dir_x*dir_x + dir_y*dir_y+ dir_z*dir_z );

	glPushMatrix();
	//ƽ��
	glTranslated( x0, y0, z0 );

	double  length;
	length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
	if ( length < 0.0001 ) { 
		dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;
	}
	//��λ��dir����
	dir_x /= length;  dir_y /= length;  dir_z /= length;

	// Up ����
	GLdouble  up_x, up_y, up_z;
	up_x = 0.0;
	up_y = 1.0;
	up_z = 0.0;

	// (up_x, up_y, up_z)��(dir_x, dir_y, dir_z)
	//------------------------------------------
	//	i		 j		 k
	// up_x		up_y	up_z
	// dir_x	dir_y	dir_z
	//------------------------------------------
	// Vector(side) = Vector(up) �� Vector(dir)
	double  side_x, side_y, side_z;
	side_x = up_y * dir_z - up_z * dir_y;
	side_y = up_z * dir_x - up_x * dir_z;
	side_z = up_x * dir_y - up_y * dir_x;

	length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );
	if ( length < 0.0001 ) {
		side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;
	}
	//��λ��side����
	side_x /= length;  side_y /= length;  side_z /= length;

	// �ٴβ�˼����up����
	up_x = dir_y * side_z - dir_z * side_y;
	up_y = dir_z * side_x - dir_x * side_z;
	up_z = dir_x * side_y - dir_y * side_x;

	// ����任����:OpenGL���������
	GLdouble  m[16] = { side_x, side_y, side_z, 0.0,
		up_x,   up_y,   up_z,   0.0,
		dir_x,  dir_y,  dir_z,  0.0,
		0.0,    0.0,    0.0,    1.0 };
	glMultMatrixd( m );
	
	pDrawBone(bone_length);

	glPopMatrix();
}
// vec3�໹�������⣬
// ʹ��vec3�м���cylinder�İ뾶��仯...???



// ----------------------------------------------------------------
//	Name��			Figure::process_font()
//	Description:	���ز����.
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::process_font( const tree_node* some, 
						   unsigned recurs_level )
{
	//����е�right������ʾ��ͼ
	font_container->AddFontElem( font_pos_x + recurs_level*10, 
								 font_pos_y + font_pos_offset_y*20, -0.05, 
								 std::string("9 by 15"), some->name.c_str() );

	font_pos_offset_y++;

	for (unsigned i = 0; i < some->children.size(); i++)
		process_font(some->children[i], recurs_level+1);
}

// ----------------------------------------------------------------
//	Name��			Figure::reset_joints()
//	Description:	deactive����Figure������Joint
//					���ڿ���ÿ��ֻ��ѡȡһ���ڵ�
//					add -- 3/17/2009 RenYaFei
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::reset_joints()
{
	for( vec_iter it = linear_joint_vec.begin(); 
		 it != linear_joint_vec.end();
		 it++ )
	{
		(*it)->deactive();
	}
}

// ----------------------------------------------------------------
//	Name��			Figure::init()
//	Description:	��ʼ��
//	Return Value:	void
// ----------------------------------------------------------------
void Figure::init()
{
	frame_control = 0;
	is_play = false;
	font_container = new FontContainer;
	font_pos_offset_y = 1;
	font_pos_x = 0;
	font_pos_y = 0;

	//pDrawBone = &(Helper::myWirePyramid);
	pDrawBone = &(Helper::mySolidCylinder);
	//pDrawBone = &(Helper::mySolidPyramid);
	//pDrawBone = &(Helper::myDrawNone);
}
