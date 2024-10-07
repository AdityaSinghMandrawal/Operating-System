#include<stdio.h>
#include<stdlib.h>
int main(){
    int n,r;
    scanf("%d %d");
    int alloc[n][r],maxalloc[n][r],need[n][r];
    int total[r],ava[r];
    for(int i=0;i<n;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<r;j++){
            scanf("%d",&maxalloc[i][j]);
        }
    }
    for(int i=0;i<r;i++){
        scanf("%d",&total[i]);
    }
    for(int i=0;i<r;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            sum+=alloc[j][i];
        }
        ava[i]=total[i]-sum;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = maxalloc[i][j] - alloc[i][j];
        }
    }
    int f[n],ss[n],ind=0;
    for(int i=0;i<n;i++) f[i]=0;
    for(int k=0;k<n;k++){
        int maxindx=-1;
        int maxr=-1;
        for(int i=0;i<n;i++){
            if(f[i]==0){
                int flag=0;
                for(int j=0;j<r;j++){
                    if(need[i][j]>ava[j]){
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    int res=0;
                    for(int j=0;j<r;j++){
                        res+=alloc[i][j];
                    }
                    if(res>maxr){
                        maxr=res;
                        maxindx=i;
                    }
                }
            }
        }
        if(maxindx==-1){
            printf("Not safe sequence");
        }
        ss[ind++]=maxindx;
        for(int y=0;y<r;y++){
            ava[y]+=alloc[maxindx][y];
        }
        f[maxindx]=1;
    }
    printf("\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", ss[i]);
    }

    return 0;
}