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
#define MAX 110000    // Maximum number of task nodes in DAG
#define MAXP 4

///////////////////////////////////////////////////////////////////////////////
int n;                              //Number of nodes in DAG
int size_core;                      //Total number of core in machine

struct node                         // Structure of node in dag
{
    int key;
    int ranku;
    int rankd;
    int cost;
    int coreid;
    double avgcost;
    node()
    {
        key=0;
        ranku=0;
        rankd=0;
        cost=0;
        coreid=0;
        avgcost=0.0;
    }
};

/*sorted list structure of task node in dag according to their upward rank and downward rank*/
struct slist
{
    int ranku;
    int rankd;
    int key;
};

struct core
{
    int id;
    bool status;                // busy or ideal
    int speed;                  // speed of processor
    int EST;                    // Earliest start time
    int EFT;                    // Earliest finish time
};

struct schedule
{
    int start;
    int end;
    int processor;
    int task;
};
////////////////////////////////////////////////////////////////////////////////////
node nodes[MAX];
vector<int> adj[MAX];
slist sorted_list[MAX];
vector<core> cores;
vector<schedule> sch;
int task_to_core[MAX];              // Mapping Task->Processor
int core_to_task[MAX];              // Mapping Proccessor->Task
/////////////////////////////////////////////////////////////////////////////////////

///// this func will find the source task nodes in DAG: O(n)
vector<int> find_root()
{
    int visit[MAX];
    int root;
    memset(visit,0,sizeof(visit));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            visit[adj[i][j]]++;
        }
    }

    vector<int> roots;

    for(int i=1;i<=n;i++)
    {
        if(visit[i]==0)
        {
            roots.push_back(i);
        }
    }
    return roots;
}

////////////////////////////////////////////////////////////////////////////////
/*Compare two node according to their rank*/

bool comp(slist n1,slist n2)
{
    if(n1.ranku>n2.ranku)
    {
        return true;
    }
    return false;
}


bool compp(core c1,core c2)
{
    if(c1.EST>c2.EST)
    {
        return true;
    }
    if(c1.EST==c2.EST)
    {
        return c1.speed<c2.speed;
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////////
/*Calculation upward rank of each task node: O(n)*/

int upward_rank(int root)
{
    if(adj[root].size()==0)
    {
        nodes[root].ranku=nodes[root].cost;
        return nodes[root].cost;
    }
    int maxv=INT_MIN;
    for(int i=0;i<adj[root].size();i++)
    {
        int temp=upward_rank(adj[root][i]);
        maxv=max(temp,maxv);
    }

    nodes[root].ranku=maxv+nodes[root].cost;
    return nodes[root].ranku;
}

//////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
/*Implementing CPOP heuristics*/

void cpop_run()
{
    vector<int> root;
    root=find_root();
    cout<<"Roots are:"<<endl;

    for(int i=0;i<root.size();i++)
    {
        cout<<root[i]<<endl;
    }

    line;
    upward_rank(root[i]);


}


////////////////////////////////////////////////////////
void display()
{
    cout<<" ";
    for(int i=0;i<=10;i++)
    {
        cout<<"  "<<i;
    }
    cout<<endl;
    for(int j=1;j<=3;j++)
    {
        cout<<j;
        for(int i=0;i<sch.size();i++)
        {
            if(sch[i].processor==j)
            {
                for(int j=0;j<sch[i].start;j++)
                    cout<<"  ";
                for(int j=sch[i].start;j<=sch[i].end;j++)
                {
                    cout<<" "<<sch[j].task;
                }
            }
        }
        cout<<endl;
    }

}

void init_core()
{
    for(int i=1;i<=3;i++)
    {
        core temp;
        temp.id=i;
        temp.status=false;
        temp.speed=1<<(i-1);
        temp.EST=0;
        temp.EFT=0;
        cores.push_back(temp);
    }
}


int main()
{
    n=3;
    //////////////////////////////////////////////////////////////
    for(int i=1;i<=5;i++)
    {
        nodes[i].cost=(1+rand()%5)*4;
        nodes[i].key=i;
        cout<<"Index="<<i<<" "<<"Cost="<<nodes[i].cost<<endl;
    }


    /////////////////////////////////////////////////////////////
    //line;
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(5);
    line;

    for(int i=1;i<=5;i++)
    {
        cout<<i<<": ";
        for(int j=0;j<adj[i].size();j++)
        {
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    line;

    init_core();
    for(int i=0;i<cores.size();i++)
    {
        cout<<cores[i].id<<" "<<cores[i].speed<<endl;
    }

    line;
    cpop_run();
    return 0;
}
