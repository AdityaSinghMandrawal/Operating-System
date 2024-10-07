#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid,at,bt,st,ct,tat,wt,rt;
}process;
int main(){
    int n;
    scanf("%d",&n);
    process p[n];
    int comp[n];
    int cur=0,sbt=0;
    int iscomp=0;
    for(int i=0;i<n;i++){
        comp[i]=0;
    }
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        scanf("%d %d",&p[i].at,&p[i].bt);
        sbt+=p[i].bt;
    }
    while(iscomp!=n){
        int minindx=-1;
        int minbt=1e9;
        for(int i=0;i<n;i++){
            if(p[i].at<=cur&&comp[i]==0){
                if(p[i].bt<minbt){
                    minbt=p[i].bt;
                    minindx=i;
                }
                else if(p[i].bt==minbt){
                    if(p[i].at<p[minindx].at){
                        minindx=i;
                    }
                }
            }
        }
        if(minindx==-1){
            cur++;
        }
        else{
            p[minindx].st=cur;
            p[minindx].ct=p[minindx].st+p[minindx].bt;
            p[minindx].tat=p[minindx].ct-p[minindx].at;
            p[minindx].wt=p[minindx].tat-p[minindx].bt;
            p[minindx].rt=p[minindx].st-p[minindx].at;
            comp[minindx]=1;
            iscomp++;
            cur=p[minindx].ct;
        }
    }
    float cpu=((float)sbt/cur)*100;
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\n%f\t",cpu);
    return 0;
}
