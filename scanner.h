struct charType{
	char character;
	int lineNum;
	int charNum;
};
struct tokenType scanner(char*,int);
struct charType getNextChar(char*,int);
void initializeGraph();
int convertToColumn(struct charType);
struct tokenType FADriver(struct charType,char*,int);
