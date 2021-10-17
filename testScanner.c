/*Name: Samantha Craig
Class:CS4280
   Project 1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include "scanner.h"
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
	char tokenNames[2][15]={"Identifier","Numbers","End Of File"};
	int len=124;
	char* line=malloc(len*sizeof(char));
	line=fgets(line,len,input);
	int lineNum=1;
	struct tokenType token;
	//while(token=scanner(line,lineNum)).tokenID!=EOFTK)
	{
		token=scanner(line,lineNum);
		//printf("\n%s ",tokenNames[token.tokenID]);
		fprintf(stderr,"%s",token.tokenInstance);
		printf("LineNumber:%d-Char Count:%d\n",token.lineCount,token.charCount);
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
