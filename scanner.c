/*Name:Samantha Craig
 * Class:4280
 * P1 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"token.h"
#include"scanner.h"
int charNum;
enum states {START, ID_STATE ,NUM_STATE};
enum finals {IDFINAL=101,EOFFINAL};
enum columns {letter,eof};
int table[2][2]={{ID_STATE,EOFFINAL},{ID_STATE,IDFINAL}};
struct tokenType scanner(char* line,int lineNum)
{
	//initializeGraph();
	charNum=0;
	struct charType currChar;
	struct tokenType token;
	currChar=getNextChar(line,lineNum);
	token=FADriver(currChar,line,lineNum);
	return token;
}
struct charType getNextChar(char* line,int lineNum)
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
//	table[3][3]= {{ID_STATE,EOFFINAL},{ID_STATE,IDFINAL} };
	/*table[START][letter]=ID_STATE;
	table[ID_STATE][letter]=ID_STATE;
	table[START][eof]=EOFFINAL;
	table[ID_STATE][eof]=IDFINAL;*/
}
int convertToColumnNum(struct charType c)
{
	if(c.character=='a')
	{
		return letter;
	}
	if(c.character=='b')
	{
		return letter;
	}
	if(c.character=='c')
	{
		return letter;
	}
	if(c.character=='\n')
	{
		return eof;
	} 
	if(c.character==EOF)
	{
		return eof;
	}
}
struct tokenType FADriver(struct charType c,char* line,int lineNum)
{
	int currentState=START;
	int nextState=0;
	int columnIndex=convertToColumnNum(c);
	struct tokenType token;
	char string[125];
	int count=0;
	while(currentState<100)
	{
		nextState=table[currentState][columnIndex];
		if(nextState>100)
		{
			if(nextState==IDFINAL)
			{
				token.tokenID=IDTK;
			}
			if(nextState==EOFFINAL)
			{
				token.tokenID=EOFTK;
			}
			//need reserved keyword lookup	
			token.tokenInstance=malloc(sizeof(char)*count);
			token.tokenInstance=string;
			token.lineCount=c.lineNum;
			token.charCount=count;
			return token;	
		}		
		else
		{
			currentState=nextState;
			string[count]=c.character;
			count++;
			c=getNextChar(line,lineNum);
			columnIndex=convertToColumnNum(c);	
		}
	}
}
