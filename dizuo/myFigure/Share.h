#ifndef SHARE_H_
#define SHARE_H_

#include "util/Rectangle.hpp"		//gtl.hpp����λ��windows.hǰ��
#include "util/TipsBoard.h"
#include "util/SmartPtr.h"

#include "GUISystem.h"
#include "Figure.h"
#include "Joint.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "DragCamera.h"
#include "TrackUI.h"

#include <gl/glut.h>

// ----------------------------------------------------------------
//  Name:           class Share
//  Description:    �洢���е�ȫ�ֱ�����Ա
//					��һЩȫ�ֵ�define����.
//					GUISystem.cpp	---->  Share Data
//					Main.cpp		---->  Share Data
//					Mouse.cpp		---->  Share Data
//					KeyBoard.cpp	---->  Share Data
//  Create Time:    [4/5/2009 RenYaFei]
// ----------------------------------------------------------------
class Share
{
	//DATA
	static const GLint	g_iWindowWid = 1024;
	static const GLint	g_iWindowHeigh = 768;
	static bool			g_bKeepRunning;

	static SmartPtr<TrackUI>	g_pTrack;
	static SmartPtr<Figure>		g_pFigure;
	static SmartPtr<DragCamera>	g_pCamera;
	static SmartPtr<TipsBoard>	g_pInfoBoard;
	static Joint*				g_pSelectJoint;

	static int			g_frameTimeMs;
private:
	//NOT IMPLEMENT
	Share(){};

public:

	//MANIPULATORS
	static void setHelpInfo(TipsBoard* info) { g_pInfoBoard = info; }
	static void setCamera(DragCamera* camera) {g_pCamera = camera;}
	static void setTrack(TrackUI* track) {g_pTrack = track;}
	static void setFigure(Figure* figure) { g_pFigure = figure; }
	static void setSelectJoint(Joint* joint) { g_pSelectJoint = joint; }

	static void setFrameTimeMs(int frameTime) { g_frameTimeMs = frameTime; }
	static void setRunFlag(bool flag) {g_bKeepRunning = flag;}
	
	static void destroy();

	//ACCESSOR
	static SmartPtr<TipsBoard> getHelpInfo() { return g_pInfoBoard; }
	static SmartPtr<DragCamera> getCamera() {return g_pCamera;}
	static SmartPtr<TrackUI> getTrack() {return g_pTrack;}
	static SmartPtr<Figure> getFigure() { return g_pFigure; }
	static Joint* getSelectJoint() {  return g_pSelectJoint; }

	static GLint getWindowWid() { return g_iWindowWid; }
	static GLint getWindowHeight() { return g_iWindowHeigh; }
	static int   getFrameTimeMs() { return g_frameTimeMs; }
	static bool  getRunFalg()  { return g_bKeepRunning; }
}; //class Share

//DEFINE
#define BUTTON  ButtonManger::GetInstance()
#define GUI		GUISystem::GetInstance()
#define bRECT	GUISystem::GetInstance()->m_pInterface->GetBottom()
#define rRECT	GUISystem::GetInstance()->m_pInterface->GetRight()
#define cRECT	GUISystem::GetInstance()->m_pInterface->GetClient()

#endif

//////////////////////////////////////////////////////////////////////////
//  [5/6/2009 RYF]
//		ָ���set�����ӿ��е����⣬�����ڴ�й©
//				1���ڸ���֮ǰ��SAFE_DELETE
//				2��ʹ������ָ��
//		��ָ��ȫ���ĳ���SmartPtr���͵�
//		g_pSelectJointֻ��ʹ��һ���ָ�룬ǳ����