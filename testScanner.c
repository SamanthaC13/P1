/*Name: Samantha Craig
Class:CS4280
   Project 1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	//Send to fileFilter in scannner
	driver(filename);
}
