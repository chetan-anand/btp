#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef vector <int> vi;
typedef pair <int,int> pii;
#define pb push_back
#define mp make_pair
#define gi(n) scanf("%d",&n)
#define gl(n) scanf("%lld",&n)
#define gs(n) scanf("%s",n);
#define pi(n) printf("%d\n",n)
#define pl(n) printf("%lld\n",n)
#define ps(n) printf("%s\n",n);
#define rep(i,n) for(int i=0;i<n;i++)
#define fi(i,a,n) for(int i=a;i<=n;i++)
#define fd(i,n,a) for(int i=n;i>=a;i--)
#define input(f) freopen("f.txt","r",stdin)
#define line cout<<"\n-----------------------------------------"<<endl


/*
	DAG parameters
	-----------------------------------------
	1.	Number of nodes
	2.	Number of Levels in DAG
	3.	Number of children
	4.	Number of parents
*/
int nodesNum;			//Number of nodes
int level;				//Levels of DAG
int numChild;			//Number of children
int numParent;			//Numbers of parents

bool isChild[1000000];
bool randBool(int prob)
{
	//srand(time(NULL));
	int temp=rand()%100 + 1;
	if(temp<=prob)
		return true;
	else
		return false;
}

void dagGen(int tc)
{
	ofstream dot;
	dot.open("graph1.gv");
	for(int k=1;k<=tc;k++)
	{
		memset(isChild,0,sizeof(isChild));
		cout<<nodesNum<<endl;
		dot<<"digraph G {"<<endl;
		for(int i=1;i<=nodesNum;i++)
		{
		    //srand(time(NULL));
			bool flag=false;
			int cntChild=0;
			for(int j=i+1;j<=nodesNum;j++)
			{
				if(cntChild>=numChild)
				{
					break;
				}
				if(randBool(50))
				{
					isChild[j]=true;
					cout<<i+1<<" "<<j+1<<endl;
					dot<<i+1<<"->"<<j+1<<endl;
					flag=true;
					cntChild++;
				}
			}
			if(!flag)
			{
				cout<<i+1<<" "<<nodesNum+2<<endl;
				dot<<i+1<<"->"<<nodesNum+2<<endl;
			}

		}

		//Making sentinal root with zero computation value
		for(int i=1;i<=nodesNum;i++)
		{
			if(!isChild[i])
			{
				cout<<"1"<<" "<<i+1<<endl;
				dot<<"1"<<"->"<<i+1<<endl;
			}
		}
		cout<<"-1 -1"<<endl;
		dot<<"}"<<endl;
	}

}

int main()
{
	
	int tc;
	//cout<<"Number of test cases to generate: ";
	//cin>>tc;
	tc=1;
	//cout<<endl;
	//cout<<"Enter number of task nodes: ";
	cin>>nodesNum;
	//cout<<endl;
	//cout<<"Enter maximum number of children a task node can have: ";
	cin>>numChild;
	//cout<<"chetan"<<endl;
	dagGen(tc);
	return 0;
}
