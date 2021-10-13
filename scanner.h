struct tokenType{
	int tokenID;
	char* tokenInstance;
	int lineCount;
	int charCount;
};
struct charType{
	char character;
	int lineNum;
	int charNum;
};
struct stateType{
	int name;
	int columnName;
};
void driver(char*);
struct charType getNextChar();
//int* initalizeGraph(int*);
//int convertToCharColumn(struct charType);
//struct token FADriver(struct charType);
