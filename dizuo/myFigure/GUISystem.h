/*************************************************************/
/**					Filename: Gui.H				            **/
/**					Version:  Common                        **/
/**   History:                                              **/
/**	  3/14/2009		RYF - Creation							**/
/**					Email:dizuo@126.com						**/
/**					All Rights Reserved.					**/
/*************************************************************/
#ifndef GUISYSTEM_H_
#define GUISYSTEM_H_

#include "util/Singleton.hpp"
#include "util/ProgressBar.h"
#include "util/timer.h"

#include "MainFrame.h"
#include "ButtonManger.h"


class Font;

class GUISystem : public Singleton<GUISystem>
{
	friend class Singleton<GUISystem>;
protected:
	GUISystem();
	~GUISystem();

public:
	//����
	void Render();

	//��������ʼ��
	//����ͳһ�����Ͻǿ�ʼ
	bool SetUp();

	enum { PICNUM = 7 };
	struct ButtonInfo {
		char* path;
		char* name;
	};
	static ButtonInfo m_vButtonInfo[ PICNUM ];

	Font			*m_pFps;
	ProgressBar		*m_pBar;
	Mainframe		*m_pInterface;
};

//	Buttonר��дһ��������
//  [5/15/2009 RYF]
//		���Կ���д��һ��������

//		���԰�path��name��pFuncд��һ���ṹ��,
//		��ť��ͼƬ���¼� ��ϵ����...
#endif