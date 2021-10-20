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
		//Writes the end of file to th etemp file I created for the keyboard input
		fputc('\n',temp);
		fputc('\0',temp);
		fclose(temp);
		filename=malloc(sizeof(char)*10);
		strcpy(filename,"temp.txt");
        }
	else
	{
		//filename is set to the file the user entered with the implict extension .fs
		filename=argv[1];
		filename=strcat(filename,".fs");
		
	}
	FILE* input;
	char* lastLine;
	//file is opened for reading 
	input=fopen(filename,"r");
	if(input==NULL)
	{
		//Error is printed if input file is  unable to be opened
		fprintf(stderr,"Error opening input file in TestScanner");
		exit(1);
	}
	//Names of all the token types that corespound to tokenIDs 
	char tokenNames[26][25]={"Identifier","Number","White Space","Keyword","End Of Line","Greater Than","Less Than","Equal","Double Equal","Colon","Colon Equal","Plus","Minus","Asterisk","Slash","Percent","Period","Left Pareneses","Right Pareneses","Comma","Left Brace","Right Brace","Semi-Colon","Left Bracket","Right Bracket","End Of File"};
	//error namaes that correspond to the error found in the scanner
	char errorNames[2][25]={"Bad Character Entered","UpperCase Letter Starter"};
	//arbitary line length given to read a line from file
	int len=124;
	char* line=malloc(len*sizeof(char));
	//read first line from file
	line=fgets(line,len,input);
	//send line to filter to filter out comments
	line=filterLine(line);
	int lineNum=1;
	int startChar=0;
	struct tokenType token;
	//This outer loop checks that the first token or last token is not EOF token 
	while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOFTK)
	{
		while(((token=scanner(line,lineNum,startChar)).tokenID)!=EOLTK)
		//This while loop takes the token and goes till the end of the line token is found 
		{
			if(token.tokenID<0)
			{//An error returns a tokenID of a negative number and the error is printed and the program is exited
				printf("\nSCANNER ERROR:%s LINE NUMBER:%d\n",errorNames[(token.tokenID*-1)-1],lineNum);
				exit(1);
			}
			if(token.tokenID!=WSTK)
			{//If a token is not a white space token then print it 
				printf("\n%s-%s-LineNumber:%d-Character Count:%d",tokenNames[token.tokenID],token.tokenInstance,token.lineCount,token.charCount);
			}
			//I am keeping track of where I am in the line by the startChar variable basically as the token character count in the line 
			startChar=startChar+token.charCount;
		}
		//set a pointer to point to the current line
		lastLine=line;
		//read the next line even if the current line was the last line
		line=fgets(line,len,input);
		if(feof(input))
		{//if the current line was the last line then the lastLine variable will not be the line again and the next token gotten will be the EOFTK
			line=lastLine;
			startChar=startChar+1;
		}
		else
		{//if the new line we just got was not after the EOF then it was not the lastLine and a new line needs to be filtered and got tokens from and line number is increased by 1
			line=filterLine(line);
			startChar=0;
			lineNum++;
		}
	}
	//if we have broken out of the outer while loop then we have hit the EOF token and we just nned to print it
	printf("\n%s-Line Number:%d\n",tokenNames[token.tokenID],token.lineCount);
}
char* filterLine(char* line)
//This function takes the line from the file and filters it into a newLine without comments
{
	//Count for the orginal line
	int lineCharCount=0;
	//count for the new created line
	int newLineCharCount=0;
	//flag for if there is a comment in this line
	int commentFlag=0;
	//c is the currrnet character from the orginal line
	char c=line[lineCharCount];
	char* newLine=malloc(sizeof(char)*124);
	while(c!='\n')
	//want to read the orginal line til it ends with the \n character
	{
		if(c=='&')
		//If we get one apersand then we look to see if the next character is an apersand
		{
			lineCharCount++;
			if(line[lineCharCount]=='&')
			//if we found a second apersand then we need to figure out if it is the beginning pair or the end pair of the comment for this I used the global variable ignore
			{
				if(ignore==0)
				//if ignore is 0 then this is the beginning pair and sets ignore to 1 and commentFlag to 1
				{
					ignore=1;
					commentFlag=1;
				}
				else if(ignore==1)
				//if ignore if already 1 then this is the end pair and ignore is set back to one but the comment Flag is set to 1 so the apersand is not put into newLine 
				{
					ignore=0;
					commentFlag=1;
				}
			}
			else
			//if we got one apersand and then their was not a second one then the appersand will be added to the newLine 
			{
				lineCharCount--;
			}	
		}
		if(ignore==0&&commentFlag==0)
		//if both the ignore and comment flags are 0 then the character c can be added to newLine and the new Line count is incremented
		{
			newLine[newLineCharCount]=c;
			newLineCharCount++;	

		}
		//the orginal line count is increased on every iteration
		lineCharCount++;
		c=line[lineCharCount];
		if(commentFlag==1&&ignore==0)
		//if the comment flag and ignore are different then comment flag is set to zero this is set so the first apersand or the last apersand are not added to newLine
		{
			commentFlag=0;
		}
	}
	//a new line character is added to the end of newLine 
	newLine[newLineCharCount]='\n';	
	//the newLine is returned 
	return newLine;
}
