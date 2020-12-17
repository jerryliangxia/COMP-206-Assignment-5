/*
 * Program to track IP addresses and find collaborators
 * ********************************************
 * Author	Dept.		Date		Notes
 * Jerry Xia	Soft. Eng.	Nov 14 2020	Initial draft.
 * Jerry Xia	Soft. Eng.	Nov 16 2020	Fixed strtok.
 * Jerry Xia	Soft. Eng.	Nov 17 2020	Final draft.
 * ********************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct logrecord
{
  char name[100];
  char IP[50];
} logrecord;

logrecord readLog(char* logline)
{
  logrecord l;
  char* thisIP;
  char *last = strrchr(logline, ',');
  if (last != NULL) thisIP=(last+1);
  char* thisName = strtok(logline, ",");

  strcpy(l.name,thisName);
  strcpy(l.IP,thisIP);
  return l;
}

int checkIfNameExists(FILE* file, char* name)
{
  //first, checks if name exists
  while (!feof(file)) //goes through all lines
  {
    char logLine[200];
    int doesExist=0; //used to check if name exists
    while(fgets(logLine, 200, file)!=NULL)
    {
      char *array[10];
      int i=0;
      array[i] = strtok(logLine,",");
      while(array[i]!=NULL) array[++i] = strtok(NULL,",");
      char* thisName = array[0];
      char* thisIP = array[6];
      if(strcmp(name,thisName)==0) doesExist=1;
    }
    if(doesExist!=1) 
    {
      printf("Error, unable to locate %s\n", name);
      return 1;
      break;
    }
  }
  return 0;
}

logrecord getInfo(FILE* file, char* name)
{
  logrecord l;
  //read through the file again
  char logLine[200];
  while(fgets(logLine, 200, file)!=NULL)
  {
    char* findIP;
    char *last = strrchr(logLine, ',');
    if (last != NULL) findIP=(last+1);

    char* thisName = strtok(logLine, ",");
    
    if(strcmp(name,thisName)==0) {
      strcpy(l.name,thisName);
      strcpy(l.IP,findIP);
      break;
    }
  }
  return l;
}

int main(int argc, char* argv[]) {

  char *name = argv[2];
  int cheatersExist = 0;
  //check correct number of arguments
  if(argc!=4)
  {
    printf("Usage ./report <csvfile> \"<student name>\" <reportfile>\n");
    return 1;
  }
  
  
  
  //check if the data file exists
  FILE *fileX = fopen(argv[1], "r");
    if(fileX == NULL)
  {
    printf("Error, unable to open csv file %s \n", argv[1]);
    return 1;
  }
  fclose(fileX);

  //test to see if the output file exists
  // FILE *fileY = fopen(argv[3], "w");
  //   if(fileY == NULL)
  //   {
  //   printf("Error, unable to open the output file %s \n", argv[3]);
  //   return 1;
  // }
  // fclose(fileY);
  if( access( argv[3], F_OK ) != -1 ) {
  } else {
      // file doesn't exist
      printf("Error, unable to open the output file %s \n", argv[3]);
      exit(EXIT_FAILURE);
  }
  

  FILE *file; //opens the file
  file = fopen(argv[1], "r");
  int x = checkIfNameExists(file, name);
  fclose(file);
  if(x==0)
  {
    FILE *newfile; //opens the file
    newfile = fopen(argv[1], "r");
    logrecord Adaline = getInfo(newfile, name);  //gets IP address of argv[1]
    //printf("%s",Adaline.IP);
    fclose(newfile);

    FILE *csvfile; //opens the file to find collaborators
    csvfile = fopen(argv[1], "r");

    int i = 0;//for overwriting
    while(!feof(csvfile))
    {
      char logline[200];
      char* line = fgets(logline, 200, csvfile);
      logrecord tmp_user = readLog(line);
      //Hint: you could try to store the previously reported collaborator's name first and compare it with the "current" one
      
      if((strcmp(tmp_user.IP,Adaline.IP)==0) && (strcmp(tmp_user.name,name)!=0))
      {
        cheatersExist = 1;
        if(i==0)
        {
          FILE* rptfile = fopen(argv[3], "w");
          fprintf(rptfile, "%s\n",tmp_user.name);
          fclose(rptfile);
          
          i++;
        }
        else 
        {
          FILE* rpTfile = fopen(argv[3], "a+");

          char logl[200];
          char* rptline = fgets(logl, 200, rpTfile);
          logrecord rpt_user = readLog(rptline);
          strcat(tmp_user.name,"\n");
          
          if(strcmp(rpt_user.name,tmp_user.name)!=0)
          {
            //int q = checkIfNameExists(FILE *file, char *name)
            fprintf(rpTfile, "%s",tmp_user.name);

          }
          else
          {
            continue;
          }
       
          fclose(rpTfile);
        }

      }


    }fclose(csvfile);
    
  }
  else
  {
    return 1;
  }

  if(cheatersExist==0) 
  {
    FILE* reportfinal = fopen(argv[3],"w");
    fprintf(reportfinal,"No collaborators found for %s\n", name);
    fclose(reportfinal);
  }
    
  
  
  


  return 0;

}
