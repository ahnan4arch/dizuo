#include "Share.h"
#include "Mouse.h"

#include "util/CButton.h"
#include "Joint.h"

#define ROTATE_SPEED		1.0		// SPEED OF ROTATION

MouseManger::MouseManger()
	: isDrag(false)
	, isTrack(false)
	, isEdit(false)
{}

MouseManger::~MouseManger()
{}


// ----------------------------------------------------------------
//	Name��			MouseManger::OnMouseHandle
//	Description:	1.��������client����
//					�����Ҽ��϶������������ת
//					2.��Ӧ��ť�����¼�
//					���ţ���ͣ��ǰ��һ֡������һ֡
//	Return Value:	void
// ----------------------------------------------------------------
void MouseManger::OnMouseHandle(int button, int state, int x, int y)
{
	//����
	if(button==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		//computeHome();
		Share::getCamera()->computeHome();
		Share::getTrack()->ComputerHome();
	}
	
	//�Ҽ�drag
	if( GUI->m_pInterface->GetClient().Intersect(x, y) && isDrag )
	{
		Share::getCamera()->OnMouseHandle(button, state, x, y);
	}
	//���track
	if( GUI->m_pInterface->GetClient().Intersect(x, y) && isTrack )
	{
		Share::getTrack()->OnMouseHandle(button, state, x, y);
	}
	
	//button hit
	if(button==GLUT_LEFT_BUTTON)
	{
		switch(state)
		{
		case GLUT_DOWN:
			if( BUTTON->GetButton( std::string("play") )->OnMouseDown(x, y) )
				Share::getFigure()->play();

			if( BUTTON->GetButton( std::string("pause") )->OnMouseDown(x, y) )
				Share::getFigure()->pause();

			if( BUTTON->GetButton( std::string("forward") )->OnMouseDown(x, y) )
				Share::getFigure()->forward();

			if( BUTTON->GetButton( std::string("backward") )->OnMouseDown(x, y) )
				Share::getFigure()->backward();

			if( BUTTON->GetButton( std::string("edit") )->OnMouseDown(x, y) )
			{
				ActiveEdit();
				DeActiveDrag();
				DeActiveTrack();
			}

			if( BUTTON->GetButton( std::string("drag") )->OnMouseDown(x, y) )
			{
				ActiveDrag();
				DeActiveTrack();
				DeActiveEdit();
			}

			if( BUTTON->GetButton( std::string("track") )->OnMouseDown(x, y) )
			{
				ActiveTrack();
				DeActiveEdit();
				DeActiveDrag();
			}

			// �������ת��ť ��ֹ��isDrag��isTrack

			// Ϊ����ת�Ǽ�׼��
			vMousePos.setValue(x, y);
			if( Share::getSelectJoint() )
			{
				Joint* pJoint = Share::getSelectJoint();
				for( size_t i(0); i<pJoint->channels.size(); i++ )
				{
					Joint::Channel *channel = pJoint->channels[i];
					float rot_data = Share::getFigure()->get_motion( Share::getFigure()->get_current_framenum(), channel->index);

					if ( channel->type == Joint::Xrot )
						vGrabRot.x() = rot_data;
					else if ( channel->type == Joint::Yrot )
						vGrabRot.y() = rot_data;
					else if ( channel->type == Joint::Zrot )
						vGrabRot.z() = rot_data;
				}
			}

			break;
		case GLUT_UP:
			( BUTTON->GetButton( std::string("play") ) )->OnMouseUp();
			( BUTTON->GetButton( std::string("pause") ) )->OnMouseUp();
			( BUTTON->GetButton( std::string("forward") ) )->OnMouseUp();
			( BUTTON->GetButton( std::string("backward") ) )->OnMouseUp();
			
			if( !isEdit )
				( BUTTON->GetButton( std::string("edit") ) )->OnMouseUp();
			if( !isTrack )
				( BUTTON->GetButton( std::string("track") ) )->OnMouseUp();
			if( !isDrag )
				( BUTTON->GetButton( std::string("drag") ) )->OnMouseUp();

			break;
		}
	}
}

