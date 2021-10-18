/*Name: Samantha Craig
Class:CS4280
   Project 1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include "scanner.h"
char* filterLine(char*);
int lastLine;
int ignore;
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
	char tokenNames[6][15]={"Identifier","Numbers","White Space","Keyword","End Of Line","End Of File"};
	int len=124;
	char* line=malloc(len*sizeof(char));
	line=fgets(line,len,input);
	printf("%s",line);
	line=filterLine(line);
	int lineNum=1;
	int startChar=0;
	struct tokenType token;
	while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOFTK)
	{
		while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOLTK)
		{
			printf("\n%s-%s-LineNumber:%d-Character Count:%d",tokenNames[token.tokenID],token.tokenInstance,token.lineCount,token.charCount);
			startChar=startChar+token.charCount;
		}
		line=fgets(line,len,input);
		if(feof(input))
		{
			break;
		}
		line=filterLine(line);
		startChar=0;
		lineNum++;							
		
	}
	printf("\nEndofFile-Line Number:%d\n",token.lineCount);
}
char* filterLine(char* line)
{
	int lineCharCount=0;
	int newLineCharCount=0;
	int commentFlag=0;
	char c=line[lineCharCount];
	char* newLine=malloc(sizeof(char)*124);
	while(c!='\n')
	{
		if(c=='&')
		{
			lineCharCount++;
			if(line[lineCharCount]=='&')
			{
				if(ignore==0)
				{
					ignore=1;
					commentFlag=1;
				}
				else if(ignore==1)
				{
					ignore=0;
				}
			}
			else
			{
				lineCharCount--;
			}	
		}
		if(ignore==0&&commentFlag==0)
		{
			newLine[newLineCharCount]=c;
			newLineCharCount++;	

		}
		lineCharCount++;
		c=line[lineCharCount];
		if(commentFlag==1&&ignore==0)
		{
			commentFlag=0;
		}
	}
	newLine[newLineCharCount]='\n';	
	return newLine;
}
