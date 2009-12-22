#include <iostream>
#include <vector>
using namespace std;

//... forward declarations for all DocElement derivatives ...
class Paragraph;
class RasterBitmap;
class DocElement;

class DocElementVisitor
{
public:
	// unique bouncing virtual function 

// 	virtual void VisitParagraph(Paragraph&) = 0;
// 	virtual void VisitRasterBitmap(RasterBitmap&) = 0;
	//�������أ��б�����ȥ���е�����
	virtual void Visit(Paragraph&) = 0;
	virtual void Visit(RasterBitmap&) = 0;
	virtual void Visit(DocElement&) = 0;
	//... other similar functions ...
};

class DocElement
{
public:
	virtual void Accept(DocElementVisitor&) = 0;
	//...
};

class Paragraph : public DocElement
{
public:
	Paragraph()
		: chars_(0), words_(0)
	{}
	Paragraph(int chars, int words)
		: chars_(chars), words_(words)
	{}
	const int NumChars(){return chars_;}
	const int NumWords(){return words_;}

	void Accept(DocElementVisitor& v)
	{
		//v.VisitParagraph(*this);
		v.Visit(*this);
	}

private:
	unsigned int 
		chars_,
		words_;
};

class RasterBitmap : public DocElement
{
public:
	void Accept(DocElementVisitor& v)
	{
		//v.VisitRasterBitmap(*this);
		v.Visit(*this);
	}
};


class DocStats : public DocElementVisitor
{
public:
	DocStats(): chars_(0), nonBlankChars_(0),
				words_(0), images_(0)
	{}
	virtual void Visit(Paragraph& par)
	{
		chars_ += par.NumChars();
		words_ += par.NumWords();
	}
	virtual void Visit(RasterBitmap&)
	{
		++images_;
	}
	virtual void Visit(DocElement&){}
	void Display()
	{
		cout<<"the chars has: "<<chars_<<endl;
		cout<<"the nonBlankChars has: "<<nonBlankChars_<<endl;
		cout<<"the words has: "<<words_<<endl;
		cout<<"the images has: "<<images_<<endl;
	}
	//...
private:
	unsigned int
		chars_,
		nonBlankChars_,
		words_,
		images_;
};

class Document
{
public:
	Document()
	{}
	~Document()
	{
		#define SAFE_DELETE(p) {if(p){ delete p; p=NULL;} }
		vector<DocElement*>::iterator iter;
		for (iter=m_DocElemVec.begin(); iter!=m_DocElemVec.end(); iter++)
			if( *iter )		SAFE_DELETE( *iter );
		
		m_DocElemVec.clear();
	}
	void push_back(DocElement* pDocment)
	{
		m_DocElemVec.push_back(pDocment);
	}
	void DisplayStatistics()
	{
		DocStats statistics;
		for (int i=0; i<m_DocElemVec.size(); i++)
			m_DocElemVec[i]->Accept(statistics);		//��OSG�еľ��˵�����...

		statistics.Display();
	}
	
private:
	vector<DocElement*> m_DocElemVec;
};


int main()
{
	int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); 
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF; 
	_CrtSetDbgFlag( tmpFlag );

	Document doc;
	Paragraph *p=new Paragraph(1000, 100);	//���£�
	RasterBitmap *r=new RasterBitmap;		//ͼƬ��
	doc.push_back( p );
	doc.push_back( r );
	doc.DisplayStatistics();

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//�м�������visitor�ľ���ϸ��
//����һ��DocElementVisitor�࣬�ܺõ��ν���DosStat��Paragraph��
//		��RasterBitmap
//////////////////////////////////////////////////////////////////////////
//osg::traverse()			����
//osg::apply()				Ӧ��
//osg::accept()				���ܷ��ʣ�

/*
the chars has: 1000
the nonBlankChars has: 0
the words has: 100
the images has: 1
�밴���������. . .*/
