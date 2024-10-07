#include<stdio.h>
#include<stdlib.h>
#define max 1e9;
typedef struct process{
    int pid,at,bt,st,ct,tat,wt,rt;
}process;
int main(){
    int n;
    scanf("%d",&n);
    process p[n];
    int comp[n];
    for(int i=0;i<n;i++)
        comp[i]=0;
    int iscomp=0;
    int rem[n];
    int sbt=0,cur=0;
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        scanf("%d %d",&p[i].at,&p[i].bt);
        sbt+=p[i].bt;
        rem[i]=p[i].bt;
    }
    while(iscomp!=n){
        int mindx=-1;
        int minbt=max;
        for(int i=0;i<n;i++){
            if(p[i].at<=cur&&comp[i]==0){
                if(rem[i]<minbt){
                    minbt=rem[i];
                    mindx=i;
                }
                else if(rem[i]==minbt){
                    if(p[i].at<p[mindx].at){
                        mindx=i;
                    }
                }
            }
        }
        if(mindx==-1){
            cur++;
        }
        else{
            if(rem[mindx]==p[mindx].bt){
                p[mindx].st=cur;
            }
            rem[mindx]--;
            cur++;
            if(rem[mindx]==0){
                p[mindx].ct=cur;
                comp[mindx]=1;
                iscomp++;
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
