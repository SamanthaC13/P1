/*Name:Samantha Craig
 * Class:4280
 * P1 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"scanner.h"
FILE*input;
char* line;
int lineNum;
int charNum;
void driver(char* filename)
{
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
/*int[][] initializeGraph(int[][])
{



}
struct token FADriver(struct charType)
{


}*/
