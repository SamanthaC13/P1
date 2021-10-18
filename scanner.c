/*Name:Samantha Craig
 * Class:4280
 * P1 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"token.h"
#include"scanner.h"
int charNum;
enum states {START, ID_STATE ,NUM_STATE};
enum finals {ID_FINAL=101,NUM_FINAL,WS_FINAL,EOF_FINAL};
enum columns {letter,number,ws,dollarSign,eof};
int table[3][5]={{ID_STATE,NUM_STATE,WS_FINAL,ID_STATE,EOF_FINAL},
		{ID_STATE,ID_STATE,ID_FINAL,ID_FINAL,ID_FINAL},
		{NUM_FINAL,NUM_STATE,NUM_FINAL,NUM_FINAL,NUM_FINAL}};
struct tokenType scanner(char* line,int lineNum, int startChar)
{
	//initializeGraph();
	charNum=startChar;
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
	if(isalpha(c.character)!=0)
	{
		return letter;
	}
	if(c.character==' ')
	{
		return ws;
	}
	if(c.character=='$')
	{
		return dollarSign;
	}
	if(isdigit(c.character)!=0)
	{
		return number;
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
	char* string=(char*)malloc(sizeof(char));
	int count=0;
	while(currentState<100)
	{
		nextState=table[currentState][columnIndex];
		if(nextState>100)
		{
			if(nextState==ID_FINAL)
			{
				token.tokenID=IDTK;
			}
			if(nextState==NUM_FINAL)
			{
				token.tokenID=NUMTK;
			}
			if(nextState==EOF_FINAL)
			{
				token.tokenID=EOFTK;
			}
			if(nextState==WS_FINAL)
			{
				count=1;
				token.tokenID=WSTK;
			}
			//need reserved keyword lookup	
			string[count]='\0';
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
			string=realloc(string,count*sizeof(char));
			c=getNextChar(line,lineNum);
			columnIndex=convertToColumnNum(c);	
		}
	}
}
