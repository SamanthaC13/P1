/*Name: Samantha Craig
Class:CS4280
   Project 1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include "scanner.h"
void printToken(struct tokenType);
int main(int argc, char**argv)
{
	char* filename;                   
	int option=0;
	//This option if the user only entered the Program name without a file
	if(argc==1)
	{
		char string[50];
		FILE* temp;
		option=1;
		temp=fopen("temp.txt","w");
		//Takes in the Keyboard input and writes it to a file I call temp.txt
		while(scanf("%s",string)!=-1)
		{
			fprintf(temp,"%s ",string);
		}
		fclose(temp);
		filename=malloc(sizeof(char)*10);
		strcpy(filename,"temp.txt");
        }
	else
	{
		filename=argv[1];
	}
	FILE* input;
	input=fopen(filename,"r");
	if(input==NULL)
	{
		fprintf(stderr,"Error opening input file in TestScanner");
	}
	int len=124;
	char* line=malloc(len*sizeof(char));
	line=fgets(line,len,input);
	int lineNum=1;
	struct tokenType token;
	while((token=scanner(line,lineNum))!=EOFTK)
	{
		printToken(token);
		/*
 *		while((token=scanner(line,lineNum))!=EOLTK)
 *		{
 *			printToken();
 *		}
 * 		*/
		fgets(line,len,input);
		lineNum++;	
	}
}
void printToken(struct tokenType token)
{
	printf("(%d-%s-%d-%d",token.tokenID,token.tokenInstance,token.lineCount,token.charCount);
}
