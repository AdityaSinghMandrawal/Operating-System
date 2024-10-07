#include<stdio.h>
#include<stdlib.h>
typedef struct process{
    int pid,at,bt,st,ct,tat,wt,rt,pri;
}process;
int main(){
    int n;
    scanf("%d",&n);
    process p[n];
    int sbt;
    for (int i = 0; i <n; i++)
    {
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pri);
        p[i].pid=i+1;
        sbt+=p[i].bt;
    }
    int comp=0,cur=0;
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
            p[indx].st=cur;
            p[indx].ct=p[indx].st+p[indx].bt;
            cur+=p[indx].bt;
            iscomp[indx]=1;
            comp++;
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