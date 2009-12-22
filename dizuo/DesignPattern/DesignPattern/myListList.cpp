#include <algorithm>
#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef struct tagMember 
{ 
	char *name; 
	char *group; 
}Member; 
Member people[]=
{ 
	{"����","һ��"}, 
	{"����","һ��"}, 
	{"����","����"}, 
	{"����","����"}, 
	{"����","����"}, 
}; 

typedef list<char*> ListType;
typedef struct ListNode
{
	char* groupName;
	ListType *next;
}NodeType;

typedef list<NodeType*> myList;
typedef myList::iterator myIter;

myIter myFind(myList& mylist, char* dest)
{
	myIter it;
	for (it=mylist.begin(); it != mylist.end(); it++)
	{
		if( (*it)->groupName == dest)
			return it;
	}
	return it;
}
int main()
{
	myList classInfo;

	NodeType* pNode;
	//����ڵ�
	for(size_t i=0; i<5; i++)
	{
		//����һ�������ڵ�
		myIter it = myFind(classInfo, people[i].group);
		if( it!= classInfo.end() )	//�Ѵ���
		{
			//�洢name
			(*it)->next->push_back( people[i].name );
		}
		else	//�����µ�NodeType�ڵ�
		{
			pNode = new NodeType;
			pNode->groupName = people[i].group;
			pNode->next = new ListType;	//����list

			//�洢��ǰ��name
			pNode->next->push_back( people[i].name );
			classInfo.push_back( pNode );
		}
	}
	
	//�����
	for (myIter it=classInfo.begin(); it != classInfo.end(); it++)
	{
		cout << (*it)->groupName << ": ";
		for ( ListType::iterator bg=(*it)->next->begin(); 
			  bg != (*it)->next->end(); bg++ )
		{
			cout << (*bg) << "\t";
		}
		cout << endl;
	}

	system("PAUSE");
	return 0;
}
// 
// һ��: ����      ����
// ����: ����
// ����: ����      ����