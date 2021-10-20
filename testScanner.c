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
int ignore=0;
int main(int argc, char**argv)
{
	char* filename;                   
	int option=0;
	//This option if the user only entered the Program name without a file
	if(argc==1)
	{
		char character;
		FILE* temp;
		option=1;
		temp=fopen("temp.txt","w");
		//Takes in the Keyboard input and writes it to a file I call temp.txt
		while((character=getc(stdin))!=EOF)
		{
			fputc(character,temp);
		}
		fputc('\n',temp);
		fputc('\0',temp);
		fclose(temp);
		filename=malloc(sizeof(char)*10);
		strcpy(filename,"temp.txt");
        }
	else
	{
		filename=argv[1];
		filename=strcat(filename,".fs");
		
	}
	FILE* input;
	char* lastLine;
	input=fopen(filename,"r");
	if(input==NULL)
	{
		fprintf(stderr,"Error opening input file in TestScanner");
		exit(1);
	}
	char tokenNames[26][25]={"Identifier","Number","White Space","Keyword","End Of Line","Greater Than","Less Than","Equal","Double Equal","Colon","Colon Equal","Plus","Minus","Asterisk","Slash","Percent","Period","Left Pareneses","Right Pareneses","Comma","Left Brace","Right Brace","Semi-Colon","Left Bracket","Right Bracket","End Of File"};
	char errorNames[2][25]={"Bad Character Entered","UpperCase Letter Starter"};
	int len=124;
	char* line=malloc(len*sizeof(char));
	line=fgets(line,len,input);
	line=filterLine(line);
	int lineNum=1;
	int startChar=0;
	struct tokenType token;
	while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOFTK)
	{
		while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOLTK)
		{
			if(token.tokenID<0)
			{
				printf("\nSCANNER ERROR:%s LINE NUMBER:%d\n",errorNames[(token.tokenID*-1)-1],lineNum);
				exit(1);
			}
			if(token.tokenID!=WSTK)
			{
				printf("\n%s-%s-LineNumber:%d-Character Count:%d",tokenNames[token.tokenID],token.tokenInstance,token.lineCount,token.charCount);
			}
			startChar=startChar+token.charCount;
		}
		lastLine=line;
		line=fgets(line,len,input);
		if(feof(input))
		{
			line=lastLine;
			startChar=startChar+1;
		}
		else
		{
			line=filterLine(line);
			startChar=0;
			lineNum++;
		}							
		
	}
	printf("\n%s-Line Number:%d\n",tokenNames[token.tokenID],token.lineCount);
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
					commentFlag=1;
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
