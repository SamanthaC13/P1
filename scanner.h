struct token{
	int tokenID;
	char* tokenInstance;
	int lineCount;
	int charCount;
}
struct charType{
	char character;
	int lineNum;
	int charNum;
}
void driver(char*);
struct charType getNextChar(FILE*);
int* initalizeGraph(int*);
int convertToCharColumn(struct charType);
struct token FADriver(struct charType);