// ----------------------------------------------------------------
//	Name��			MouseManger::OnMotionHandle
//	Description:	�Ҽ��϶��������ת���ƶ���ť
//	Return Value:	void
// ----------------------------------------------------------------
void MouseManger::OnMotionHandle(int x, int y)
{
	// �ر�Drag��trackģʽ��������ת����
//  	isDrag = false;
//  	isTrack = false;
	
	// ��תѡ�еĽڵ� ���²�λ��skeleton
	if( isEdit )
		this->MoveSelectedSkeletons(x, y);
	
	//Right button Drag
	if( isDrag )
		Share::getCamera()->OnMotionHandle(x, y);

	//Left button TrackBall
	if( isTrack )
		Share::getTrack()->OnMotionHandle(x, y);
	
	//Move the button
	//....

	glutPostRedisplay();
}

// ----------------------------------------------------------------
//	Name��			MouseManger::MoveSelectedSkeleton
//	Description:	��תѡ�нڵ����µ�����skeleton
//	Return Value:	void
// ----------------------------------------------------------------
void MouseManger::MoveSelectedSkeletons(int x, int y)
{
	int mousey =  Share::getWindowHeight() - y;

	Joint* pJoint = Share::getSelectJoint();
	//if ( !( ( Share::getSelectJoint() ).isNull() ) )
	if (pJoint==NULL)
		return;

	float frame = Share::getFigure()->get_current_framenum();
	for( size_t i(0); i<pJoint->channels.size(); i++ )
	{
		Joint::Channel *channel = pJoint->channels[i];
		//�ı�motion data
		if ( channel->type == Joint::Xrot && (x - vMousePos.x()) != 0 )
		{
			float value = vGrabRot.x() + ( (float)ROTATE_SPEED * (x - vMousePos.x()) );
			Share::getFigure()->set_motion( frame, channel->index, value );
		}
		else if ( channel->type == Joint::Yrot && (mousey - vMousePos.y()) != 0 )
		{
			float value = vGrabRot.y() + ( (float)ROTATE_SPEED * (mousey - vMousePos.y()) );
			Share::getFigure()->set_motion( frame, channel->index, value );
		}
		else if ( channel->type == Joint::Zrot && (mousey - vMousePos.y()) != 0 && (x - vMousePos.x()) != 0 )
		{
			float delta = ( (float)ROTATE_SPEED * (mousey - vMousePos.y()) ) + ( (float)ROTATE_SPEED * (x - vMousePos.x()) );
			float value = vGrabRot.z() + delta / 2.0f;
			Share::getFigure()->set_motion( frame, channel->index, value );
		}
	}
}


// ----------------------------------------------------------------
//	Name��			MouseManger::PickJointByMouse
//	Description:	ͨ�����ֱ�ӵ��ѡȡ�ڵ�
//	Return Value:	void
// ----------------------------------------------------------------
void MouseManger::PickJointByMouse(int button, int state, int x, int y)
{
	if( button != GLUT_LEFT || state != GLUT_DOWN)
		return;

	#define MyVector Share::getFigure()->get_joints_vector()

	Share::getFigure()->reset_joints();
	for (size_t i(0); i<MyVector.size(); i++)
	{
		//ѡ�нڵ���:
		if( x > MyVector[i]->screen_pos[0] - PickThreshold &&
			x < MyVector[i]->screen_pos[0] + PickThreshold &&
			y > MyVector[i]->screen_pos[1] - PickThreshold &&
			y < MyVector[i]->screen_pos[1] + PickThreshold )
		{
			MyVector[i]->active();
			Share::setSelectJoint( MyVector[i] );
		}
	}
}

// ----------------------------------------------------------------
//	Name��			MouseManger::SelectJointByName
//	Description:	ͨ����ߵĽڵ�nameѡȡ�ڵ�
//	Return Value:	void
// ----------------------------------------------------------------
void MouseManger::SelectJointByName(int button, int state, int x, int y)
{
	//�ұ߽ṹ��ѡȡ
	if(button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	if( Share::getFigure()->font_container->OnMouseDown(x, y) )
	{
		//�ڼ���һ��֮ǰ�����е�Jointִ��reset
		Share::getFigure()->reset_joints();
		(Share::getFigure()->get_joint( Share::getFigure()->font_container->GetSelectName() ))->active();

		Share::setSelectJoint( Share::getFigure()->get_joint( Share::getFigure()->font_container->GetSelectName() ) );
	}
	else
		Share::getFigure()->reset_joints();
}