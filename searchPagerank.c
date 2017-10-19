#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
//#include "readData.h"

#define MAX_BUFFER 64
//Pagerank ordered URL table Entry
typedef struct {
   char *UrlName;
   int  wordnum;
} UTE;

static UTE *UrlTable;      // array of url table entries

int getNumOfUrlFromFile(char *fileName);
void initUrlTable(int nums);

//number of urls
int getNumOfUrlFromFile(char *fileName) {
    if (fileName == NULL) return -1;
    int numOfUrl = 0;
    FILE *fp = fopen(fileName, "r");
    //printf("bbb\n");
    if (fp != NULL) {
        char temp[MAX_BUFFER];
        while (fscanf(fp, "\n %s ", temp) == 1) {
            if (strstr(temp, "url")) numOfUrl++;
        }
    }
    else{
        printf("opne file error");
    }
    fclose(fp);
    return numOfUrl;
}

void initUrlTable(int nums)
{
   UrlTable = malloc(nums * sizeof(UTE));
   if (UrlTable == NULL) {
      fprintf(stderr, "Can't initialise Memory\n");
      exit(EXIT_FAILURE);
   }
   //printf("aaa\n");
   for (int i = 0; i < nums; i++) {
      UTE *u = &UrlTable[i];
      u->UrlName = "\0";
      u->wordnum = 0; 
   }
}

int main(int argc, char *argv[]){

  if (argc < 2) {
      fprintf(stderr, "Not enough key words.\n");
      exit(EXIT_FAILURE);
  }

	//get nums of urls
	int nums = getNumOfUrlFromFile("pagerankList.txt");
	initUrlTable(nums);

    FILE *f = fopen("pagerankList.txt", "r");
    
    char buff[1000];//stores urls into array
    
    //copying the list of url into new array
    int i = 0;
    //printf("ccc\n");
    while (i<nums){
        //printf("ddd\n");
        fscanf(f, "%s", buff);
        //printf("eee\n");
        if (strstr(buff, "url")) {
          UrlTable[i].UrlName = strdup(buff);//creates a copy of buff into urls[i]
          UrlTable[i].UrlName[strlen(UrlTable[i].UrlName) - 1] = 0;//strcat(UrlTable[i].UrlName,"\0");
          i++;  
        }
        
    }

    //printf("ggg\n");
    
    fclose(f);

    /*printf("argc = %d\n",argc);
    int j;
    for (j=0; j < nums; j++){
      //printf("lll\n");
      printf("%s\n",UrlTable[j].UrlName);
      printf("%d\n",UrlTable[j].wordnum);
    }*/

    int k;
    for (k = 1;k < argc;k++){
      f = fopen("invertedIndex.txt", "r");
      char temp[1000];
      while(fgets(temp,sizeof temp,f)){   
        //printf("%s\n",temp);
        //printf("argv[k] = %s\n", argv[k]);
        //find the line where the key word is 
        char sub[1000]="\0";
        int length = strlen(argv[k]);
        strncpy(sub,temp,length);
        //printf("substring is %s\n",sub);
        if(strcmp(sub,argv[k]) == 0){
          //printf("%s\n",temp);
          //printf("k = %d\n",k);
          //loop through the url table
          //add to the num of key words contained in the url
          for(i = 0;i < nums;i++){
            if(strstr(temp, UrlTable[i].UrlName)){
              //printf("url = %s\n",UrlTable[i].UrlName);
              UrlTable[i].wordnum++;
              //printf("url %s = %d\n",UrlTable[i].UrlName,UrlTable[i].wordnum);
            }
          }
        }
      }
      fclose(f);
    }

    
    int j;
    for (i =(argc-1);i >0;i--){
      for(j = 0;j<nums;j++){
        if (UrlTable[j].wordnum == i){
          printf("%s\n",UrlTable[j].UrlName);
          //printf("%d\n",UrlTable[j].wordnum);
        }
      }
    }
    

    return 0;
}

