struct charType{
	char character;
	int lineNum;
	int charNum;
};
struct stateType{
	int name;
	int columnName;
};
struct tokenType scanner(char*,int);
struct charType getNextChar(char*);
void initializeGraph();
int convertToColumn(struct charType);
struct tokenType FADriver(struct charType,char*);
