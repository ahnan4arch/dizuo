#ifndef XMLSCRIPTPARSER_H_
#define XMLSCRIPTPARSER_H_

#include <iostream>
#include <string>

#include "Tree.hpp"
#include "tinyxml.h"

namespace util {
	using namespace kptree;

	template<class DataType>
	class XMLScriptParser : public tree<DataType>
	{
		std::string file_name;	//XML Script Name
		std::string m_name;		//�ö������name

		//��ֹĬ�Ϲ��캯��
		XMLScriptParser(){};
	public:
		typedef DataType Type;
		XMLScriptParser(std::string name);
		virtual ~XMLScriptParser(){};

		bool loadXMLScript();
	protected:
		bool recursParse(TiXmlElement* pTreeNode, pre_order_iterator& parent);
	};

	template<class DataType>
	XMLScriptParser<DataType>::XMLScriptParser(std::string name)
		: file_name(name)
	{}

	template<class DataType>
	bool XMLScriptParser<DataType>::loadXMLScript()
	{
		TiXmlDocument doc( file_name.c_str() );
		if (!doc.LoadFile()) 
			return false;

		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);

		// block: name
		pElem=hDoc.FirstChildElement().Element();
		// should always have a valid root but handle gracefully if it does
		if (!pElem) 
			return false;
		m_name=pElem->Value();		//m_name = "HTree"

		// save this for later
		hRoot=TiXmlHandle(pElem);

		// block: Nodes
		
		TiXmlElement* pTreeNode = hRoot.FirstChild( "Node" ).Element();
		
		Type node;
		//��ȡ��ǰ�ڵ��name: 
		const char *pName=pTreeNode->Attribute("Name");
		if (pName)
			node.name = pName;
		//��ȡ��ǰ�ڵ��type: 
		const char *pType=pTreeNode->Attribute("Type");	// "ROOT"
		if (pType)
			node.type = pType;

		pre_order_iterator parent = begin();
		parent = insert(parent, node );

		// ����XML�ļ�
		return recursParse(  pTreeNode, parent );
	}

	template<class  DataType>
	bool XMLScriptParser<DataType>::recursParse( TiXmlElement* pTreeNode, 
												 pre_order_iterator& parent )
	{
		if ( pTreeNode == NULL ) 
			return true;

		// process block����ѭ������Ҳ�ǿ��Եģ�ò�����𲻴�

		for ( pTreeNode = pTreeNode->FirstChildElement(); 
			  pTreeNode; 
			  pTreeNode = pTreeNode->NextSiblingElement() )
		{
			{	//Process Block
				Type node;

				//��ȡ��ǰ�ڵ��name: 
				const char *pName=pTreeNode->Attribute("Name");
				if (pName) node.name=pName;
				//��ȡ��ǰ�ڵ��type: 
				const char *pType=pTreeNode->Attribute("Type");
				if (pType) node.type=pType;

				pre_order_iterator child = append_child(parent, node);
				//	����һ��Type������append_child����

				recursParse( pTreeNode, child );
			}
		}

		return true;
	}
}

//////////////////////////////////////////////////////////////////////////
//	4/29/2009	-	RYF
//	ʵ����XML�ű�������û�б�Ҫ�Լ�д��^_^

#endif