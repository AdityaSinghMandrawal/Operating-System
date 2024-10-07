#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
int main(){
    DIR *d;
    d=opendir("k");
    struct dirent *dir;
    if(d){
        printf("contents of Directory");
        while((dir=readdir(d))!=NULL){
            printf("%s",dir->d_name);
        }
    }
    else{
        perror("opendir");
    }
    return 0;
}
//execlp("ls","ls","-l",(char*)NULL);
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void WriteToFile(char* file,char* content){
    FILE *fp=fopen(file,"w");
    if(!fp){
        perror("NoFile");
    }
    fwrite(content,sizeof(char),strlen(content),fp);
    fclose(fp);
}
void PintMatching(char* file,char* file1){
    FILE *fp=fopen(file,"r");
    FILE *fp1=fopen(file1,"r");
    if(!fp||!fp1){
        perror("NoFile");
    }
    char line1[256],line2[256];
   while(fgets(line1,sizeof(line1),fp)&&fgets(line2,sizeof(line2),fp1)){
    if(strcmp(line1,line2)==0){
        printf("%s",line1);
    }
   }
   fclose(fp);
   fclose(fp1);
}
int main() {
    char myDetails[] = "Name: YourName\nAge: 20\nDepartment: CSE\n";
    char friendDetails[] = "Name: FriendName\nAge: 20\nDepartment: CSE\n";

    // Write details to files
    writeToFile("mydetails.txt", myDetails);
    writeToFile("frienddetails.txt", friendDetails);

    // Print matching lines
    printf("Matching lines in both files:\n");
    printMatchingLines("mydetails.txt", "frienddetails.txt");

    return 0;
}