/*Name:Samantha Craig
 * Class:4280
 * P1 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"scanner.h"
int Table[3][2];
FILE*input;
char* line;
int lineNum;
int charNum;
enum states (START, IDSTATE , FINAL);
enum columns (letter=1,eof=2);
void driver(char* filename)
{
	Table=initializeGraph;
	input=fopen(filename,"r");
	if(input==NULL)
	{
		fprintf(stderr,"Error opening input file in scanner");
	}
	int len=124;
	int ignore=0;
	line=malloc(len*sizeof(char));
	lineNum=0;
	charNum=0;
	struct charType currChar;
	while(fgets(line,len,input)!=NULL)
	{
		lineNum++;
		charNum=0;
		currChar=getNextChar();
		while(currChar.character!='\n')
		{
			charNum++;
			currChar=getNextChar();	
		}
	}
}
struct charType getNextChar()
{
	struct charType c;
	c.character=line[charNum];
	c.charNum=charNum;
	c.lineNum=lineNum;
	return c;
}
int[][] initializeGraph()
{
	Table[START][letter]=ID_STATE;
	Table[ID_STATE][letter]=ID_STATE;
	Table[START][eof]=FINAL;
	Table[ID_STATE][eof]=FINAL;
}
int convertToColumnNum(struct charType c)
{
	if(isAlpha(c.character))
	{
		return letter;
	}
}
struct tokenType FADriver(struct charType c)
{
	struct stateType currentState;
	struct stateType nextState;
	currentState.columnName=convertToColumnNum(c);
	currentState.name=start;
	struct tokenType token;
	char string[125]=NULL;
	int count=0;
	while(currentState.name!=FINAL)
	{
		nextState.name=Table[currentState.name][currentState.columnName];
		if(currentState.name==FINAL)
		{
			//need reserved keyword lookup
			token.tokenInstance=malloc(sizeof(char)*count);
			token.tokenInstance=string;
			token.tokenID=currentState.name;
			token.lineCount=c.lineNum;
			token.charCount=c.charNum;
			return token;	
		}		
		else
		{
			currentState.name=nextState.name;
			string[count]=c.character;
			count++;
			c=getNextChar();
			currentState.columnName=convertToColumnName(c);	
		}

	}


}
