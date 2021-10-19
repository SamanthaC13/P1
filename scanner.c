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
enum states {START, ID_STATE ,NUM_STATE,GREATER_STATE,LESSER_STATE,EQUAL_STATE,DOUBLEEQ_STATE,COLON_STATE,COLONEQ_STATE};
enum finals {ID_FINAL=101,NUM_FINAL,WS_FINAL,EOL_FINAL,GREATER_FINAL,LESSER_FINAL,EQ_FINAL,DOUBLEEQ_FINAL,COLON_FINAL,COLONEQ_FINAL,EOF_FINAL};
enum columns {letter,number,ws,dollarSign,eol,greater,lesser,equal,colon,eof};
int table[9][10]={{ID_STATE,NUM_STATE,WS_FINAL,ID_STATE,EOL_FINAL,GREATER_STATE,LESSER_STATE,EQUAL_STATE,COLON_STATE,EOF_FINAL},
		{ID_STATE,ID_STATE,ID_FINAL,ID_FINAL,ID_FINAL,ID_FINAL,ID_FINAL,ID_FINAL,ID_FINAL,ID_FINAL},
		{NUM_FINAL,NUM_STATE,NUM_FINAL,NUM_FINAL,NUM_FINAL,NUM_FINAL,NUM_FINAL,NUM_FINAL,NUM_FINAL,NUM_FINAL},
		{GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL,GREATER_FINAL},
		{LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL,LESSER_FINAL},
		{EQ_FINAL,EQ_FINAL,EQ_FINAL,EQ_FINAL,EQ_FINAL,EQ_FINAL,EQ_FINAL,DOUBLEEQ_STATE,EQ_FINAL,EQ_FINAL},
		{DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL,DOUBLEEQ_FINAL},
		{COLON_FINAL,COLON_FINAL,COLON_FINAL,COLON_FINAL,COLON_FINAL,COLON_FINAL,COLON_FINAL,COLONEQ_STATE,COLON_FINAL,COLON_FINAL},
		{COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL,COLONEQ_FINAL}
		};
char* keywords[16]={"start","stop","loop","while","for","label","exit","listen","talk",
			"program","if","then","assign","declare","jump","else"};
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
		return eol;
	}
	if(c.character=='>')
	{
		return greater;
	}
	if(c.character=='<')
	{
		return lesser;
	}
	if(c.character=='=')
	{
		return equal;
	}
	if(c.character==':')
	{
		return colon;	
	}
	if(c.character=='\0')
	{
		return eof;
	}
}
int isKeyword(char* string)
{
	int i=0;
	for(i=0;i<16;i++)
	{
		if(strcmp(string,keywords[i])==0)
		{
			return 1;
		}
	}
	return 0;
} 
struct tokenType FADriver(struct charType c,char* line,int lineNum)
{
	int currentState=START;
	int nextState=0;
	int columnIndex=convertToColumnNum(c);
	struct tokenType token;
	char* string=(char*)malloc(sizeof(char));
	int stringCount=0;
	while(currentState<100)
	{
		nextState=table[currentState][columnIndex];
		if(nextState>100)
		{
			if(nextState==ID_FINAL)
			{
				token.tokenID=IDTK;
				if(isKeyword(string)==1)
				{
					token.tokenID=KEYWRDTK;
				}
				token.charCount=stringCount;
			}
			if(nextState==NUM_FINAL)
			{
				token.charCount=stringCount;
				token.tokenID=NUMTK;
			}
			if(nextState==EOF_FINAL)
			{
				token.charCount=stringCount;
				token.tokenID=EOFTK;
			}
			if(nextState==EOL_FINAL)
			{
				token.charCount=1;
				token.tokenID=EOLTK;
			}
			if(nextState==WS_FINAL)
			{
				token.charCount=1;
				token.tokenID=WSTK;
			}
			if(nextState==GREATER_FINAL)
			{
				token.charCount=1;
				token.tokenID=GTTK;
			}
			if(nextState==LESSER_FINAL)
			{
				token.charCount=1;
				token.tokenID=LTTK;
			}
			if(nextState==EQ_FINAL)
			{
				token.charCount=1;
				token.tokenID=EQTK;
			}
			if(nextState==DOUBLEEQ_FINAL)
			{
				token.charCount=stringCount;
				token.tokenID=DBEQTK;
			}
			if(nextState==COLON_FINAL)
			{
				token.charCount=1;
				token.tokenID=CLNTK;
			}
			if(nextState==COLONEQ_FINAL)
			{
				token.charCount=stringCount;
				token.tokenID=CLNEQTK;
			}
			//need reserved keyword lookup	
			string[stringCount]='\0';
			token.tokenInstance=string;
			token.lineCount=c.lineNum;
			return token;	
		}		
		else
		{
			currentState=nextState;
			string[stringCount]=c.character;
			stringCount++;
			string=realloc(string,stringCount*sizeof(char));
			c=getNextChar(line,lineNum);
			columnIndex=convertToColumnNum(c);	
		}
	}
}
