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
int pnum;                      //Total number of core in machine

struct node                         // Structure of node in dag
{
    int key;
    double ranku;
    double cost;
    int coreid;
    double avgcost;
    bool status;
    double EST;
    double EFT;
    bool visit;
    node()
    {
        key=0;
        ranku=0;
        cost=0;
        coreid=0;
        avgcost=0.0;
        status=false;
        EST=0.0;
        EFT=0.0;
        visit=false;
        ranku=-1;
    }
};

struct slist                        // sorted list structure of task node in dag according to their upward rank
{
    int ranku;
    int key;
};

struct core
{
    int id;
    bool status;                // busy or ideal
    double speed;                  // speed of processor
    double EST;                    // Earliest start time
    double EFT;                    // Earliest finish time
    double cost;
    core()
    {
        status=false;
        EST=0.0;
        EFT=0.0;
    }
};

struct schedule
{
    double start;
    double end;
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

class Compare
{
public:
    bool operator() (node node1, node node2)
    {
        if(node1.ranku!=node2.ranku)
        {
            return node1.ranku<node2.ranku;
        }
        else
        {
            return node1.key<node2.key;
        }
    }
};
/////////////////////////////////////////////////////////////////////////////////
/*Calculation upward rank of each task node: O(n)*/

double upward_rank(int root)
{
    //cout<<"hello"<<endl;
    if(nodes[root].ranku>=0){return nodes[root].ranku;}
    if(adj[root].size()==0)
    {
        nodes[root].ranku=nodes[root].cost;
        return nodes[root].cost;
    }
    double maxv=DBL_MIN;
    for(int i=0;i<adj[root].size();i++)
    {
        double temp=upward_rank(adj[root][i]);
        maxv=max(temp,maxv);
    }

    nodes[root].ranku=maxv+nodes[root].cost;
    return nodes[root].ranku;
}


//////////////////////////////////////////////////////////////////////////////////

void display()
{
    //line;
    double make_span=0;
    double total_cost=0;
    for(int i=0;i<sch.size();i++)
    {
        make_span=max(make_span,sch[i].end);
        //cout<<"task ="<<sch[i].task<<" : processor ="<<sch[i].processor<<" : start="<<sch[i].start<<" : end="<<sch[i].end<<endl;
        double x=((sch[i].end-sch[i].start)*cores[sch[i].processor].cost);
        //cout<<"x="<<x<<endl;
        total_cost= total_cost + ((sch[i].end-sch[i].start)*cores[sch[i].processor].cost);
    }
    cout<<n-2<<" "<<make_span<<" "<<total_cost<<endl;
    //line;
}

/////////////////////////////////////////////////////////////
/*Implementing HEFT heuristics algorithm*/

void heft_algo()
{
    //vector<int> root;
    //root=find_root();
    //cout<<"Roots are:"<<endl;

    /*for(int i=0;i<root.size();i++)
    {
        cout<<root[i]<<endl;
    }*/

    //line;
    int temp_root=1;
    /*for(int i=0;i<root.size();i++)
    {
        upward_rank(root[i]);
        temp_root=root[i];
    }*/

    upward_rank(1);

    /*for(int i=1;i<=n;i++)
    {
        cout<<"Index="<<i<<" "<<nodes[i].ranku<<endl;
    }*/

    //line;

    /*for(int i=1;i<=n;i++)
    {
        sorted_list[i].key=i;
        sorted_list[i].ranku=nodes[i].ranku;
    }

    sort(sorted_list+1,sorted_list+n,comp);*/
    
    priority_queue<struct node, vector<node>, Compare> pq;
    pq.push(nodes[temp_root]);
    nodes[temp_root].status=true;
    double make_span=0.0;
    while(!pq.empty())
    {

        node temp=pq.top();

        //cout<<"key="<<temp.key<<endl;
        //cout<<"EST="<<temp.EST<<endl;
        pq.pop();
        //cout<<"size="<<pq.size()<<endl;
        // Processor selection phase
        double minv=DBL_MAX;
        int idx=0;
        for(int i=0;i<cores.size();i++)
        {
            double duration=temp.cost/cores[i].speed;
            double temp_start=max(cores[i].EST, temp.EST);
            if((duration + temp_start) < minv)
            {
                minv=duration+temp_start;
                idx=i;
            }
        }
        //cout<<"minv="<<minv<<endl;

        schedule temp_sch;
        temp_sch.start=max(cores[idx].EST, temp.EST);;
        temp_sch.end=minv;
        temp_sch.task=temp.key;
        temp_sch.processor=idx;
        cores[idx].EST=minv;
        sch.push_back(temp_sch);

        for(int i=0;i<adj[temp.key].size();i++)
        {
            if(!nodes[adj[temp.key][i]].status)
            {
                nodes[adj[temp.key][i]].status=true;
                nodes[adj[temp.key][i]].EST=minv;
                //cout<<"minv1="<<nodes[adj[temp.key][i]].EST<<endl;
                pq.push(nodes[adj[temp.key][i]]);
                
                //cout<<"queue_push"<<adj[temp.key][i]<<endl;
            }
            
        }

    }
    display();
}




////////////////////////////////////////////////////////


void init_core()
{
    ifstream inp2;
    inp2.open("configuration.ip");
    inp2>>pnum;
    for(int i=0;i<pnum;i++)
    {
        core temp;
        temp.id=i;
        double x;
        inp2>>x;
        temp.speed=x;
        cores.push_back(temp);
    }
    for(int i=0;i<pnum;i++)
    {
        double x;
        inp2>>x;
        cores[i].cost=x;
    }
    inp2.close();
}

void populate_weight()
{
    ifstream inp;
    inp.open("weight.ip");

    nodes[1].key=1;
    nodes[1].cost=0;
    nodes[n].key=n;
    nodes[n].cost=0;
    for(int i=2;i<=n-1;i++)
    {
        /*nodes[i].cost=(1+rand()%5)*4;
        nodes[i].key=i;
        cout<<"Index="<<i<<" "<<"Cost="<<nodes[i].cost<<endl;*/
        double temp;
        inp>>temp;
        //cout<<"weight temp="<<temp<<endl;
        nodes[i].cost=temp;
        nodes[i].key=i;
    }
    inp.close();
}
////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    ifstream inp1;
    inp1.open("test.ip");
    inp1>>n;
    n=n+2;
    //n=5;
    //cout<<"Number of Nodes="<<n<<endl;
    while(true)
    {
        int x,y;
        inp1>>x>>y;

        if(x==-1){break;}
        //cout<<x<<"-"<<y<<endl;
        adj[x].push_back(y);
    }
    inp1.close();
    /*-------------------------------------*/

    /*adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(5);*/
    
    populate_weight();
    //line;

    /*for(int i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for(int j=0;j<adj[i].size();j++)
        {
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    line;*/

    init_core();
    /*for(int i=0;i<cores.size();i++)
    {
        cout<<cores[i].id<<" "<<cores[i].speed<<endl;
    }
    line;*/


    heft_algo();
    return 0;
}
