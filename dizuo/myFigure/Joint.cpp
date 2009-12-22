#include "Joint.h"

#include "util/global.h"

const GLfloat	green[] = { 20/255.0f, 254.0f/255.0f, 20/255.0f, 1.0f};
const GLfloat	yellow[] = { 253.0f/255.0f, 208.0f/255.0f, 0.0f/255.0f, 1.0f};

// ----------------------------------------------------------------
//	Name��			Joint::Joint
//	Description:	���ݸ�����Ϣ����ڵ�
//	Return Value:	...
// ----------------------------------------------------------------
Joint::Joint(std::string _name, float x, float y, float z )
{
	clear();
	name = _name;
	offset.setValue(x, y, z);
}
// ----------------------------------------------------------------
//	Name��			Joint::Joint
//	Description:	Ĭ�Ϲ��캯��
//	Return Value:	...
// ----------------------------------------------------------------
Joint::Joint()
{
	clear();
}

// ----------------------------------------------------------------
//	Name��			Joint::~Joint
//	Description:	�ͷ���Դ
//	Return Value:	...
// ----------------------------------------------------------------
Joint::~Joint()
{
	clear();
}

// ----------------------------------------------------------------
//	Name��			Joint::render
//	Description:	���ƽڵ㣬������,�ڵ㱻ѡ��ʱ���Ŵ�һ��.
//					���ÿһ֡��ÿ���ڵ��ڴ����е�λ��
//					��ʱ�����Ƿ����ѡ��
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::render(GLenum mode)		
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];
	
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	gluProject(0, 0, 0, modelMatrix, projMatrix, viewport,
		&screen_pos[0], &screen_pos[1], &screen_pos[2]);


	glColor4f(0.0, 1.0, 1.0, 1.0);
	if(is_select)
	{
		glColor4f(253.0f/255.0f, 208.0f/255.0f, 0.0f/255.0f, 1.0f);
		glutSolidSphere(joint_radius*2, 10, 6);
	}
	else
	{
		glutSolidSphere(joint_radius, 10, 6);
	}
}

// ----------------------------------------------------------------
//	Name��			Joint::active
//	Description:	�ڵ㱻ѡ��...
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::active()
{
	is_select = true;
}

// ----------------------------------------------------------------
//	Name��			Joint::deactive
//	Description:	�ڵ㱻�ͷ�...
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::deactive()
{
	is_select = false;
}

// ----------------------------------------------------------------
//	Name��			Joint::clear
//	Description:	
//	Return Value:	void
// ----------------------------------------------------------------
void Joint::clear()
{
	is_select = false;
	parent = NULL;
	name = "";
	joint_radius = 0.9f;
	children.clear();
	offset.setValue(0.0, 0.0, 0.0);
	screen_pos.setValue(0.0, 0.0, 0.0);

	for (size_t i=0; i<channels.size(); i++ )
	{
		SAFE_DELETE( channels[i] );
	}
	channels.clear();
}

// [3/16/2009 RenYaFei]
//		�ı�Render�ĺ������ܣ�����ѡ��...

// [3/16/2009 RenYaFei]
//	ʹ��joint_sequence_number ʧ�ܣ�ԭ����˳�����⣬�ȴ������нڵ㣬
//		Ȼ���ڵݹ���Ⱦ���������һ������������Ⱦ����ok��..
//	���ӱ���joint_id.(1-�ڵ�����)