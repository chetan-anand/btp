#include <bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
using namespace std;
int num_nodes;

struct node
{
    int data;
    struct node *next;
};

struct schedulenode
{
    int node_id;
    double start_time;
    double finish_time;
    struct schedulenode *next;
};

struct couple
{
    int a;
    double b;
};


void insertion_beg(struct node **head,int key)
{
    struct node * newNode;
    newNode=(struct node *)malloc(sizeof(struct node));
    newNode->data=key;
    newNode->next=*head;
    *head=newNode;
    return;
}

void insertion_end(struct schedulenode ** head, int id,double start,double finish)
{
    struct schedulenode *newNode,*temp;
    newNode=(struct schedulenode *)malloc(sizeof(struct schedulenode));
    newNode->node_id=id;
    newNode->start_time=start;
    newNode->finish_time=finish;
    newNode->next=NULL;
    temp=*head;
    if(temp!=NULL)
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newNode;
    }
    else
    {
        *head=newNode;
    }

}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void print1(struct schedulenode *head)
{
    while(head)
    {
        printf("%d\t%lf\t%lf\t",head->node_id,head->start_time,head->finish_time);
        head=head->next;
    }
    printf("\n");
}

void print(struct node *head)
{
    while(head)
    {
        printf("%d\t",head->data);
        head=head->next;
    }
    printf("\n");

}

void print_scheduleLength(double *p_available,int pnum)
{
    int i;
    double max=p_available[0];
    for(i=0;i<pnum;i++)
    {
        if(p_available[i]>max)
            max=p_available[i];
    }

    printf("%lf",max);
}

void print_scheduleCost(double *pcost,int pnum)
{
    int i;
    double sum=0;
    for(i=0;i<pnum;i++)
    {
        sum+=pcost[i];
    }

    printf("%lf",sum);
}

void print_scheduling(struct schedulenode **scheduleList,int pnum)
{
    int i;
    struct schedulenode *temp;
    printf("Scheduling of tasks on each processors\n");
    for(i=0;i<pnum;i++)
    {
        printf("%d: ",i+1);
        temp=scheduleList[i+1];
        while(temp)
        {
            printf("%d (%lf,%lf)\t",temp->node_id,temp->start_time,temp->finish_time);
            temp=temp->next;
        }
        printf("\n");
    }
}

int comp(const void  *e1,const void *e2)
{
    struct couple *f1=(struct couple *)e1;
    struct couple *f2=(struct couple *)e2;
    int a1=(int)f1->b;
    int a2=(int)f2->b;


    return(a1-a2);

}

void Sort_a_on_cost(int *arr,double *cost,int n)
{
    int i;
    struct couple *c=(struct couple *)malloc(sizeof(struct couple)*n);

    for(i=0;i<n;i++)
   {
       c[i].a=arr[i];
       c[i].b=cost[i];
   }

  qsort(c,sizeof(c)/sizeof(c[0]),sizeof(c[0]), comp);

  for(i=0;i<n;i++)
   {
       arr[i]=c[i].a;

   }

}

