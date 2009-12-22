#ifndef __CTEXTURE_H_
#define __CTEXTURE_H_

#include "global.h"
#include "Singleton.hpp"
#include <string>
#include <list>

class CTexture
{
public:
	CTexture();
	~CTexture();

	GLuint Create(const char* filename, int wrap);
	int LoadTGA(const char * filename);

	int Width;
	int Height;
	int BytesPerPixel;
	unsigned char * Data;
	
	GLuint GetTexId()const { return m_iTexID; };
	const char* GetName()  const { return m_sName.c_str(); };
private:
	std::string m_sName;
	GLuint m_iTexID;
};

class CTextureManager : public Singleton<CTextureManager>
{
	friend class Singleton<CTextureManager>;
protected:
	CTextureManager(){};
	~CTextureManager(){ CleanAllTextures(); }

public:
	// functions
	void Initialize(){ m_texlist.clear(); };
	unsigned int LoadTexture( const char *filename )
	{
		for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
		{
			if( strcmp( (*itor)->GetName(), filename ) == 0 )
				return (*itor)->GetTexId();
		}
		CTexture *tex = new CTexture;
		m_texlist.push_back( tex );
		return tex->Create( filename, GL_CLAMP );
	}
	void DeleteTexture( unsigned int id )
	{
		for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
		{
			if( (*itor)->GetTexId() == id )
			{
				delete (*itor);
				itor = m_texlist.erase( itor );
			}
		}
	}
	void CleanAllTextures( void )
	{
		for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
		{
			SAFE_DELETE(*itor);
		}
	}

private:
	// linked texture list
	typedef std::list<CTexture *>	TextureList;
	typedef TextureList::iterator	TListItor;

	TextureList						m_texlist;
};

// �궨�巽��ʹ�ã�
#define TEXTURE CTextureManager::GetInstance() 

//////////////////////////////////////////////////////////////////////////
//ò��TGA������32λ��.....

// [3/3/2009 RenYaFei]
//	������CTextureManger�����࣬
//	�����Ҫ��������ֻ��Ҫ�Ĳ����У�Initialize
//		1: ��ʼ��	CTextureManger::GetInstance()->Initialize();
//		2: ��������	TexID = CTextureManger::GetInstance()->LoadTexture("name.TGA");
//		3: ����ʹ�� glBindTexture(GL_TEXTURE_2D, TexID);
//		4: ��		CTextureManger::FreeInstance();

#endif
