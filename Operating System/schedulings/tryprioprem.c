#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid,at,bt,pri,st,ct,tat,wt,rt;
}process;
int main(){
    int n;
    scanf("%d",&n);
    process p[n];
    int sbt=0,rem[n];
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pri);
        sbt+=p[i].bt;
        rem[i]=p[i].bt;
    }
    int cur=0,comp=0;
    int iscomp[n];
    for(int i=0;i<n;i++) iscomp[i]=0;
    while(comp!=n){
        int indx=-1;
        int maxp=-1;
        for(int i=0;i<n;i++){
            if(p[i].at<=cur&&iscomp[i]==0){
                if(p[i].pri>maxp){
                    maxp=p[i].pri;
                    indx=i;
                }
                else if(p[i].pri==maxp){
                    if(p[i].at<p[indx].at)
                        indx=i;
                }
            }
        }
        if(indx==-1){
            cur++;
        }
        else{
            if(p[indx].bt==rem[indx]){
                p[indx].st=cur;
            }
            rem[indx]--;
            cur++;
            if(rem[indx]==0){
                p[indx].ct=cur;
                iscomp[indx]=1;
                comp++;
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