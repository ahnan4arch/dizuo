//ʹ��unix������ʽ:
#ifndef FIGURE_H
#define FIGURE_H

#include "Joint.h"
//#include "util/Font.h"
#include <iostream>
#include <map>

#include "util/global.h"
#include "FontContainer.h"

#include "BvhEditer.h"

class Figure : public BvhEditer
{
public:
	typedef Joint part;
	typedef void (*pFunc) (GLdouble);

	Figure();
	Figure(std::string _name);
	Figure(const char * _name);
	~Figure();

	//animation control:
	bool	 update();
	void	 play();
	void	 pause();
	void	 forward();
	void	 backward();

	//render function
	void	 render_figure(float scale=1.0, GLenum mode=GL_RENDER);
	void	 render(part* some, size_t frame, float scale = 1.0, GLenum mode=GL_RENDER);
	void	 render_bone(double x0, double y0, double z0, double x1, double y1, double z1);
	
	//select function
	void	 reset_joints();	//�������еĽڵ�
	void	 init();

	void	 process_font(const tree_node* some, unsigned recurs_level);
public:
	void	 set_draw_mode(pFunc drawfunc){ pDrawBone = drawfunc; }
	void	 set_font_pos(int x, int y){font_pos_x = x;font_pos_y = y;}
	int		 get_current_framenum() const{return frame_control;}
	
	FontContainer	*font_container;
private:
	//void (*pDrawBone)(GLdouble);
	pFunc		pDrawBone;
	bool		is_play;
	int			frame_control;

	//�ṹ����ʾ
	int			font_pos_offset_y;
	int			font_pos_x, font_pos_y;	//������ʼλ��
	//��ʾ���壬��ֱ�������������ӵģ�����x����ȷʵ����ʽ��
};
//////////////////////////////////////////////////////////////////////////
//�ṩ����setup����
//		�����ֶ����룬�Խű���ʽ��Ӧ�õ�����
//		�������ļ�����ʽ
// [3/11/2009 RenYaFei]
//	������������ʾ
// [3/16/2009 RenYaFei]
//		������ʾ���⣺font_pos_offset_y����y����ƫ�ƣ����Ե�...
//				  recurs_levelǡ�ÿ��Կ���x����ģ�����ʽ��...
//		font_container�ṩ�ұߵ�����ѡȡ����
// [3/17/2009 RenYaFei]
//		������reset_joints����
// [4/1/2009 RenYaFei]
//		�ع�Figure�ࣺ
//		ȥ��map�洢�ṹ��ʹ������vector��
//		����resetʵ��
//		ȥ��proce_file()
//		Figure�̳���htree����
//		Figure�̳���BvhEditer
//  [4/4/2009 RenYaFei]
//		���Ӻ���ָ��ʵ�ֶ���ģʽ����
//  [4/5/2009 RenYaFei]
//		�б�Ҫ����һ��Bone����.
//  [4/23/2009 RenYaFei]
//		offset��������������ϵ�µľ�������...
/*
+-----------------------------------------------------------+
|                                                           |
|                          o                                |
|                          | Head                           |
|        Right.shoulder    |   Left.shoulder                |
|                  o-------o-------o                        |
|  Right.upperarm  |       |Upper- | Left.upperarm          |
|                  |       |back   |                        |
|                  o       |       o                        |
|  Right.lowerarm  |       |       | Left.lowerarm          |
|                  |       oLower- |                        |
|                  o       |back   o                        |
|  Right.hand      |       |       | Left.hand              |
|                          |                                |
|               Right.butt | Left.butt                      |
|                       o--o--o                             |
|                       |     |                             |
|                       |     |                             |
|       Right.upperleg  |     | Left.upperleg               |
|                       |     |                             |
|                       o     o                             |
|                       |     |                             |
|                       |     |                             |
|       Right.lowerleg  |     | Left.lowerleg               |
|                       o     o                             |
|       Right.foot     /     /  Left.foot                   |
|                                                           |
|                                                           |
+-----------------------------------------------------------+
*/

#endif 