#include<iostream>
#include<stack>
#include<stdlib.h>
#include<windows.h>
using namespace std;
typedef int ElemType;
void DrawMap();
int Map[13][13]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,0,0,0,0,1,1},
    {1,0,1,1,1,0,1,0,1,1,0,1,1},
    {1,0,0,0,0,0,1,0,1,1,0,1,1},
    {1,0,1,0,1,1,1,0,1,0,0,1,1},
    {1,0,1,0,0,0,1,0,1,0,1,1,1},
    {1,0,0,0,1,1,1,0,1,0,1,1,1},
    {4,0,1,0,1,0,0,0,1,0,0,1,1},
    {1,0,1,0,1,0,1,0,1,1,0,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,0,1,1,1,0,1,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,2,1,1,1},
};
typedef struct{
    int r;
    int i;
    int j;
    int mark;
}SA;
typedef struct
{
	ElemType data[100];
	int top;
}Sqstack;
void CreatSqstack(Sqstack * &s)
{
	s = (Sqstack*)malloc(sizeof(Sqstack*));
	s->top = -1;
}
bool Push(Sqstack * &s, ElemType &e)
{
	if (s->top == 99)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}
void Destorystack(Sqstack * &s)
{
    free(s);
}
bool Pop(Sqstack * &s, ElemType &e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}
bool Empty(Sqstack * &s)
{
    return (s->top==-1);
}
void display(Sqstack * &s,SA sa[])
{
	Sqstack *p;
	int null;
	p = s;
	ElemType b;
	null=p->top;
	p->top=0;

	while (p->top<=null){
        b=p->data[p->top];
        if(Map[sa[b].i][sa[b].j]==3)Map[sa[b].i][sa[b].j]=-1;
        p->top++;
	}
	system("cls");
	DrawMap();
	p->top=0;
	while (p->top<=null)
	{
	    b=p->data[p->top];
		cout<<b<<":";
		cout<<"("<<sa[b].i<<","<<sa[b].j<<") :"<<Map[sa[b].i][sa[b].j]<<endl;
		p->top++;
	}
    cout<<Empty(s)<<" "<<null<<endl;
}
bool AIFindRout(Sqstack * &s,SA sa[]){
    int d,i1,j1,K=0;
    bool Find=false;
    bool mark;
    ElemType B=0,e;sa[B].i=7;sa[B].j=0;sa[B].r=0;
    i1=sa[B].i;j1=sa[B].j;
    Push(s,B);
    while(!Empty(s)&&Map[i1][j1]!=2){
       system("cls");
       //Sleep(100);
       d=sa[B].r;
       while(Find==false&&d!=4){
            d++;
            i1=sa[B].i;j1=sa[B].j;
            switch(d){
                case 1:j1++;break;
                case 2:i1--;break;
                case 3:i1++;break;
                case 4:j1--;break;
            }
            if(Map[i1][j1]==0||Map[i1][j1]==2)Find=true;
       }
       if(Find){
           sa[B].r=d;
           B++;
           sa[B].i=i1;sa[B].j=j1;sa[B].r=0;
           Push(s,B);
           if(Map[i1][j1]!=2)Map[i1][j1]=-1;
           Find=false;
           mark=true;
       }
       else{
           Pop(s,e);
           Map[sa[B].i][sa[B].j]=3;
           B--;
           mark=false;
       }
       if(Map[i1][j1]==4)return false;
       //cout<<B<<":"<<sa[B].i<<","<<sa[B].j<<endl;
       //K++;
       Map[sa[B].i][sa[B].j]=5;
       DrawMap();
       if(mark)Map[sa[B].i][sa[B].j]=-1;
       else if(!mark)Map[sa[B].i][sa[B].j]=3;
       if(sa[B].i==12&&sa[B].j==9)Map[sa[B].i][sa[B].j]=2;
    }
    //cout<<"Y\n"<<K<<endl;
    display(s,sa);
    cout<<"Map[11][9]:"<<Map[11][9]<<endl;
    return true;

}
void DrawMap(){
    for(int i=0;i<13;i++){
        for(int j=0;j<13;j++){
          switch(Map[i][j]){
              case 1:cout<<"█";break;
              case 0:cout<<"  ";break;
              case 3:cout<<"  ";break;
              case -1:cout<<"☆";break;
              case 2:cout<<"★";break;
              case 4:cout<<"★";break;
              case 5:cout<<"♀";break;
          }
        }
        cout<<endl;
    }
}
int main()
{
	Sqstack *st;
	SA sa[100];
	CreatSqstack(st);
	if(AIFindRout(st,sa))cout<<endl<<"成功走出迷宫!"<<endl;
	else cout<<"没有找到路径!"<<endl;
	return 0;
}