void WaveFront(struct node **List,double *cost,int n,double *pspeed,double *pprice,int pnum)
{
    //printf("inside WaveFront\n%d\n",n);
    int n_schedule=0,i,select_t,select_p;
    double max=0,min=1000000000000000000;
    double start_time[n],finish_time[n];
    struct node *temp;
    struct schedulenode *temp1;
    struct schedulenode *scheduleList[pnum+1];
    int *schedule=(int *)malloc(sizeof(int)*n);
    int *indegree=(int *)malloc(sizeof(int)*n);
    double *pcost=(double *)malloc(sizeof(double)*pnum);
    double *p_available=(double *)malloc(sizeof(double)*pnum);
    double final_avail=0;
    double temp_start_time=0;
    int *arr,n_free;
    //double *temp_cost;              //Earlier it was double pointer
    int *temp_cost;
    //printf("before  initialisation\n");
    for(i=0;i<n;i++)
    {
        schedule[i]=0;
        indegree[i]=0;
        start_time[i]=0;
        finish_time[i]=0;
    }

    for(i=0;i<pnum;i++)
    {
        pcost[i]=0;
        p_available[i]=0;
    }
    //printf("after initialisation\n");
    for(i=0;i<pnum+1;i++)
        scheduleList[i]=NULL;
    // finding indegree of the nodes.
    //printf("before finding indegree\n");
    for(i=0;i<n;i++)
    {
        temp=List[i+1];
        //print(temp);
        while(temp)
        {
            indegree[(temp->data)-1]++;
            temp=temp->next;
        }
    }

    //printf("after finding indegree\n//printing indegree of nodes\n");
    for(i=0;i<n;i++)
    {
        //printf("%d\t",indegree[i]);
    }
    //printf("\n");

    while(n_schedule<n)
    {
        n_free=0;
        max=-1;
        arr=(int *)malloc(sizeof(int)*1);
        temp_cost=(int *)malloc(sizeof(int)*1);
        for(i=0;i<n;i++)
        {

            if(indegree[i]==0 && schedule[i]==0)
            {
                n_free++;
                arr=(int *)realloc(arr,n_free);
                temp_cost=(int *)realloc(temp_cost,n_free);
                arr[n_free-1]=i;
                temp_cost[n_free-1]=cost[i];
            }
        }

    /*
        Sort_a_on_cost(arr,temp_cost,n_free);

        //printf("Array of Free nodes\n");
        for(i=0;i<n_free;i++)
        {
            //printf("%d\t",arr[i]);
        }

        //printf("\n");
*/

        for(i=0;i<n_free;i++)
        {
            select_t=arr[i];

            min=10000000000000000;

            //printf("Task selected %d with start time %lf\n\n",select_t+1,start_time[select_t]);

            for(i=0;i<pnum;i++)
            {
                if(start_time[select_t]>p_available[i])
                    final_avail=start_time[select_t];
                else
                    final_avail=p_available[i];

                /*
                if((final_avail+(cost[select_t]/pspeed[i]))< min)
                {
                    min=final_avail+(cost[select_t]/pspeed[i]);
                    select_p=i;
                    //printf("processor slected: %d\tmin: %lf\tfinal_available: %lf\n",select_p+1,min,final_avail);
                    temp_start_time=final_avail;
                }

                */


                if(((cost[select_t]/pspeed[i])*pprice[i])< min)
                {
                    min=(cost[select_t]/pspeed[i])*pprice[i];
                    select_p=i;
                    //printf("processor slected: %d Min Processor Cost: %lf\tfinal_available: %lf\n",select_p+1,min,final_avail);
                    temp_start_time=final_avail;
                }
                else if(((cost[select_t]/pspeed[i])*pprice[i]) == min)
                {
                    if(temp_start_time > final_avail)
                    {
                        select_p=i;
                        temp_start_time=final_avail;
                    }
                }

            }

            schedule[select_t]=1;

            temp=List[select_t+1];
            while(temp!=NULL)
            {
                indegree[(temp->data)-1]--;
                temp=temp->next;
            }
            //printf("indegree after scheduling %d node on %d processor\n",select_t+1,select_p+1);
            for(i=0;i<n;i++)
            {
                //printf("%d\t",indegree[i]);
            }
            //printf("\n");

            start_time[select_t]=temp_start_time;
            p_available[select_p]=temp_start_time+cost[select_t]/pspeed[select_p];
            finish_time[select_t]=p_available[select_p];

            temp=List[select_t+1];
             while(temp!=NULL)
            {
                if(start_time[i]==0)
                    start_time[(temp->data-1)]+=finish_time[select_t];
                else
                {
                    if(finish_time[select_t]>start_time[(temp->data)-1])
                        start_time[(temp->data-1)]=finish_time[select_t];
                }
                temp=temp->next;
            }


            //printf("start time after scheduling %d node on %d processor\n",select_t+1,select_p+1);
            for(i=0;i<n;i++)
            {
                //printf("%lf\t",start_time[i]);
            }
            //printf("\n");
            pcost[select_p]+=(cost[select_t]/pspeed[select_p])*pprice[select_p];

            insertion_end(&scheduleList[select_p+1],select_t+1,start_time[select_t],finish_time[select_t]);
            //print1(scheduleList[select_p+1]);

            n_schedule++;
        }

        free(arr);
        free(temp_cost);


    }

    //printf("--------------------------------------------------------------------------------");
    //printf("\n");
    print_scheduleLength(p_available,pnum);
    printf(" ");
    print_scheduleCost(pcost,pnum);
    cout<<" "<<num_nodes-2<<endl;

    print_scheduling(scheduleList,pnum);
    /*printf("\n");
    printf("--------------------------------------------------------------------------------");*/
}

int main()
{
    /*---------------------------*/
    ifstream inp2,inp;
    inp2.open("test.ip");
    /*---------------------------*/
    int i,pnum;
    double *pspeed,*pprice;

    /*---------------------------*/
    inp2>>num_nodes;
    num_nodes+=2;
    double *cost= new double[num_nodes];
    cost[0]=cost[num_nodes-1]=0.0;
    inp.open("weight.ip");
    for(int i=1;i<num_nodes-1;i++)
    {
        int temp;
        //cin>>temp;
        inp>>temp;
        //cout<<"cost="<<temp<<endl;
        cost[i]=temp;
    }
    /*---------------------------*/

    //double cost[7]={5,10,15,40,45,35,25};
    struct node **List = new node *[num_nodes+1];
    //struct node *List[8];                   //have taken one extra to for easy index referring.
    for(i=0;i<num_nodes;i++)
        List[i]=NULL;
    List[0]=NULL;

    /*---------------------------*/
    while(true)
    {
        int x,y;
        inp2>>x>>y;

        if(x==-1){break;}
        //cout<<x<<"-"<<y<<endl;
        insertion_beg(&List[x],y);
    }
    List[num_nodes]=NULL;
    /*---------------------------*/
    /*
    insertion_beg(&List[1],2);
    insertion_beg(&List[1],3);
    insertion_beg(&List[2],7);
    insertion_beg(&List[3],4);
    insertion_beg(&List[3],5);
    insertion_beg(&List[4],6);
    insertion_beg(&List[5],6);
    insertion_beg(&List[6],7);
    List[7]=NULL;*/

    //printf("Enter the number of processors\n");
    /*---------------------------*/
    ifstream inp1;
    inp1.open("configuration.ip");
    inp1>>pnum;
    /*---------------------------*/
    //scanf("%d",&pnum);
    pspeed=(double *)malloc(sizeof(double)*pnum);
    pprice=(double *)malloc(sizeof(double)*pnum);
    //printf("Enter the speed of procesors\n");
    for(i=0;i<pnum;i++)
    {
        inp1>>pspeed[i];
        //scanf("%lf",&pspeed[i]);
    }
    //printf("Enter the prices of processors\n");
    for(i=0;i<pnum;i++)
    {
        inp1>>pprice[i];
        //scanf("%lf",&pprice[i]);
    }
    inp1.close();
    WaveFront(List,cost,num_nodes,pspeed,pprice,pnum);

    return 0;
}
