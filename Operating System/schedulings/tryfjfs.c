#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid,at,bt,tat,wt,rt,st,ct;
}process;
int comp(const void *a,const void *b){
    process* p1=(process*)a;
    process* p2=(process*)b;
    if(p1->at!=p2->at)
        return p1->at-p2->at;
    else
        return p1->pid-p2->pid;
    
}
int comp1(const void *a,const void *b){
    process* p1=(process*)a;
    process* p2=(process*)b;
    return p1->pid-p2->pid;
}
int main(){
    int n;
    scanf("%d",&n);
    process p[n];
    int sbt=0,cur=0,srt,stat,swt;
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        scanf("%d %d",&p[i].at,&p[i].bt);
        sbt+=p[i].bt;
    }
    qsort(p,n,sizeof(process),comp);
    for(int i=0;i<n;i++){
        if(p[i].at<=cur){
            p[i].st=cur;
            p[i].ct=p[i].st+p[i].bt;
            cur+=p[i].bt;
        }
        else{
            cur=p[i].at;
            p[i].st=cur;
            p[i].ct=p[i].st+p[i].bt;
            cur+=p[i].bt;
        }
    }
    qsort(p,n,sizeof(process),comp1);
    for(int i=0;i<n;i++){
        p[i].rt=p[i].st-p[i].at;
        srt+=p[i].rt;
        p[i].tat=p[i].ct-p[i].at;
        stat+=p[i].tat;
        p[i].wt=p[i].tat-p[i].bt;
        swt+=p[i].wt;
    }
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    float cpu=((float)sbt/cur)*100;
    float throught=(float)n/cur;
    printf("%f %f\n",cpu,throught);
}