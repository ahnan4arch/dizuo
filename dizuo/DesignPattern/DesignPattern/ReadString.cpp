#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int count_three = 0;
	int count[127] = {0};

	ifstream file_stream( "data//test.txt" );
	istream_iterator<string> bg_it(file_stream);
	istream_iterator<string> sentinel;
	vector<string> buffers(bg_it,sentinel);

	//�������е�����
	for( int i=0; i<buffers.size(); i++ )
	{
		if( buffers[i].size()==3 )
			count_three++;

		if( buffers[i].size()==1 )
			count[ buffers[i][0] ]++;
	}

	cout << "��λ��������" << count_three << endl;

	for(int i(0); i<127; i++)
	{
		if(count[i])
			cout << "the " << (char)i << "'s number is: " << count[i] << endl;
	}
 	return 0;
}
// ��λ��������3
// the A's number is: 1
// the B's number is: 1
// the C's number is: 1
// �밴���������. . .