/*For generating random weights of the task node*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
	ofstream out;
	int num=10;
	out.open("weight.ip");
	cout<<"How many nodes=";
	cin>>num;
	//srand(time(NULL));
	for(int i=0;i<num;i++)
	{
		
		int temp=((rand()%10)+1)*4;
		cout<<temp<<endl;
		out<<temp<<endl;
	}
	out.close();
	return 0;
}