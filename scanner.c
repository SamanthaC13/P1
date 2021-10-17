/*Name:Samantha Craig
 * Class:4280
 * P1 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include"scanner.h"
int table[3][2];
int lineNum;
int charNum;
enum states {START, ID_STATE , FINAL};
enum columns {letter=1,eof=2};
struct tokenType scanner(char* line,int lineNum)
{
	initializeGraph();
	charNum=0;
	struct charType currChar;
	struct tokenType token;
	currChar=getNextChar(line);
	token=FADriver(currChar,line);
	return token;
}
struct charType getNextChar(char* line)
{
	struct charType c;
	c.character=line[charNum];
	c.charNum=charNum;
	c.lineNum=lineNum;
	charNum++;
	return c;
}
void initializeGraph()
{
	table[START][letter]=ID_STATE;
	table[ID_STATE][letter]=ID_STATE;
	table[START][eof]=FINAL;
	table[ID_STATE][eof]=FINAL;
}
int convertToColumnNum(struct charType c)
{
	if(isAlpha(c.character))
	{
		return letter;
	}
}
struct tokenType FADriver(struct charType c,char* line)
{
	struct stateType currentState;
	struct stateType nextState;
	currentState.columnName=convertToColumnNum(c);
	currentState.name=START;
	struct tokenType token;
	char string[125];
	int count=0;
	while(currentState.name!=FINAL)
	{
		nextState.name=table[currentState.name][currentState.columnName];
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
			c=getNextChar(line);
			currentState.columnName=convertToColumnName(c);	
		}

	}


}
