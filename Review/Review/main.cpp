//
//  main.cpp
//  Review
//
//  Created by Kyle.Yang on 15/6/1.
//  Copyright (c) 2015年 Kyle.Yang. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXNUM 10000

char *English[MAXNUM];
char *Chinese[MAXNUM];

void DeleteSpace(char *filename);
int readfile(int *index);
void Review(char *english[],char *chinese[],int index);
void Test(char *english[],char *chinese[],int index);
void freedom(int index);
void system(int *index);

void DeleteSpace(char *filename){
    int filename_len=strlen(filename);
    if(filename[filename_len-1]==' ')
        filename[filename_len-1]='\0';
}

int readfile(int *index){
    printf("Please enter the file path:");
    char *filename;
    filename=new char[2000];
    gets(filename);
    DeleteSpace(filename);
    FILE *file;
    int english_len;
    int chinese_len;
    char linebuffer[256];
    file=fopen(filename,"r");
    if(file==NULL){
        printf("Error while open the file!\n");
        return -1;
    }
    bzero(linebuffer,256);
    
    while(fgets(linebuffer,255,file)){
        char *pchar;
        char *pchar_temp;
        pchar=strchr(linebuffer,' ');
        pchar_temp=pchar;
        if(pchar==NULL)
            continue;
        while((pchar[1]>='a' && pchar[1]<='z')||(pchar[1]>='A' && pchar[1]<='Z')||(pchar[1]==' ')){
            pchar_temp=pchar;
            while(pchar[1]==' '){
                pchar++;
            }
            if((pchar[1]>='a' && pchar[1]<='z')||(pchar[1]>='A' && pchar[1]<='Z')){
                pchar++;
                pchar=strchr(pchar,' ');
            }
            else
                break;
        }
        english_len=pchar_temp-linebuffer;
        chinese_len=strlen(pchar)-2;
        pchar++;
        English[*index]=new char[english_len];
        memcpy(English[*index],linebuffer,english_len);
        Chinese[*index]=new char[chinese_len];
        memcpy(Chinese[*index],pchar,chinese_len);
        (*index)++;
    }
    fclose(file);
    delete [] filename;
    return 0;
}

void Review(char *english[],char *chinese[],int index){
    int *flag;
    int count=0;
    int n;
    char a;
    int num;
    int choice;
    
    flag=new int[index];
    memset(flag,0,sizeof(int)*index);
    srand((unsigned)time(NULL));
    printf("Please enter the number of words:");
    scanf("%d",&num);
    if(num>index)
        num=index;
    char **temp_english=new char *[num];
    char **temp_chinese=new char *[num];
    getchar();
    while(count<num){
        n=rand()%index;
        if(flag[n]!=1){
            flag[n]=1;
            printf("%s  %s",english[n],chinese[n]);
            temp_english[count]=english[n];
            temp_chinese[count]=chinese[n];
            a=getchar();
            while(a!='\n'){
                a=getchar();
            }
            count++;
        }
    }
    printf("1.Test after review 0.Exit\n");
    scanf("%d",&choice);
    while(choice!=0){
        if(choice==1){
            Test(temp_english,temp_chinese,num);
            printf("1.Test after review 0.Exit\n");
            scanf("%d",&choice);
        }
        else{
            printf("1.Test after review 0.Exit\n");
            scanf("%d",&choice);
        }
    }
    delete [] temp_english;
    delete [] temp_chinese;
    delete [] flag;
}

void Test(char *english[],char *chinese[],int index){
    int *flag;
    int count=0;
    int n;
    int tag=0;
    char a;
    int num;
    char *temp_answer=new char[200];

    flag=new int[index];
    memset(flag,0,sizeof(int)*index);
    srand((unsigned)time(NULL));
    printf("Please enter the number of words:");
    scanf("%d",&num);
    getchar();
    if(num>index)
        num=index;
    while(count<num){
        tag=0;
        n=rand()%index;
        if(flag[n]!=1){
            flag[n]=1;
            printf("%s\n",chinese[n]);
            a=getchar();
            while(a!='\n'){
                temp_answer[tag]=a;
                tag++;
                a=getchar();
            }
            temp_answer[tag]='\0';
            if(tag==0){
                printf("The answer is %s\n",english[n]);
                count++;
            }
            else{
                if(strcmp(temp_answer,english[n])==0)
                    printf("Correct!\n");
                else
                    printf("Wrong!The correct answer is %s\n",english[n]);
                count++;
            }
        }
    }
    delete [] flag;
    delete [] temp_answer;
}

void freedom(int index){
    for(int i=0;i<index;i++){
        delete English[index];
        delete Chinese[index];
    }
}

void system(int *index){
    int tag;
    printf("The World List Program Version 1.0 Created By Kyle.Yang\n");
    int flag=readfile(index);
    while(flag==-1){
        flag=readfile(index);
    }
    printf("1.Review 2.Test 0.Exit\n");
    scanf("%d",&tag);
    while(tag!=0){
        switch(tag){
            case 1:
                Review(English,Chinese,*index);
                printf("1.Review 2.Test 0.Exit\n");
                scanf("%d",&tag);
                break;
            case 2:
                Test(English,Chinese,*index);
                printf("1.Review 2.Test 0.Exit\n");
                scanf("%d",&tag);
                break;
            case 0:
                exit(0);
            default:
                printf("1.Review 2.Test 0.Exit\n");
                scanf("%d",&tag);
                break;
        }
    }
}

int main(){
    int index=0;
    
    system(&index);
    freedom(index);
    
    return 0;
}
