#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid,at,bt,st,ct,tat,wt,rt,rbt;
}process;
int comp(const void* a,const void* b){
    process* p1=(process*)a;
    process* p2=(process*)b;
    if(p1->at!=p2->at)
        return p1->at-p2->at;
    else
        return p1->pid-p2->pid;
}
int comp1(const void* a,const void* b){
    process* p1=(process*)a;
    process* p2=(process*)b;
    return p1->pid-p2->pid;
}
int max(int a,int b){
    return (a>b?a:b);
}
int main(){
    int n,sbt=0,tq;
    scanf("%d",&n);
    process p[n];
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rbt=p[i].bt;
        sbt+=p[i].bt;
    }
    scanf("%d",&tq);
    int queue[100];
    int f=0,r=0,cur=0,comp=0;
    queue[r]=0;
    int iscomp[n];
    for (int i = 0; i <n; i++)
    {
        iscomp[i]=0;
    }
    iscomp[0]=1;
    while(comp!=n){
        int indx=queue[f++];
        if(p[indx].rbt==p[indx].bt){
            p[indx].st=max(cur,p[indx].at);
            cur=p[indx].st;
        }
        if(p[indx].rbt-tq>0){
            cur+=tq;
            p[indx].rbt-=tq;
        }
        else{
            cur+=p[indx].rbt;
            p[indx].rbt=0;
            p[indx].ct=cur;
            comp++;
        }
        for(int i=1;i<n;i++){
            if(p[i].rbt>0&&p[i].at<=cur&&iscomp[i]==0){
                queue[++r]=i;
                iscomp[i]=1;
            }
        }
        if(p[indx].rbt>0){
            queue[++r]=indx;
        }
        if(f>r){
            for(int i=1;i<n;i++){
                if(p[i].rbt>0){
                    queue[++r]=i;
                    iscomp[i]=1;
                    break;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=p[i].st-p[i].at;
    }
    float cpu=((float)sbt/cur)*100;
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\n%f\t",cpu);
    
}