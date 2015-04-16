/*

Generating random cost configuration models of the computing resources from the folloying given formula

y = a*x^n + c 
*/

/*
Cost configuration equation
y= a*x^n + c

where:- 
y = per unit cost of using the particular computing resources
x =	speed of the processor
n = Degree of cost equation
c = Initial cost of the processor
*/

#inlcude <bits/stdc++.h>
using namespace std;


void costOutput(int x,int a,int n,int c)
{
	int temp = pow((a*x),n)+c;
	return temp;
}

void genConfig1(int a,int n,int c)
{
	int temp;
	for(int i=1;i<=10;i++)
	{
		temp=costOutput(i,1,n,c);
		cout<<temp<<endl;
	}
}
int main()
{
	int a,c,n,x;
	a=1;
	c=


#include <bits/stdc++.h>
using namespace std;
int main()
{
	int 

	return 0;
}