#include "util/Helper.h"
#include "util/global.h"
#include "util/CButton.h"
#include "util/SmartPtr.h"

#include "util/Font.h"

#include "ButtonManger.h"

#include "GUISystem.h"
#include "Share.h"

// ͼƬ·��
GUISystem::ButtonInfo GUISystem::m_vButtonInfo[ PICNUM ] = {
	{"data/play_128_64.tga", "play"},
	{"data/pause_128_64.tga", "pause"},
	{"data/for_128_64.tga", "forward"},
	{"data/back_128_64.tga", "backward"},
	{"data/edit_128_64.tga", "edit"},
	{"data/track_128_64.tga", "track"},
	{"data/drag_128_64.tga", "drag"}
};

GUISystem::GUISystem()
	: m_pInterface(0), m_pBar(0), m_pFps(0)
{};

GUISystem::~GUISystem()
{
	SAFE_DELETE(m_pBar);
	SAFE_DELETE(m_pFps);

	SAFE_DELETE(m_pInterface);
}

void GUISystem::Render()
{
	glPushMatrix();
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);	//set font color
		CTimer::GetInstance()->Update();
		// print fps statistics
		std::string tmp = "Fps: " + Helper::Float2Str( CTimer::GetInstance()->GetFps() ); 
		m_pFps->SetStr( tmp );
		m_pFps->Render3();

		glEnable(GL_TEXTURE_2D);	//add
		{
			//render the gui...
			ButtonManger::GetInstance()->Render();
			m_pInterface->Render();

			m_pBar->setProgress(Share::getFigure()->get_current_framenum());
			m_pBar->Render();
		}glDisable(GL_TEXTURE_2D);	//add
	}glPopMatrix();
}

bool GUISystem::SetUp()
{
	//����
	CTimer::GetInstance()->Initialize();
	m_pFps = new Font(Share::getWindowWid()-150, 30, 0, (int)GLUT_BITMAP_HELVETICA_18, "Fps: ");

	//�����
	unsigned texId = TEXTURE->LoadTexture("data/bvh_backer_gui.tga");
	m_pInterface = new Mainframe(texId);

	//������...
	//λ��Ҳ�ǲ�������...
	m_pBar = new ProgressBar(8, 760, 1024, 30);

	//��ť
	const unsigned btn_wid = 100;
	const unsigned btn_hgt = 30;
	//38, 100, 110���ǲ������ã�û��ʲô����.
	unsigned btn_pos_y = (unsigned) (m_pInterface->GetBottom().m_Top) + 45;//��ť��y����
	unsigned btn_bg_pos_x = 40;	//��һ����ťx����
	unsigned btn_ofset_x = 40;		//��ť֮���x�������

	CTextureManager::GetInstance()->Initialize();
	SmartPtr<CButtonMovable> pButton;

	for (size_t i(0); i<PICNUM; i++)
	{
		texId = TEXTURE->LoadTexture( m_vButtonInfo[i].path );
		pButton = new CButtonMovable(btn_bg_pos_x + (btn_wid + btn_ofset_x) * i, btn_pos_y, btn_wid, btn_hgt );
		pButton->SetTexId( texId );

		ButtonManger::GetInstance()->AddButton( std::string( m_vButtonInfo[i].name ),
												pButton );
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// ��figure����ȫ�־�̬���У�����...